#pragma once

#include "ship.h"

namespace segmentColor {

enum SegmentColor {
	base,
	player,
	enemy,
	neutral,
};

}
class SpaceBattleSegment
{
public:

	// center
	float gameX, gameY;

	// center
	float screenX, screenY;

	// ships located in this segment
	std::vector<Ship*> ships;

	segmentColor::SegmentColor color;

};