#pragma once

//
// This file contain item declaration
//
//
//

#include <string>
#include "baseObject.h"

namespace itemType {
	enum ItemType
	{

		null,
		module = 1,
		equipment,

	};
} // itemType

namespace itemModifier {
	enum ItemModifier
	{
		broken,
		bad,
		normal,
		upgrade1,
		upgrade2,
		legendary

	};
}



namespace equipmentType {
	enum EquipmentType
	{
		null,
	};
}

namespace equipmentSlot {
	enum EquipmentSlotType
	{
		null = -1,
		head,
		body,
		arms,
		legs,
	};
}

namespace moduleType {
	enum ModuleType
	{
		null,
	};
}

namespace moduleSlot {
	enum ModuleSlotType
	{
		null = -1,
		core = 0,
		hyperdrive,
		engine,
		system,
		primaryWeapon,
		secondaryWeapon,
		universal,
	};
	enum ModuleSlotSize
	{
		small,
		medium,
		large,
		huge,
	};
	struct ModuleSlot {
		ModuleSlotType type;
		ModuleSlotSize size;
	};
}

class Item : public BaseObject
{
public:
	int level;
	int rarity;
	int itemId;
	itemType::ItemType itemType;
	std::wstring name;
	Item()
	{
		itemType = itemType::null;
	}
};

class ItemConstructable : public Item
{
public:
	// Constructor constructor;
	__int64 key;
	int quality;
	itemModifier::ItemModifier modifier;
};

class ItemEquipable : public ItemConstructable
{
public:
	ItemEquipable()
	{
		ItemConstructable();
		itemType = itemType::equipment;
	}
};

class Module : public ItemEquipable
{
public:
	moduleType::ModuleType moduleType;
	moduleSlot::ModuleSlotType slot;
	moduleSlot::ModuleSlotSize size;
	Module()
	{
		ItemEquipable();
		itemType = itemType::module;
	}
};

class Equipment : public ItemEquipable
{
public:
	equipmentType::EquipmentType equipmentType;
	equipmentSlot::EquipmentSlotType equipmentSlotType;
};

class WeaponModule : public Module
{
public:
	
};