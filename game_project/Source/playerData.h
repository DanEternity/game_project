#pragma once

//
// Player data
//

#include <vector>
#include "ship.h"

class PlayerData
{
public:
	
	// inventory // storage
	std::vector<Item *> inventory;

	// player ship
	Ship * ship;

};