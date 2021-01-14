#pragma once

#include "baseObject.h"
#include "effect.h"

class PassiveSkill : BaseObject
{
public:
	std::wstring name;
	int level;
	bool active;
	StatModEffectSkill* effect;

	PassiveSkill(std::wstring name, int level)
	{
		this->objectType = objectType::skillObject;
		this->memoryControl = memoryControl::fixed;
		this->name = name;
		this->level = level;
		active = false;
		
	}
};