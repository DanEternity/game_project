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
		resource,

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

namespace itemClass {

	enum ItemClass
	{
		null,
		miscellaneos, // category not specified
		// ship modules section
		core,
		hyperdrive,
		engine,
		system,
		shieldGenerator,
		shieldAmplifier, // req shieldGenerator
		sensorSystem,
		sensorAmplifier, // req sensor

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
	int level; // level of item; used in generation
	int rarity; // rarity of item; used in generation
	int itemId;
	itemType::ItemType itemType;
	std::string itemClass; // item class for dependecies
	std::wstring name;
	tgui::Panel::Ptr tooltipDescription; // owo what's this?
	Item()
	{
		objectType = objectType::item;
		itemType = itemType::null;
		itemClass = "Not defined";
	}
};

class ItemConstructable : public Item
{
public:
	// Constructor constructor;
	int key;
	int quality;
	itemModifier::ItemModifier modifier;

	ItemConstructable() : Item()
	{

	}

};

class ItemEquipable : public ItemConstructable
{
public:
	ItemEquipable() : ItemConstructable()
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

	Module() : ItemEquipable()
	{
		tooltipDescription = tgui::Panel::create();
		ItemEquipable();
		itemType = itemType::module;
		memoryControl = memoryControl::fixed;
		moduleType = moduleType::system;
		online = false;
		powerSupply = 0;
		powerPriority = 1;
		highPowerSupply = 0;
	}

	Module(std::wstring name, moduleType::ModuleType moduleType,
		moduleSlot::ModuleSlotType moduleSlot, moduleSlot::ModuleSlotSize moduleSize) : ItemEquipable()
	{
		tooltipDescription = tgui::Panel::create();
		this->itemType = itemType::module;
		this->memoryControl = memoryControl::fixed;
		this->moduleType = moduleType::system;
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

	Equipment() : ItemEquipable()
	{
		itemType = itemType::equipment;
	}

	Equipment(std::wstring name, equipmentSlot::EquipmentSlotType type) : ItemEquipable()
	{
		this->name = name;
		itemType = itemType::equipment;
		this->equipmentSlotType = type;
	}
};

class WeaponModule : public Module
{
public:

};

class ItemResource : public Item
{
public:
	
	int count;
	int maxCount;

	ItemResource() : Item()
	{
		memoryControl = memoryControl::fixed;
		itemType = itemType::resource;
	}
};