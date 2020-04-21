#include "worldGenerator.h"

void startWorldGeneration()
{

	// initiate generation parameters

	const int maxGeneratedPoints = 1200;
	const int maxGalaxyRadius = 5000;
	const int sectorPropertiesCountWeightRaw[12] = { 0, 10, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


	std::map<int, int> sectorPropertiesCountWeight;

	int wParam = 0;
	for (int i(0); i < 12; i++)
	{
		wParam += sectorPropertiesCountWeightRaw[12];
		sectorPropertiesCountWeight[wParam] = i;
	}

	gEnv->game.randTmp = gEnv->game.worldSeed;

	AdnvetureData * a = &gEnv->game.adventureData;



	// point generation

	for (int i(0); i < maxGeneratedPoints; i++)
	{

		int x = (getRand() % (2*maxGalaxyRadius)) - maxGalaxyRadius;
		int y = (getRand() % (2*maxGalaxyRadius)) - maxGalaxyRadius;

		if ((x*x) + (y*y) > maxGalaxyRadius*maxGalaxyRadius)
			continue;

		MapSector * p = new MapSector();

		p->x = x;
		p->y = y;

		p->distance = sqrt((x*x) + (y*y));

		//p->key = getRand64();
		p->key = getRand();

		//a->sectors[std::to_string(p->key)] = p;

		a->sectors[std::to_string(i)] = p;

	}

	printf("(World generator log) Initial generation: %li points\n", a->sectors.size());

	// region generation

	// not used yet

	for (auto it(a->sectors.begin()); it != a->sectors.end(); it++)
	{
		it->second->regionName = "default";
	}

	// properties generation

	for (auto it(a->sectors.begin()); it != a->sectors.end(); it++)
	{
		
		auto p = it->second;

		// get list of available properties
		//std::map<std::string, std::pair<MapSectorPropertyTemplate*, float>> listA;
		
		// map <weight, property>
		std::map<double, MapSectorPropertyTemplate*> listA;

		auto param = p->distance;

		// should be calculated randomly
		int paramCount = 1;

		for (int number(0); number < paramCount; number++)
		{
			float totalWeight = 0;

			for (auto prop(a->worldGeneratorData.sectorProperties.begin()); prop != a->worldGeneratorData.sectorProperties.end(); prop++)
			{
				auto weight = prop->second->getLocalProbability(param);
				if (weight >= 0.1)
				{
					//listA[prop->second->srcName].first = prop->second;
					//listA[prop->second->srcName].second = weight;					
					//listA[prop->second->srcName].second = totalWeight;
					totalWeight += weight;
					listA[totalWeight] = prop->second;
					
				}
			}

			double sRand = double(getRand()) / double(MAX_RAND_32);

			sRand = sRand * totalWeight;

			auto vProperty = listA.upper_bound(sRand);
			bool vCorrect = true;
			//vProperty->second->conflictProperties

			if (!vProperty->second->requiredProperties.empty())
			for (auto prop(vProperty->second->requiredProperties.begin()); prop != vProperty->second->requiredProperties.end(); prop++)
				if (p->vProperty.find(*prop) == p->vProperty.end())
				{
					vCorrect = false;
					break;
				}
			if (!vProperty->second->conflictProperties.empty())
			if (vCorrect)
				for (auto prop(vProperty->second->conflictProperties.begin()); prop != vProperty->second->conflictProperties.end(); prop++)
					if (p->vProperty.find(*prop) != p->vProperty.end())
					{
						vCorrect = false;
						break;
					}
			
			if (vCorrect)
			{
				p->vProperty[vProperty->second->srcName] = vProperty->second;

				// duplicates not allowed
				listA.erase(vProperty->first);
			}

		}

	}
 
}

void loadSectorPropertiesDB()
{

	// Base generation section

	MapSectorPropertyTemplate * p;
	
	p = new MapSectorPropertyTemplate();
	p->baseValue = 100;
	p->srcName = L"default";
	p->valueWeight = 100;
	p->valueDistribution = 5000;
	gEnv->game.adventureData.worldGeneratorData.sectorProperties[p->srcName] = p;

	p = new MapSectorPropertyTemplate();
	p->baseValue = 100;
	p->srcName = L"default2";
	p->valueWeight = 1000;
	p->valueDistribution = 5000;
	gEnv->game.adventureData.worldGeneratorData.sectorProperties[p->srcName] = p;

}

void loadSectorTemplatesDB()
{

	SectorTemplate * p;

	p = new SectorTemplate();
	//p->required.push_back();
	p->compatible.push_back(gEnv->game.adventureData.worldGeneratorData.sectorProperties[L"default"]);
	p->compatible.push_back(gEnv->game.adventureData.worldGeneratorData.sectorProperties[L"default2"]);
	p->filename = "\\resources\\scripts\\\World\\SectorTemplates\\Test2.esl";

	gEnv->game.adventureData.worldGeneratorData.sectorTemplates.push_back(p);

	p->script;
}

void worldGeneratorUpdate(double deltatime)
{
	
	if (gEnv->game.adventureData.worldGeneratorData.task == "init")
	{

		// Load generation resources

		loadSectorPropertiesDB();
		loadSectorTemplatesDB();

		//

		gEnv->game.adventureData.worldGeneratorData.task = "loadTemplates";
		
		gEnv->game.adventureData.worldGeneratorData.sector = gEnv->game.adventureData.sectors.begin();
		gEnv->game.adventureData.worldGeneratorData.templateId = 0;

	}

	if (gEnv->game.adventureData.worldGeneratorData.task == "loadTemplates")
	{
		
		if (gEnv->game.adventureData.worldGeneratorData.templateId < gEnv->game.adventureData.worldGeneratorData.sectorTemplates.size())
		{
			auto p = gEnv->game.adventureData.worldGeneratorData.sectorTemplates[gEnv->game.adventureData.worldGeneratorData.templateId];

			ScriptCompiler * c;
			ScriptDescriptor * q;
			std::string filename;

			filename = gEnv->game.workDir;
			filename += p->filename;
			c = new ScriptCompiler();
			q = c->compileFile(filename, p->familyId);
			delete(c);

			addScriptToQueue(q);

			gEnv->game.adventureData.worldGeneratorData.templateId++;
		}
		else
		{
			startWorldGeneration();
			gEnv->game.adventureData.worldGeneratorData.task = "processingSectors";
		}

	}

	//if (gEnv->load)

	if (gEnv->game.adventureData.worldGeneratorData.task == "processingSectors")
	{


		gEnv->game.adventureData.worldGeneratorData.task = "completed";
	}


	if (gEnv->game.adventureData.worldGeneratorData.task == "completed")
	{
		
		gEnv->game.gameAdventureGUIRequiresUpdate = true;
		gEnv->game.adventureUI.adventureUIDrawRequired = true;

		gEnv->game.activeGameMode = gameMode::adventureMode;

		gEnv->game.worldGeneratorRequiresUpdate = false;
		
		
	}



}
