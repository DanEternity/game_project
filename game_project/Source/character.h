#pragma once

#include "baseObject.h"
#include "item.h"
#include "stat.h"
#include "effect.h"
#include "passiveSkill.h"
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
		captain,

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
	std::vector<StatModEffect*> effectsForShip;

	bool haveRole = false;

	int level = 2;
	int skillPoints = 1;
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

	std::map<std::wstring, std::vector<PassiveSkill*>> skillTrees;

	Character(std::wstring name)
	{
		this->name = name;
		this->characterClass = L"Noe";
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

		switch (classToInt(characterClass))
		{
		case 0:
			std::vector<PassiveSkill*> vct;

			PassiveSkill* skill = new PassiveSkill(L"+10 hp", 1);
			skill->effect = new StatModEffect();
			skill->effect->targetType = targetType::character;
			skill->effect->statName = statNames::characterHealth;
			skill->effect->p_add = 10;
			vct.push_back(skill);

			skill = new PassiveSkill(L"+20 hp", 1);
			skill->effect = new StatModEffect();
			skill->effect->targetType = targetType::character;
			skill->effect->statName = statNames::characterHealth;
			skill->effect->p_add = 20;
			vct.push_back(skill);

			skill = new PassiveSkill(L"+30 hp", 2);
			skill->effect = new StatModEffect();
			skill->effect->targetType = targetType::character;
			skill->effect->statName = statNames::characterHealth;
			skill->effect->p_add = 30;
			vct.push_back(skill);

			skill = new PassiveSkill(L"+6% hull", 3);
			skill->effect = new StatModEffect();
			skill->effect->targetType = targetType::ship;
			skill->effect->statName = statNames::hull;
			skill->effect->p_mul = 0.06;
			vct.push_back(skill);

			skill = new PassiveSkill(L"+30 power supply", 3);
			skill->effect = new StatModEffect();
			skill->effect->targetType = targetType::ship;
			skill->effect->statName = statNames::powerSupply;
			skill->effect->p_add = 30;
			vct.push_back(skill);

			skillTrees[L"classicTree"] = vct;
			break;
		}
	}

	int classToInt(std::wstring persClass)
	{
		if (persClass == L"None")
			return 0;
	}
};