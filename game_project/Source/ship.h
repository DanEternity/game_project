#pragma once


//
// This file contain ship object
//
// This file should not include enviroment.h
//

#include <vector>
#include "baseObject.h"
#include "item.h"
#include "character.h"
#include "stat.h"
#include "effect.h"
#include <map>

class Ship : public BaseObject
{
public:

	// links section

	std::vector<Module*> modules;
	std::vector<moduleSlot::ModuleSlot> slots;

	// links to characters binded to this ship
	// this vector does not represent all characters available for player control
	// only characters that affect this ship stats and functions
	
	std::vector<characterRole::Role> characterRoleSlots;
	std::vector<Character*> characterPosition;

	// stats section

	/* here goes various stats of the ship. Example energy, defenses, hull etc... */

	std::map<statNames::StatName, Stat*> shipStats;

	Stat powerSupply; // ship energy for module operation
	Stat highPowerSupply; // ship energy for module operation
	Stat actionPoints; // ship power condensator capacity
	
	// defence stats
	Stat hull;
	Stat hullResist;
	Stat hullReg;
	Stat hullStructureStability;
	Stat shield;
	Stat shieldResist;
	Stat shieldReg;
	Stat shieldStructureStability;

	Stat evasion;
	Stat mobility;
	Stat stealth;
	Stat stealthTier;
	Stat sensorPower;
	Stat sensorTier;
	Stat missileDefense;
	Stat missileDefenseTier;

	// hyperdrive 
	Stat hyperDrivePower;
	Stat hyperDriveTier;
	Stat hyperDriveFuelEfficiency;

	Stat additionalWeaponAccuracy;
	float totalDamageMultiplier; // output damage multiplier
	
	float missileDefencePenalty;  // penalty due to dense missile attack
	float actionPointsPenalty; // penalty due to damage to Core

	Stat fuel; // hyperdrive fuel

	Ship()
	{

		this->memoryControl = memoryControl::fixed;
		this->objectType = objectType::ship;

		shipStats[statNames::powerSupply] = &powerSupply;
		shipStats[statNames::highPowerSupply] = &highPowerSupply;
		shipStats[statNames::actionPoints] = &actionPoints;

		shipStats[statNames::hull] = &hull;
		shipStats[statNames::hullResist] = &hullResist;
		shipStats[statNames::hullReg] = &hullReg;
		shipStats[statNames::hullStructureStability] = &hullStructureStability;

		shipStats[statNames::shield] = &shield;
		shipStats[statNames::shieldResist] = &shieldResist;
		shipStats[statNames::shieldReg] = &shieldReg;
		shipStats[statNames::shieldStructureStability] = &shieldStructureStability;

		shipStats[statNames::evasion] = &evasion;
		shipStats[statNames::mobility] = &mobility;
		shipStats[statNames::stealth] = &stealth;
		shipStats[statNames::stealthTier] = &stealthTier;
		shipStats[statNames::sensorPower] = &sensorPower;
		shipStats[statNames::sensorTier] = &sensorTier;
		shipStats[statNames::missileDefense] = &missileDefense;
		shipStats[statNames::missileDefenseTier] = &missileDefenseTier;
		shipStats[statNames::additionalWeaponAccuracy] = &additionalWeaponAccuracy;


		shipStats[statNames::hyperDrivePower] = &hyperDrivePower;
		shipStats[statNames::hyperDriveTier] = &hyperDriveTier;
		shipStats[statNames::hyperDriveFuelEfficiency] = &hyperDriveFuelEfficiency;

		shipStats[statNames::fuel] = &fuel;

		characterPosition.resize(4, nullptr);
		characterRoleSlots.resize(4, characterRole::noneRole);
		characterRoleSlots[1] = characterRole::noneRole;
		
	}

};
