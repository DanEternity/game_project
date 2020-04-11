#pragma once

#include "baseObject.h"
#include "item.h"
#include "stat.h"
#include "effect.h"
#include <vector>

namespace characterAspect
{
	enum Aspect
	{
		noneAspect,
	};
}

namespace characterRole
{
	enum Role
	{
		noneRole,
	};
}

class Character : public BaseObject
{
public:

	// common information

	std::wstring name;

	std::wstring characterClass;
	std::wstring characterRace;
	characterAspect::Aspect aspect = characterAspect::noneAspect;
	characterRole::Role role = characterRole::noneRole;
	
	// links

	std::vector<Equipment*> equipment;
	std::vector<equipmentSlot::EquipmentSlotType> slot;

	// stats

	std::map<statNames::StatName, Stat*> characterStats;
	std::map<statNames::StatName, Stat*> statsForShip;

	int level;
	float exp;
	std::map<int, float> expToNextLevel;
	Stat health;
	Stat armor;
	Stat shield;
	Stat block;

	Stat resist;
	Stat ShieldReg;

	Stat actionPoints;
	Stat energy;
	Stat energyReg;

	Stat initiative;

	// skill tree stuff

	std::map<std::wstring, std::map<StatModEffect*, bool>> skillTreePassives;

	Character(std::wstring name)
	{
		this->name = name;
		this->characterClass = L"None";
		this->characterRace = L"Human";
		this->health.baseValue = 100;
		slot.resize(7);
		slot[0] = equipmentSlot::head;
		slot[1] = equipmentSlot::body;
		slot[2] = equipmentSlot::arms;
		slot[3] = equipmentSlot::legs;
		slot[4] = equipmentSlot::universal;
		slot[5] = equipmentSlot::universal;
		slot[6] = equipmentSlot::universal;

		characterStats[statNames::characterHealth] = &health;
		characterStats[statNames::characterArmor] = &armor;
		characterStats[statNames::characterShield] = &shield;
		characterStats[statNames::characterBlock] = &block;
		characterStats[statNames::characterResist] = &resist;
		characterStats[statNames::characterShieldReg] = &ShieldReg;
		characterStats[statNames::characterActionPoints] = &actionPoints;
		characterStats[statNames::characterEnergy] = &energy;
		characterStats[statNames::characterEnergyReg] = &energyReg;
		characterStats[statNames::characterInitiative] = &initiative;

		equipment.resize(7, nullptr);
	}
};