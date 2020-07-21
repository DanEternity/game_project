#pragma once

#include <map>
#include "poolObject.h"
#include "item.h"
#include "shopClass.h"

class ObjectStorage
{
public:
	int nextItemId = 0;
	std::map<int, Item*> items;

	int nextEffectId = 0;
	std::map<int, EffectObject*> effects;

	int nextPoolId = 0;
	std::map<int, PoolObject*> pools;

	int nextSkillId = 0;
	std::map<int, PassiveSkill*> skills;

	int nextDecor = 0;
	std::map<int, MapDecoration*> decor;

	int nextCharId = 0;
	std::map<int, Character*> characters;

	int nextShopId = 0;
	std::map<int, Shop*> shops;

};