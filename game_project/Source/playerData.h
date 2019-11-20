#pragma once

//
// Player data
//

#include <vector>
#include "ship.h"
#include "crew.h"

class PlayerData
{
public:
	
	// inventory // storage
	std::vector<Item *> inventory;

	// player ship
	Ship * ship;

	Crew * crew;
};