#pragma once

//
//
//	This file contain "effect object" implementation
//	
//

#include "baseObject.h"
#include <string>
#include "character.h"

namespace effectGroups {

	enum EffectGroup {
		null,
		statModifier, // change specific stat	
	};

}


namespace statNames {

	// this contain ALL names;
	// it may not work for specific objects and should be ignored then

	enum StatName {

		null = 0,


		powerSupply, // ship energy for module operation
		highPowerSupply, // ship energy for module operation
		actionPoints, // ship power condensator capacity

		// defence stats
		hull,
		hullResistPhysical,
		hullResistEnergy,
		hullReg,
		hullStructureStability,
		shield,
		shieldResistPhysical,
		shieldResistEnergy,
		shieldReg,
		shieldStructureStability,

		evasion,
		mobility,
		stealth,
		stealthTier,
		sensorPower,
		sensorTier,
		missileDefense,
		missileDefenseTier,

		// hyperdrive 
		hyperDrivePower,
		hyperDriveTier,
		hyperDriveFuelEfficiency,

		additionalWeaponAccuracy,
		totalDamageMultiplier, // output damage multiplier

		fuel, // hyperdrive fuel

		//character stats

		characterHealth,
		characterArmor,
		characterShield,
		characterBlock,
		characterResist,
		characterShieldReg,
		characterActionPoints,
		characterEnergy,
		characterEnergyReg,
		characterInitiative,

		characterCombat,
		characterScience,
		characterAdaptation,
		characterReflexes,
		characterEngineering,
		characterPerception,

		characterSocial,

		// weapon module stat

		weaponActivationCost, // amount of ActionPoint required to fire with this weapon

		weaponFullCooldown, // Amount of round required to refill ActivationLimit
		weaponActivationsLimit, // Amount of activation this weapon can perform until full cooldown required
		weaponActivationsPartial, // Amount of activation this weapon can perform before partial cooldown (usually 1-2 per round)
		weaponPartialCooldown, // Required when activationsPartial exceeded (usually 1) (if 0 this mean that weapon does not have partial CD)

		weaponBaseDamage, // Damage of single hit of this weapon
		weaponProjectilesAmount, // Amount of projectiles per activation (Even if weapon laser type) cannot be 0,
								// full damage per activation = baseDamage * projectilesAmount,


		weaponOptimalDistance,
		weaponAccuracy, // raw value - accuracy will degrade based on distance
		weaponDamagePenalty, // when out of optimal range per one unit of distance
		weaponAccuracyPenalty, // when out of optimal range per one unit of distance

		weaponResistanceIgnoreHullFlat, // - resistance
		weaponResistanceIgnoreHullPercent, // - %resistance

		weaponResistanceIgnoreShieldFlat,
		weaponResistanceIgnoreShieldPercent,

		weaponCriticalChanceHull, // chance 1.0 = 100%
		weaponCriticalDamageHull, // multiplier 1.0 = +100%

		weaponCriticalChanceShield,
		weaponCriticalDamageShield,

		weaponAmmoMax, // (zero if ammo not used) (weapon always required 1 ammo per activation regardless of projectile count)

		weaponChargeActivationCost,
		weaponChargeFinalCost,
		weaponChargeRoundsCount,



		weaponMissileHealth, // def against flak
		weaponMissileTier, // def against flak tier

		// module

		modulePowerConsumption,
		moduleHighPowerConsumption,

	};

}

namespace targetType {

	enum TargetType {
		ship,
		character,
		module,
	};

}


class EffectObject : public BaseObject
{
public:
	std::wstring text = L"";	// visual effect description
								// Can be empty or have partial info
								// Will be displayed in effect description

	effectGroups::EffectGroup effectGroup; // effect family


	int effectId = 0;	// indicates effect internal ID
						// Does not required to be filled
						// But can be used by some mechanics
						// where only true/false 
						// (exist/not exist) data is 
						// important

	EffectObject()
	{
		this->objectType = objectType::effect;
		this->memoryControl = memoryControl::fixed;
	}

};

class StatModEffect : public EffectObject
{
public:
	// effectGroup = statModifier

	targetType::TargetType targetType; // entity type name // ship, character... etc
	
	statNames::StatName statName;

	float p_add;	// +X			// base + X1+X2+X3+...+Xn
	float p_mul;	// *(1+X)		// base * (X1+X2+X3+...+Xn)
	float p_sub;	// -X			// total - X1 ... Xn 
	float p_negMul;	// *(1-X)		// total * (1-X1) * (1-X2) * ... * (1-Xn)

	// This is not battle effect
	// It shouldn't be used as battle effect 

	StatModEffect() : EffectObject()
	{
		
		this->effectGroup = effectGroups::statModifier;
		this->objectType = objectType::effect;

		p_add = 0;
		p_mul = 0;
		p_sub = 0;
		p_negMul = 0;
	}

	StatModEffect(targetType::TargetType target, statNames::StatName stat, float add, float mul, float sub, float negMul) : EffectObject()
	{
		this->effectGroup = effectGroups::statModifier;
		this->objectType = objectType::effect;

		this->targetType = target;
		this->statName = stat;

		this->p_add = add;
		this->p_mul = mul;
		this->p_sub = sub;
		this->p_negMul = negMul;
	}

};

class StatModEffectSkill : public StatModEffect
{
public:
	characterRole::Role targetRole;

	StatModEffectSkill(targetType::TargetType target, statNames::StatName stat, float add, float mul, float sub, float negMul, characterRole::Role role)
		: StatModEffect(target, stat, add, mul, sub, negMul)
	{
		this->targetRole = role;
	}
};