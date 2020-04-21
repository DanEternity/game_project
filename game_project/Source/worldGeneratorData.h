#pragma once

//
// Settings for world generation
// and chached generation info
//

#include "mapSectorPropertyTemplate.h"
#include "sectorGeneratorTemplate.h"

class WorldGenerationData
{
public:
	std::map<std::wstring, MapSectorPropertyTemplate*> sectorProperties;

	std::vector<SectorTemplate*> sectorTemplates;

	std::string task = "";

	std::map<std::string, MapSector*>::iterator sector;

	int templateId = 0;
};