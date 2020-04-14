#pragma once

#include <map>
#include "poolObject.h"
#include "item.h"

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
};