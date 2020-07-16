#pragma once

#include <vector>
#include "spaceBattleSegment.h"

class SpaceBattleData
{
public:
	// O O O O
	//  O O O
	// O O O O
	
	std::vector<std::vector<SpaceBattleSegment * >> map;

	int maxLines;
	int maxLength;

	std::string state;

	SpaceBattleData()
	{
		maxLines = 8;
		maxLength = 8;

		state = "init";

	}

	sf::Sprite * mapSegment = NULL;
	sf::Sprite * mapSegmentHover = NULL;

	float cameraX, cameraY;

};
