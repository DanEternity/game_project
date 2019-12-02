#pragma once

//
// Settings for world generation
// and chached generation info
//

class WorldGenerationData
{
public:
	std::map<std::string, MapSectorPropertyTemplate*> sectorProperties;
};