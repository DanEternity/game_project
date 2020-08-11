#pragma once

// this is for item recipes (templates, schemes)
// used fo crafting

#include "item.h"

namespace itemScheme
{

	enum Param
	{
		level,
		rarity
	};

	struct ResourceModifier
	{
		// This is specific rule, that apply change to default recipe if some certain params are in specific range

		// More clearly that used to modify recipes of modules that have high rarity or level

		itemScheme::Param targetParam;
		int minValue; // more or equal 
		int maxValue; // less or equal

		int targetResourceId; // if rule = true -> set resource id to this variable 
		int targetResourceCount; // if rule = true -> set resource count to this variable; still be modified by default price increment (from level and rarity)

	};

	struct RecipeComponent
	{
		
		int resourceIdBase; // 0 for null 
		int resourceCountBase; // 0 for 0 xd
		std::vector<ResourceModifier> modifierRules; // rules that change this recipe component

	};

}
class ItemScheme : public BaseObject
{
public:
	// crafting stats requirement
	float scienceMin;
	float engeneeringMin;
	float perceptionMin;

	// crafting resources requirement
	std::vector<itemScheme::RecipeComponent> recipe; // up to 6 resources can be used

	// crafting info
	int baseSchemeLevel;

	bool isStatic;	// static recipe will not be modified by any mechanics; This recipes is constant;
	
	int targetItemId; // resulting item id
	int targetItemKey;
	int targetItemRarity;
	int targetItemLevel;

	ItemScheme()
	{
		this->objectType = objectType::itemScheme;
	}

};