#pragma once

#include <map>
#include "item.h"

class ObjectStorage
{
public:
	int nextItemId = 0;
	std::map<int, Item*> items;

	int nextEffectId = 0;
	std::map<int, EffectObject*> effects;
};