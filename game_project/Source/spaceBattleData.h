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

	int turnNumber;

	std::vector<int> factionOrder; // factions make moves sequentially by an order described in this structure
	int currentFactionIndex; // vector index, not faction index
	std::string turnProcessingState = "null";

	SpaceBattleData()
	{
		maxLines = 12;
		maxLength = 20;
		
		turnNumber = 1;

		state = "init";

	}

	// graphics section
	sf::Sprite * mapSegment = NULL;
	sf::Sprite * mapSegmentHover = NULL;
	sf::Sprite * mapSegmentPlayer = NULL;
	sf::Sprite * mapSegmentEnemy = NULL;
	sf::Sprite * mapSegmentNeutral = NULL;

	sf::Sprite * backgroundImage = NULL;

	float cameraX, cameraY;
	float scale = 2;

	// UI handler
	tgui::Gui GUI;

};
