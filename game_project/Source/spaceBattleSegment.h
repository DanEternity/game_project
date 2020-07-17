#pragma once

#include "ship.h"

class SpaceBattleSegment
{
public:

	// center
	float gameX, gameY;

	// center
	float screenX, screenY;

	// ships located in this segment
	std::vector<Ship*> ships;



};