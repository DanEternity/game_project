#pragma once

#include "baseObject.h"
#include "item.h"
#include <vector>

class Person : BaseObject
{
public:
	std::vector<Equipment*> personEquipment;
};