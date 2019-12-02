#include "worldGenerator.h"

void startWorldGeneration()
{

	// initiate generation parameters

	const int maxGeneratedPoints = 1200;
	const int maxGalaxyRadius = 4000;

	gEnv->game.randTmp = gEnv->game.worldSeed;

	//const int 

	std::vector<MapSector*> points;

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

		gEnv->game.adventureData.sectors[std::to_string(p->key)] = p;

	}

	printf("(World generator log) Initial generation: %li points\n", points.size());

	// region generation

	// not used yet



}
