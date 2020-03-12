#pragma once

#include "baseObject.h"
#include "item.h"
#include <vector>

class Character : public BaseObject
{
public:

	// common information

	std::wstring name;
	
	// links

	std::vector<Equipment*> equipment;
	std::vector<equipmentSlot::EquipmentSlotType> slot;

	// stats

	Character(std::wstring name)
	{
		this->name = name;
		slot.resize(7);
		slot[0] = equipmentSlot::head;
		slot[1] = equipmentSlot::body;
		slot[2] = equipmentSlot::arms;
		slot[3] = equipmentSlot::legs;
		slot[4] = equipmentSlot::universal;
		slot[5] = equipmentSlot::universal;
		slot[6] = equipmentSlot::universal;

		equipment.resize(7, nullptr);
	}
};