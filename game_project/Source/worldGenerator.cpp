#include "worldGenerator.h"

void startWorldGeneration()
{

	// initiate generation parameters

	const int maxGeneratedPoints = 1000;
	const int maxGalaxyRadius = 4000;

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

	}

	printf("(World generator log) Initial generation: %i points\n", points.size());

}
