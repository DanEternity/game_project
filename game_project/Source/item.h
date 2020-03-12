#pragma once

//
// This file contain item declaration
//
//
//

#include <string>
#include "baseObject.h"
#include "effect.h"
#include <TGUI/tGui.hpp>

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
		universal
	};
}

namespace moduleType {
	enum ModuleType
	{
		null,
		system,
		weapon,
		special
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
	tgui::Panel::Ptr tooltipDescription;
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

	std::vector<EffectObject*> effects;

	bool online;
	float powerSupply;
	float highPowerSupply;

	int powerPriority; // lower is better

	Module()
	{
		tooltipDescription = tgui::Panel::create();
		ItemEquipable();
		itemType = itemType::module;
		online = false;
		powerSupply = 0;
		powerPriority = 1;
		highPowerSupply = 0;
	}

	Module(std::wstring name, moduleType::ModuleType moduleType,
		moduleSlot::ModuleSlotType moduleSlot, moduleSlot::ModuleSlotSize moduleSize)
	{
		tooltipDescription = tgui::Panel::create();
		this->itemType = itemType::module;
		this->name = name;
		this->moduleType = moduleType;
		this->slot = moduleSlot;
		this->size = moduleSize;
	}
};

class Equipment : public ItemEquipable
{
public:
	equipmentType::EquipmentType equipmentType;
	equipmentSlot::EquipmentSlotType equipmentSlotType;

	Equipment()
	{
		ItemEquipable();
		itemType = itemType::equipment;
	}

	Equipment(std::wstring name, equipmentSlot::EquipmentSlotType type)
	{
		this->name = name;
		ItemEquipable();
		itemType = itemType::equipment;
		this->equipmentSlotType = type;
	}
};

class WeaponModule : public Module
{
public:

};
