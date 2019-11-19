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

namespace moduleType {
	enum ModuleType 
	{
		null,
	};
}

namespace equipmentType {
	enum EquipmentType
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
};

class Module : public ItemEquipable
{
public:
	moduleType::ModuleType moduleType;
	moduleSlot::ModuleSlotType slot;
	moduleSlot::ModuleSlotSize size;
};

class Equipment : public ItemEquipable
{
public:
	equipmentType::EquipmentType equipmentType;
};

class WeaponModule : public Module
{
public:
	
};
