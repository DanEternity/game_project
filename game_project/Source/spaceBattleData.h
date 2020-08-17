#pragma once

#include <vector>
#include "spaceBattleSegment.h"
#include "spaceBattleAnimationData.h"

namespace spaceBattleState
{
	enum SpaceBattleState
	{
		primary,
		targetingWeapon,
		animationFire,
		animationPostFire,
		animationMoving,
		endTurn,
		tacticsMode,
		waitForWeaponAnim,
	};
}

class SpaceBattleData
{
public:
	// O O O O
	//  O O O
	// O O O O
	
	std::vector<std::vector<SpaceBattleSegment * >> map; // segment map (hexes on battlefield)

	int maxLines; // initial battlefield size
	int maxLength;

	spaceBattleState::SpaceBattleState turnStatus; // this is battle current state
	
	std::string state; // this is GAMEMODE state (means loading, updating, idle etc)
	
	int turnNumber;

	std::vector<int> factionOrder; // factions make moves sequentially by an order described in this structure
	int currentFactionIndex; // vector index, not faction index
	std::string turnProcessingState = "null";

	int pickI = -1, pickJ = -1; // coordinates of cursor (Segment Coordinates)
	bool miniWindowCreated = false; // ship stats window (cursor hover)

	bool miniWindowEmptyCreated = false; // mini stats (for empty zones)

	int SelectI, SelectJ; // segment coordinates
	bool selected = false; // ship selected flag
	int SelectedShipId; // at ships[]

	bool showPath = false; // draw path flag
	std::vector<std::pair<int, int >> currentPath;

	WeaponModule * selectedWeaponModule = NULL;
	bool weaponModuleSelected = false;
	int weaponId = -1;

	// weapon use section (new)

	int srcI, srcJ, srcK;
	int dstI, dstJ, dstK;
	int srcWepId;

	// end


	bool leftMBPressed = false;
	bool rightMBPressed = false;

	int actionCooldown = 0;


	bool EndTurnPressed = false;

	int tacticsRange = 1;

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

	sf::Sprite * mapPathMarker = NULL;

	sf::Sprite * backgroundImage = NULL;

	std::vector<spaceBattleAnimationElement*> animElems;

	spaceBattleAnimationElement * waitForAnimElement = NULL;

	float cameraX, cameraY;
	float scale = 2;

	// UI handler
	tgui::Gui GUI;


};
