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

	// Load generation resources

	loadSectorPropertiesDB();

	// point generation

	for (int i(0); i < maxGeneratedPoints; i++)
	{

		int x = getRand() % maxGalaxyRadius;
		int y = getRand() % maxGalaxyRadius;

		if ((x*x) + (y*y) > maxGalaxyRadius*maxGalaxyRadius)
			continue;

		MapSector * p = new MapSector();

		p->x = x;
		p->y = y;

		p->distance = sqrt((x*x) + (y*y));

		p->key = getRand64();

		a->sectors[std::to_string(p->key)] = p;

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

	//auto it = a->sectors.end();
	//it--;
	//printf("%llu \n", it->second->key);
	//uint64_t vKey = 0;
	//for (auto it(a->sectors.begin()); it != a->sectors.end(); it++)
	//{
	//	if (vKey < it->second->key)
	//		vKey = it->second->key;
	//}
	//printf("%llu \n", vKey);
	BuildMapUI();
}

void loadSectorPropertiesDB()
{

	// Base generation section

	MapSectorPropertyTemplate * p;
	
	p = new MapSectorPropertyTemplate();
	p->baseValue = 100;
	p->srcName = "default";
	p->valueWeight = 100;
	p->valueDistribution = 5000;
	gEnv->game.adventureData.worldGeneratorData.sectorProperties[p->srcName] = p;

	p = new MapSectorPropertyTemplate();
	p->baseValue = 100;
	p->srcName = "default2";
	p->valueWeight = 1000;
	p->valueDistribution = 5000;
	gEnv->game.adventureData.worldGeneratorData.sectorProperties[p->srcName] = p;

}
