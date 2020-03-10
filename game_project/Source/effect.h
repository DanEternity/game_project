#pragma once

//
//
//	This file contain "effect object" implementation
//	
//

#include "baseObject.h"
#include <string>

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

		powerSupply, // ship energy for module operation
		highPowerSupply, // ship energy for module operation
		actionPoints, // ship power condensator capacity

		// defence stats
		hull,
		hullResist,
		hullReg,
		hullStructureStability,
		shield,
		shieldResist,
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

	};

}

namespace targetType {

	enum TargetType {
		ship,
		character,
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

	StatModEffect()
	{
		this->effectGroup = effectGroups::statModifier;
		this->objectType = objectType::effect;

		p_add = 0;
		p_mul = 0;
		p_sub = 0;
		p_negMul = 0;
	}

};