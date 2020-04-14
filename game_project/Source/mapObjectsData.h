#pragma once

#include "baseObject.h"
#include "scriptTypes.h"
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
	ScriptDescriptor * sd; // script link

	//sf::Vector2f pos;
	//sf::Vector2f scale;

	sf::Sprite * sprite = NULL;

	MapMarker()
	{
		this->memoryControl = memoryControl::fixed;
		this->objectType = objectType::mapMarker;
	}

	MapMarker(sf::Vector2f pos)
	{
		this->memoryControl = memoryControl::fixed;
		this->objectType = objectType::mapMarker;
		this->pos = pos;
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
		this->memoryControl = memoryControl::fixed;
		this->objectType = objectType::mapDecoration;
	}
};

