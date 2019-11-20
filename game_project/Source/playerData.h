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
	

};