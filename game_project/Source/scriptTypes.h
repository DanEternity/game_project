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
		terminate,
	};
}

class StackElement
{
public:
	
	std::map<std::string, BaseObject*> localMemory;

	int returnPoint;



};

class ComparatorElement
{
public:
	bool unaryComparator = false;
	std::string left;
	std::string operation;
	std::string right;
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
	std::vector<ComparatorElement> comparators;
	ChooseScript()
	{
		this->scriptType = scriptType::choose;
	}
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

class TerminateScript : public BaseScript
{
public:
	TerminateScript()
	{
		this->scriptType = scriptType::terminate;
	}
};