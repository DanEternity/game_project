#pragma once


//
// Contain data about game logic and game variables
//
//

#include <map>
#include <vector>
#include <string>
#include "sectorData.h"
#include "worldGeneratorData.h"

class AdnvetureData
{
public:
	int gameTime = 0; // in game hours

	// all sectors
	std::map<std::string, MapSector*> sectors;	
	// Probably need to load/unload graphical resourses for map elements
	// cause having 10-20 objects for 500 sectors can use serious amount
	// of memory.
	// But in simple situation it doesn't need

	std::string currentSectorId = "null";

	// world to pixel coordinate conversion
	float settingMapScale = 2;

	WorldGenerationData worldGeneratorData;

	sf::Sprite * bgImage = NULL;

};