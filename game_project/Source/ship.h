#pragma once


//
// This file contain ship object
//
// This file should not include enviroment.h
//

#include <vector>
#include "baseObject.h"
#include "item.h"

class Ship : BaseObject
{

	// links section

	std::vector<Module*> modules;
	std::vector<moduleSlot::ModuleSlot> slots;

	// stats section

	/* here goes various stats of the ship. Example energy, defenses, hull etc... */

};
