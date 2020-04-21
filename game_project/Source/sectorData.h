#pragma once

//
// This file contain sector data
//
//
//

#include "mapObjectsData.h"
#include "mapSectorPropertyTemplate.h"

class MapSector : public BaseObject
{
public:
	std::vector<MapMarker*> markers;
	std::vector<MapDecoration*> objects;

	// generation property
	std::map<std::wstring, MapSectorPropertyTemplate*> vProperty;

	// region name
	std::string regionName;

	// sector coordinates // integer because pixel coordinates int anyway
	int x;
	int y;

	// distance to center
	int distance;

	// unique key value
	int key;

	// background
	std::wstring backgroundImage;

	MapSector()
	{
		this->objectType = objectType::mapSector;
	}
};

