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
		noneAspect = 0,
	};
}

namespace characterRole
{
	enum Role
	{
		noneRole,
		captain,
		scientist,
		engineer,
		pilot,
	};
}

class Character : public BaseObject
{
private:
	int treeCount = 0;
public:

	// common information

	std::wstring name;

	characterRole::Role characterClass;
	std::wstring characterRace;
	characterAspect::Aspect aspect = characterAspect::noneAspect;
	characterRole::Role role = characterRole::noneRole;
	
	// links

	std::vector<Equipment*> equipment;
	std::vector<equipmentSlot::EquipmentSlotType> slot;

	// stats

	std::map<statNames::StatName, Stat*> characterStats;
	std::vector<StatModEffectSkill*> skillForShip;

	bool haveRole = false;

	int level = 3;
	int skillPoints = 3;
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

	Stat Combat;
	Stat Science;
	Stat Adaptation;
	Stat Reflexes;
	Stat Engineering;
	Stat Perception;

	Stat Social;

	// skill tree stuff

	std::map<int, std::vector<PassiveSkill*>> skillTrees;

	Character(std::wstring name)
	{
		this->objectType = objectType::character;
		this->memoryControl = memoryControl::fixed;
		this->name = name;
		this->characterClass = characterRole::engineer;
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

		characterStats[statNames::characterCombat] = &Combat;
		characterStats[statNames::characterScience] = &Science;
		characterStats[statNames::characterAdaptation] = &Adaptation;
		characterStats[statNames::characterReflexes] = &Reflexes;
		characterStats[statNames::characterEngineering] = &Engineering;
		characterStats[statNames::characterPerception] = &Perception;

		characterStats[statNames::characterSocial] = &Social;


		equipment.resize(7, nullptr);

		std::vector<std::wstring> names;
		names.push_back(L"+10hp");
		names.push_back(L"+20hp");
		names.push_back(L"+30hp");
		names.push_back(L"+6%hull");
		names.push_back(L"+30powersupply");
		std::vector<int> skillLevels;
		skillLevels.push_back(1);
		skillLevels.push_back(1);
		skillLevels.push_back(2);
		skillLevels.push_back(3);
		skillLevels.push_back(3);
		std::vector<StatModEffectSkill*> effects;
		effects.push_back(new StatModEffectSkill(targetType::character, statNames::characterHealth, 10, 0, 0, 0, characterRole::noneRole));
		effects.push_back(new StatModEffectSkill(targetType::character, statNames::characterHealth, 20, 0, 0, 0, characterRole::noneRole));
		effects.push_back(new StatModEffectSkill(targetType::character, statNames::characterHealth, 30, 0, 0, 0, characterRole::noneRole));
		effects.push_back(new StatModEffectSkill(targetType::ship, statNames::hull, 0, 0.06, 0, 0, characterRole::noneRole));
		effects.push_back(new StatModEffectSkill(targetType::ship, statNames::powerSupply, 30, 0, 0, 0, characterRole::engineer));

		createNewTree(addPassives(names, skillLevels, effects));

		expToNextLevel[2] = 200.0f;
		expToNextLevel[3] = 300.0f;
		expToNextLevel[4] = 400.0f;
		expToNextLevel[5] = 500.0f;
		exp = 0.0f;
	}

	void createNewTree(std::vector<PassiveSkill*> passives)
	{
		skillTrees[treeCount++] = passives;
	}

	std::vector<PassiveSkill*> addPassives(std::vector<std::wstring> names, std::vector<int> levels, std::vector<StatModEffectSkill*> effects)
	{
		std::vector<PassiveSkill*> vct;
		if (names.size() != effects.size()) return vct;
		for (int i = 0; i < names.size(); i++)
		{
			PassiveSkill* skill = new PassiveSkill(names[i], levels[i]);
			skill->effect = effects[i];
			vct.push_back(skill);
		}
		return vct;
	}

	int classToInt(std::wstring persClass)
	{
		if (persClass == L"None")
			return 0;
	}
};

//// TEST CODE FOR BASE SKILL TREE

/*switch (classToInt(characterClass))
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

skillTrees[0] = vct;
break;
}*/