#pragma once

//
// This file contain item declaration
//
//
//

#include <string>
#include "baseObject.h"
#include "stat.h"
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
	tgui::Panel::Ptr tooltipDescription; // Panel with description of module
	bool tooltipWasCreated = false;
	sf::Texture* icon;
	Item()
	{
		objectType = objectType::item;
		itemType = itemType::null;
		itemClass = "Not defined";
		icon = NULL;
	}
};

class ItemConstructable : public Item
{
public:
	// Constructor constructor;
	int key;
	int quality;
	itemModifier::ItemModifier modifier;

	float positiveMultiplier;
	float negativeMultiplier;

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

	Stat powerSupply;
	Stat highPowerSupply;

	int powerPriority; // lower is better

	Module() : ItemEquipable()
	{
		tooltipDescription = tgui::Panel::create();
		ItemEquipable();
		itemType = itemType::module;
		memoryControl = memoryControl::fixed;
		moduleType = moduleType::system;
		online = false;
		powerSupply.baseValue = 0;
		powerPriority = 1;
		highPowerSupply.baseValue = 0;
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

	void CalcPowerSupply()
	{
		powerSupply.clear();
		highPowerSupply.clear();

		for (int i(0); i<effects.size(); i++)
			if (effects[i] != NULL)
			{
				if (effects[i]->effectGroup == effectGroups::statModifier)
				{
					StatModEffect * p = static_cast<StatModEffect*>(effects[i]);
					if (p->targetType == targetType::module)
					{
						if (p->statName == statNames::modulePowerConsumption)
						{
							powerSupply.increment += p->p_add;
							powerSupply.multiplier += p->p_mul;
							powerSupply.decrement += p->p_sub;
							powerSupply.debuffMultiplier *= (1 - p->p_negMul);
						}
						if (p->statName == statNames::moduleHighPowerConsumption)
						{
							highPowerSupply.increment += p->p_add;
							highPowerSupply.multiplier += p->p_mul;
							highPowerSupply.decrement += p->p_sub;
							highPowerSupply.debuffMultiplier *= (1 - p->p_negMul);
						}
					}
				}

			}

		powerSupply.calcTotal();
		highPowerSupply.calcTotal();
		powerSupply.total = std::max(0.0f, powerSupply.total);
		highPowerSupply.total = std::max(0.0f, highPowerSupply.total);
	}

};

class Equipment : public ItemEquipable
{
public:
	equipmentType::EquipmentType equipmentType;
	equipmentSlot::EquipmentSlotType equipmentSlotType;

	std::vector<EffectObject*> effects;

	Equipment() : ItemEquipable()
	{
		tooltipDescription = tgui::Panel::create();
		itemType = itemType::equipment;
		this->memoryControl = memoryControl::fixed;
	}

	Equipment(std::wstring name, equipmentSlot::EquipmentSlotType type) : ItemEquipable()
	{
		tooltipDescription = tgui::Panel::create();
		this->name = name;
		itemType = itemType::equipment;
		this->memoryControl = memoryControl::fixed;
		this->equipmentSlotType = type;
	}
};

class WeaponModule : public Module
{
public:
/*  reference
	int fullCooldown; // Amount of round required to refill ActivationLimit
	int activationsLimit; // Amount of activation this weapon can perform until full cooldown required
	int activationsPartial; // Amount of activation this weapon can perform before partial cooldown (usually 1-2 per round)
	int partialCooldown; // Required when activationsPartial exceeded (usually 1) (if 0 this mean that weapon does not have partial CD)

	int activationsRemainingPartial; // Until partial CD
	int activationsRemainingFull; // Until full cooldown

	float baseDamage; // Damage of single hit of this weapon
	int projectilesAmount; // Amount of projectiles per activation (Even if weapon laser type) cannot be 0;
	// full damage per activation = baseDamage * projectilesAmount;

	int damageType; // 0 - null, 1 - physical, 2 - energy;

	float optimalDistance;
	float accuracy; // raw value - accuracy will degrade based on distance
	float damagePenalty; // when out of optimal range per one unit of distance
	float accuracyPenalty; // when out of optimal range per one unit of distance

	float resistanceIgnoreHullFlat; // - resistance
	float resistanceIgnoreHullPercent; // - %resistance

	float resistanceIgnoreShieldFlat;
	float resistanceIgnoreShieldPercent;

	float criticalChanceHull; // chance 1.0 = 100%
	float criticalDamageHull; // multiplier 1.0 = +100%

	float criticalChanceShield;
	float criticalDamageShield;

	int weaponAmmo; // current
	int weaponMaxAmmo; // (zero if ammo not used) (weapon always required 1 ammo per activation regardless of projectile count)
*/

	Stat fullCooldown; // Amount of round required to refill ActivationLimit
	Stat activationsLimit; // Amount of activation this weapon can perform until full cooldown required
	Stat activationsPartial; // Amount of activation this weapon can perform before partial cooldown (usually 1-2 per round)
	Stat partialCooldown; // Required when activationsPartial exceeded (usually 1) (if 0 this mean that weapon does not have partial CD)

	Stat activationsRemainingPartial; // Until partial CD
	Stat activationsRemainingFull; // Until full cooldown

	Stat baseDamage; // Damage of single hit of this weapon
	Stat projectilesAmount; // Amount of projectiles per activation (Even if weapon laser type) cannot be 0;
						   // full damage per activation = baseDamage * projectilesAmount;
	int damageType; // 0 - null, 1 - physical, 2 - energy;

	Stat optimalDistance;
	Stat accuracy; // raw value - accuracy will degrade based on distance
	Stat damagePenalty; // when out of optimal range per one unit of distance
	Stat accuracyPenalty; // when out of optimal range per one unit of distance

	Stat resistanceIgnoreHullFlat; // - resistance
	Stat resistanceIgnoreHullPercent; // - %resistance

	Stat resistanceIgnoreShieldFlat;
	Stat resistanceIgnoreShieldPercent;

	Stat criticalChanceHull; // chance 1.0 = 100%
	Stat criticalDamageHull; // multiplier 1.0 = +100%

	Stat criticalChanceShield;
	Stat criticalDamageShield;
	
	Stat weaponAmmoMax; // (zero if ammo not used) (weapon always required 1 ammo per activation regardless of projectile count)
	int weaponAmmo; // current
	int activations;
	int cooldownPartial;
	int cooldownFull;
	int weaponState; // change to ENUM

	WeaponModule() : Module()
	{
		moduleType = moduleType::weapon;
	}

	Stat * getStat(statNames::StatName statName)
	{
		auto p = statName;
		switch (p)
		{
		case statNames::weaponFullCooldown:
			return &fullCooldown;
			break;
		case statNames::weaponActivationsLimit:
			return &activationsLimit;
			break;
		case statNames::weaponActivationsPartial:
			return &activationsPartial;
			break;
		case statNames::weaponPartialCooldown:
			return &partialCooldown;
			break;
		case statNames::weaponActivationsRemainingPartial:
			return &activationsRemainingPartial;
			break;
		case statNames::weaponActivationsRemainingFull:
			return &activationsRemainingFull;
			break;
		case statNames::weaponBaseDamage:
			return &baseDamage;
			break;
		case statNames::weaponProjectilesAmount:
			return &projectilesAmount;
			break;
		case statNames::weaponOptimalDistance:
			return &optimalDistance;
			break;
		case statNames::weaponAccuracy:
			return &accuracy;
			break;
		case statNames::weaponDamagePenalty:
			return &damagePenalty;
			break;
		case statNames::weaponAccuracyPenalty:
			return &accuracyPenalty;
			break;
		case statNames::weaponResistanceIgnoreHullFlat:
			return &resistanceIgnoreHullFlat;
			break;
		case statNames::weaponResistanceIgnoreHullPercent:
			return &resistanceIgnoreHullPercent;
			break;
		case statNames::weaponResistanceIgnoreShieldFlat:
			return &resistanceIgnoreShieldFlat;
			break;
		case statNames::weaponResistanceIgnoreShieldPercent:
			return &resistanceIgnoreShieldPercent;
			break;
		case statNames::weaponCriticalChanceHull:
			return &criticalChanceHull;
			break;
		case statNames::weaponCriticalDamageHull:
			return &criticalDamageHull;
			break;
		case statNames::weaponCriticalChanceShield:
			return &criticalChanceShield;
			break;
		case statNames::weaponCriticalDamageShield:
			return &criticalDamageShield;
			break;
		case statNames::weaponWeaponAmmoMax:
			return &weaponAmmoMax;
			break;
		default:
			return NULL;
			break;
		}
	}

};

class ItemResource : public Item
{
public:
	
	int count;
	int maxCount;

	ItemResource() : Item()
	{
		memoryControl = memoryControl::fixed;
		tooltipDescription = tgui::Panel::create();
		itemType = itemType::resource;
	}
};