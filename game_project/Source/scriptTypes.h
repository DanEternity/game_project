#pragma once

#include "baseObject.h"
#include <string>
#include <vector>
#include <map>

//
// This file contain types for script system. Each class represent one or more commands in script system.
//


namespace scriptType
{
	enum ScriptType
	{
		null,
		text,
		put,
		choose,
	};
}

class StackElement
{
public:
	
	std::map<std::string, BaseObject*> localMemory;

	int returnPoint;



};

// Command types

class BaseScript : public BaseObject
{
public:
	scriptType::ScriptType scriptType;
	int commandId;
	BaseScript()
	{
		this->memoryControl = memoryControl::free;
		this->scriptType = scriptType::null;
	}
};

class TextScript : public BaseScript
{
public:
	std::string text;
	TextScript()
	{
		this->scriptType = scriptType::text;
	}
};

class ChooseScript : public TextScript
{
public:
	std::vector<std::string> variants;
	std::vector<int> jumps;
	std::vector<std::string> comparators;
};

class PutScript : public BaseScript
{
public:
	std::string scr;
	std::string dest;
	PutScript()
	{
		this->scriptType = scriptType::put;
	}
};