#pragma once

//
// Player data
//

#include <vector>
#include "ship.h"
#include "character.h"
#include "crewData.h"

class PlayerData
{
public:
	
	// inventory // storage
	std::vector<Item *> inventory;

	// player ship
	Ship * ship;

	CrewData crew;
	
	// Adventure ship position on sector (world coord)
	sf::Vector2f shipPosition = { 0, 0 };
	// camera position (world coord) // adventure ONLY
	sf::Vector2f cameraPosition = { 0, -600 };
};