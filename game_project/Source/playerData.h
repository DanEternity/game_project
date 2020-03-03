#pragma once

//
// Player data
//

#include <vector>
#include <string>
#include "ship.h"
#include "character.h"
#include "crewData.h"

class IntventoryFilter
{
public:
	std::wstring searchString;
	std::set<itemType::ItemType> itemType;
	// add other filters if needed
};

class PlayerData
{
public:
	
	// inventory // storage
	std::vector<Item *> inventory;

	// temp inventory // view
	std::vector<int> localInventory;

	// filter condition
	IntventoryFilter inventoryFilter;

	// player ship
	Ship * ship;

	CrewData crew;
	
	// Adventure ship position on sector (world coord)
	sf::Vector2f shipPosition = { 0, 0 };
	// camera position (world coord) // adventure ONLY
	sf::Vector2f cameraPosition = { 0, -600 };
};