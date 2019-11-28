#pragma once

#include "baseObject.h"
#include <SFML/Graphics.hpp>

//
// This file contain classes for adventure map objects
//
//

class MapMarker : public BaseObject
{
public:
	// position in WORLD coordinates (not in pixel)
	sf::Vector2f pos;

	MapMarker()
	{
		this->objectType = objectType::mapMarker;
	}
};

class MapDecoration : public BaseObject
{
public:
	// position in WORLD coordinates (not in pixel)
	sf::Vector2f pos;
	std::wstring model;
	sf::Vector2f scale;
	float rotation;

	sf::Sprite * sprite = NULL;

	MapDecoration()
	{
		this->objectType = objectType::mapDecoration;
	}
};

class MapSector : public BaseObject
{
public:
	std::vector<MapMarker*> markers;
	std::vector<MapDecoration*> objects;


	MapSector()
	{
		this->objectType = objectType::mapSector;
	}
};