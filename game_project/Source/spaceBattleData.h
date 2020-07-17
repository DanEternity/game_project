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
		maxLines = 12;
		maxLength = 20;

		state = "init";

	}

	sf::Sprite * mapSegment = NULL;
	sf::Sprite * mapSegmentHover = NULL;

	sf::Sprite * backgroundImage = NULL;

	float cameraX, cameraY;
	float scale = 2;


};
