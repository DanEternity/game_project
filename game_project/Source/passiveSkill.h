#pragma once

#include "baseObject.h"
#include "effect.h"

class PassiveSkill : BaseObject
{
public:
	std::wstring name;
	int level;
	bool active;

	passiveSkill(std::wstring name, int level)
	{
		this->name = name;
		this->level = level;
		active = false;
	}
};