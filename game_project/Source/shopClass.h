#pragma once

#include "baseObject.h"
#include "item.h"
#include "character.h"
#include "ship.h"

struct selling
{
	Item* product;
	Item* itemPrice;
	int creditsPrice;
};

class Shop : BaseObject
{
public:
	std::vector<selling> resources;
	std::vector<selling> components;

	std::vector<selling> modules;
	std::vector<selling> modulePlanes;
	std::vector<selling> equipments;
	std::vector<selling> equipmentPlanes;

	std::vector<std::pair<Ship*, int>> ships;

	std::vector<std::pair<Character*, int>> characters;

	void addItemToShop(Item* product, Item* itemPrice, int creditsPrice)
	{
		selling newSell;
		newSell.product = product;
		newSell.itemPrice = itemPrice;
		newSell.creditsPrice = creditsPrice;
		switch (product->itemType)
		{
		case itemType::resource:
			resources.push_back(newSell);
			break;
		case itemType::module:
			modules.push_back(newSell);
			break;
		case itemType::equipment:
			equipments.push_back(newSell);
			break;
		}
	}

	void addCrewToShop(Character* c, int price)
	{
		std::pair<Character*, int> newPair;
		newPair.first = c;
		newPair.second = price;
		characters.push_back(newPair);
	}

	void addShipToShop(Ship* s, int price)
	{
		std::pair<Ship*, int> newPair;
		newPair.first = s;
		newPair.second = price;
		ships.push_back(newPair);
	}
};