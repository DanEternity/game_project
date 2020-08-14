#pragma once

//
// Player data
//

#include <vector>
#include <string>
#include "ship.h"
#include "character.h"
#include "crewData.h"
#include "plan.h"

class IntventoryFilter
{
public:
	std::wstring searchString;
	
	std::set<itemType::ItemType> itemType;
	std::set<moduleSlot::ModuleSlotType> moduleSlotType;
	std::set<equipmentType::EquipmentType> equipmentType;

	// add other filters if needed
};

namespace shipMenu {

	enum ShipMenu
	{
		null, // window closed
		ship,
		lab,
		crew,
		craft,
		storage,
		stats,
		hangar,
		map
	};

}

class PlayerData
{
public:
	
	// inventory // storage
	std::vector<Item *> inventory;

	// temp inventory // view
	std::vector<int> localInventory;

	// temp inventory for rewards
	std::vector<Item *> rewardInventory;

	// filter condition
	IntventoryFilter inventoryFilter;

	// list of all known plans
	std::vector<Plan*> planList;

	// player ship
	Ship * ship;
	sf::Sprite * shipModel = NULL;
	sf::Sprite * shipModelIdle = NULL;
	sf::Sprite * shipModelMove = NULL;
	bool PlayerShipMoving = false;
	float shipAngle = 0;
	CrewData crew;
	Character * captain;

	int hangarSize = 4;
	std::vector<Ship*> fighterPlanes;
	
	// Adventure ship position on sector (world coord)
	sf::Vector2f shipPosition = { 0, 0 };
	// camera position (world coord) // adventure ONLY
	sf::Vector2f cameraPosition = { 0, -600 };

	float cameraSpeed = 250;
	
	double HeavyUpdateTime = 0;

	// UI section
	// current ship menu
	shipMenu::ShipMenu shipMenu = shipMenu::null;

	// Item picked by item selection
	Item * pickedItem = NULL;
	int pickedLocalInventory = -1; // NULL
	int pickedItemInvId = -1; // NULL


	// stats

	int money = 200;

	// controls
	float mouseWheelDelta = 0;

};