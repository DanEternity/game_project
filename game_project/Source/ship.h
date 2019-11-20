#pragma once


//
// This file contain ship object
//
// This file should not include enviroment.h
//

#include <vector>
#include "baseObject.h"
#include "item.h"
#include "character.h"

class Ship : public BaseObject
{
public:

	// links section

	std::vector<Module*> modules;
	std::vector<moduleSlot::ModuleSlot> slots;

	// links to characters binded to this ship
	// this vector does not represent all characters available for player control
	// only characters that affect this ship stats and functions
	std::vector<Character*> crew;

	// stats section

	/* here goes various stats of the ship. Example energy, defenses, hull etc... */

};
