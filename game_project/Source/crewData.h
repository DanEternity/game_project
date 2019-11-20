#pragma once

#include "character.h"

class CrewData
{
public:

	// this vector contain all characters available for player control
	// other characters cant be controlled
	std::vector<Character*> characters;


};