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
		jump,
		ariphmetic,
		ifDoJump,
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
	ComparatorElement(bool a, std::string left, std::string op, std::string right)
	{
		unaryComparator = a;
		this->left = left;
		this->operation = op;
		this->right = right;
	}
	ComparatorElement() {}
};

class ChooseElement
{
public:
	std::string textLine;
	int jump;
	ComparatorElement comp;
	ChooseElement(std::string textLine, int jump, bool a, std::string left, std::string op, std::string right)
	{
		this->textLine = textLine;
		this->jump = jump;
		this->comp = ComparatorElement(a, left, op, right);
	}
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
	std::vector<ChooseElement> variants;
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

class JumpScript : public BaseScript
{
public:
	int lineId;
	JumpScript()
	{
		this->scriptType = scriptType::jump;
	}
};

class AriphmeticScript : public BaseScript
{
public:
	std::string dest;
	std::string operation;
	std::string left;
	std::string right;
	AriphmeticScript()
	{
		this->scriptType = scriptType::ariphmetic;
	}
};

class IfDoJumpScript : public BaseScript
{
public:
	ComparatorElement condition;
	int lineId; // jump to line
	IfDoJumpScript()
	{
		this->scriptType = scriptType::ifDoJump;
	}
};