#include "scriptWorkflowUtility.h"

BaseObject * scriptUtil::getArgumentIntObject(std::wstring arg, ScriptDescriptor * sd, bool &error)
{

	error = false;
	BaseObject * obj = NULL;

	// check if src is const
	if (arg.size() >= 1)
	{
		if (arg[0] != '$')
		{
			// value is const
			auto code = convertConstToObject(arg, &obj);
			if (code != memoryUtil::ok)
			{
				// failed
				error = true;
				return obj;
			}
		}
		else
		{
			// get src object if not a const
			auto code = getMemoryCell(arg, &obj, &sd->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				error = true;
				return obj;
			}
		}
	}
	else
	{
		// failed
		// no source provided
		error = true;
		return obj;
	}

	if (obj->objectType != objectType::integer)
		error = true;

	return obj;

}

int scriptUtil::getArgumentIntValue(std::wstring arg, ScriptDescriptor * sd, bool & error)
{
	//int error = false;
	auto p = getArgumentIntObject(arg, sd, error);
	if (error)
		return 0;
	
	int r = static_cast<IntObject*>(p)->value;

	if ((p->memoryControl & memoryControl::singleUse) != 0)
		delete(p);

	return r;
}

BaseObject * scriptUtil::getArgumentFloatObject(std::wstring arg, ScriptDescriptor * sd, bool & error)
{
	error = false;
	BaseObject * obj = NULL;

	// check if src is const
	if (arg.size() >= 1)
	{
		if (arg[0] != '$')
		{
			// value is const
			auto code = convertConstToObject(arg, &obj);
			if (code != memoryUtil::ok)
			{
				// failed
				error = true;
				return obj;
			}
		}
		else
		{
			// get src object if not a const
			auto code = getMemoryCell(arg, &obj, &sd->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				error = true;
				return obj;
			}
		}
	}
	else
	{
		// failed
		// no source provided
		error = true;
		return obj;
	}

	if (obj->objectType != objectType::real)
	{
		if (obj->objectType != objectType::integer)
			error = true;
		else
		{
			// convert int to float
			FloatObject * q = new FloatObject(static_cast<IntObject*>(obj)->value);
			if ((obj->memoryControl & memoryControl::singleUse) != 0)
				delete (obj);
			obj = q;
			obj->memoryControl = memoryControl::singleUse;
		}
	}
	return obj;
}

float scriptUtil::getArgumentFloatValue(std::wstring arg, ScriptDescriptor * sd, bool & error)
{
	//int error = false;
	auto p = getArgumentFloatObject(arg, sd, error);
	if (error)
		return 0;

	float r = static_cast<FloatObject*>(p)->value;

	if ((p->memoryControl & memoryControl::singleUse) != 0)
		delete(p);

	return r;
}

BaseObject * scriptUtil::getArgumentStringObject(std::wstring arg, ScriptDescriptor * sd, bool & error)
{

	error = false;
	BaseObject * obj = NULL;

	// check if src is const
	if (arg.size() >= 1)
	{
		if (arg[0] != '$')
		{
			// value is const
			auto code = convertConstToObject(arg, &obj);
			if (code != memoryUtil::ok)
			{
				// failed
				error = true;
				return obj;
			}
		}
		else
		{
			// get src object if not a const
			auto code = getMemoryCell(arg, &obj, &sd->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				error = true;
				return obj;
			}
		}
	}
	else
	{
		// failed
		// no source provided
		error = true;
		return obj;
	}

	if (obj->objectType != objectType::string)
	{
		if (obj->objectType != objectType::integer)
			error = true;
		else
		{
			// convert int to float
			StringObject * q = new StringObject();
			q->value = std::to_wstring(static_cast<IntObject*>(obj)->value);
			if ((obj->memoryControl & memoryControl::singleUse) != 0)
				delete (obj);
			obj = q;
			obj->memoryControl = memoryControl::singleUse;
		}
	}

	return obj;

}

std::wstring scriptUtil::getArgumentStringValue(std::wstring arg, ScriptDescriptor * sd, bool & error)
{
	//int error = false;
	auto p = getArgumentStringObject(arg, sd, error);
	if (error)
		return L"";

	std::wstring r = static_cast<StringObject*>(p)->value;

	if ((p->memoryControl & memoryControl::singleUse) != 0)
		delete(p);

	return r;
}

targetType::TargetType scriptUtil::getFromStringTargetType(std::wstring name)
{

	if (name == L"ship" || name == L"Ship") { return targetType::ship; }
	if (name == L"character" || name == L"Character") { return targetType::character; }

	return targetType::TargetType();
}

BaseObject * scriptUtil::replicateStandart(std::wstring arg, ScriptDescriptor * sd, bool & error)
{
	error = false;
	BaseObject * obj = NULL;

	// check if src is const
	if (arg.size() >= 1)
	{
		if (arg[0] != '$')
		{
			// value is const
			auto code = convertConstToObject(arg, &obj);
			if (code != memoryUtil::ok)
			{
				// failed
				error = true;
				return obj;
			}
		}
		else
		{
			// get src object if not a const
			auto code = getMemoryCell(arg, &obj, &sd->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				error = true;
				return obj;
			}
		}
	}
	else
	{
		// failed
		// no source provided
		error = true;
		return obj;
	}

	if (obj->memoryControl == memoryControl::fixed)
		return obj;
	

	if (obj->objectType == objectType::integer)
	{
		IntObject * p = new IntObject(static_cast<IntObject*>(obj)->value);
		if (obj->singleUse())
			delete(obj);
		return p;
	}

	if (obj->objectType == objectType::real)
	{
		FloatObject * p = new FloatObject(static_cast<FloatObject*>(obj)->value);
		if (obj->singleUse())
			delete(obj);
		return p;
	}

	if (obj->objectType == objectType::string)
	{
		StringObject * p = new StringObject(static_cast<StringObject*>(obj)->value);
		if (obj->singleUse())
			delete(obj);
		return p;
	}

	// unsafe return
	wprintf(L"Warning replicate function encountered unsafe argument that cannot be replicated. Arg = [%ws] \n", arg.c_str());
	return obj;

}

statNames::StatName scriptUtil::getFromStringStatName(std::wstring name)
{

	//	powerSupply,
	//	highPowerSupply, 
	//	actionPoints, 
	//	hull,
	//	hullResist,
	//	hullReg,
	//	hullStructureStability,
	//	shield,
	//	shieldResist,
	//	shieldReg,
	//	shieldStructureStability,
	//	evasion,
	//	mobility,
	//	stealth,
	//	stealthTier,
	//	sensorPower,
	//	sensorTier,
	//	missileDefense,
	//	missileDefenseTier,
	//	hyperDrivePower,
	//	hyperDriveTier,
	//	hyperDriveFuelEfficiency,
	//	additionalWeaponAccuracy,
	//	totalDamageMultiplier, 
	//	fuel, 

	//characterHealth,
	//characterArmor,
	//characterShield,
	//characterBlock,
	//characterResist,
	//characterShieldReg,
	//characterActionPoints,
	//characterEnergy,
	//characterEnergyReg,
	//characterInitiative,

	if (name == L"powerSupply") { return statNames::powerSupply; }
	if (name == L"highPowerSupply") { return statNames::highPowerSupply; } 
	if (name == L"actionPoints") { return statNames::actionPoints; } 
	if (name == L"hull") { return statNames::hull; }
	if (name == L"hullResist") { return statNames::hullResist; }
	if (name == L"hullReg") { return statNames::hullReg; }
	if (name == L"hullStructureStability") { return statNames::hullStructureStability; }
	if (name == L"shield") { return statNames::shield; }
	if (name == L"shieldResist") { return statNames::shieldResist; }
	if (name == L"shieldReg") { return statNames::shieldReg; }
	if (name == L"shieldStructureStability") { return statNames::shieldStructureStability; }
	if (name == L"evasion") { return statNames::evasion; }
	if (name == L"mobility") { return statNames::mobility; }
	if (name == L"stealth") { return statNames::stealth; }
	if (name == L"stealthTier") { return statNames::stealthTier; }
	if (name == L"sensorPower") { return statNames::sensorPower; }
	if (name == L"sensorTier") { return statNames::sensorTier; }
	if (name == L"missileDefense") { return statNames::missileDefense; }
	if (name == L"missileDefenseTier") { return statNames::missileDefenseTier; }
	if (name == L"hyperDrivePower") { return statNames::hyperDrivePower; }
	if (name == L"hyperDriveTier") { return statNames::hyperDriveTier; }
	if (name == L"hyperDriveFuelEfficiency") { return statNames::hyperDriveFuelEfficiency; }
	if (name == L"additionalWeaponAccuracy") { return statNames::additionalWeaponAccuracy; }
	if (name == L"totalDamageMultiplier") { return statNames::totalDamageMultiplier; } 
	if (name == L"fuel") { return statNames::fuel; } 
	// character
	if (name == L"characterHealth") { return statNames::characterHealth; }
	if (name == L"characterArmor") { return statNames::characterArmor; }
	if (name == L"characterShield") { return statNames::characterShield; }
	if (name == L"characterBlock") { return statNames::characterBlock; }
	if (name == L"characterResist") { return statNames::characterResist; }
	if (name == L"characterShieldReg") { return statNames::characterShieldReg; }
	if (name == L"characterActionPoints") { return statNames::characterActionPoints; }
	if (name == L"characterEnergy") { return statNames::characterEnergy; }
	if (name == L"characterEnergyReg") { return statNames::characterEnergyReg; }
	if (name == L"characterInitiative") { return statNames::characterInitiative; }



	return statNames::null;

}
