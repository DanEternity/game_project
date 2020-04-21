#pragma once

//
// This file contain class definition of Template object for sector generation
//
//

#include <vector>

#include "baseObject.h"
#include "scriptTypes.h"
#include "mapSectorPropertyTemplate.h"


class SectorTemplate : public BaseObject
{
public:

	// this template requires following properties (tags)
	std::vector<MapSectorPropertyTemplate*> required;

	// this template compatible with following properties (tags)
	std::vector<MapSectorPropertyTemplate*> compatible;

	// Script to be called where sector template selected and ready to be initialized
	ScriptDescriptor * script;

	// Filename
	std::string filename;

	// FamilyId
	std::wstring familyId;

	SectorTemplate()
	{
		this->memoryControl = memoryControl::fixed;
		this->objectType = objectType::sectorTemplate;
	}
};