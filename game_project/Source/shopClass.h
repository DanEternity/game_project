#pragma once

#include "baseObject.h"
#include "item.h"
#include "character.h"
#include "ship.h"

struct Goods
{
	int stock; // 1 if not resource
	Item* product; // resulting item - player will get it
	Item* itemPrice; // item price - player will lose it
	int creditsPrice; // alternative price in credits

};

class Shop : public BaseObject
{
public:

	std::wstring label;

	std::vector<Goods> resources;
	std::vector<Goods> components;

	std::vector<Goods> modules;
	std::vector<Goods> moduleSchemes;
	std::vector<Goods> equipments;
	std::vector<Goods> equipmentSchemes;

	std::vector<std::pair<Ship*, int>> ships;

	std::vector<std::pair<Character*, int>> characters;

	void addItemToShop(Item* product, Item* itemPrice, int creditsPrice)
	{
		Goods newSell;
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

	Shop() : BaseObject()
	{
		this->objectType = objectType::shop;
		this->memoryControl = memoryControl::fixed;
	}

};