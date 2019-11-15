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
		changeScriptEntryPoint,
		spendTime,
	};
}

class StackElement
{
public:
	
	std::map<std::wstring, BaseObject*> localMemory;

	int returnPoint;



};

class ComparatorElement
{
public:
	bool unaryComparator = false;
	std::wstring left;
	std::wstring operation;
	std::wstring right;
	ComparatorElement(bool a, std::wstring left, std::wstring op, std::wstring right)
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
	std::wstring textLine;
	int jump;
	std::wstring chache;
	ComparatorElement comp;
	ChooseElement(std::wstring textLine, int jump, bool a, std::wstring left, std::wstring op, std::wstring right)
	{
		this->textLine = textLine;
		this->jump = jump;
		this->comp = ComparatorElement(a, left, op, right);
	}
	ChooseElement(std::wstring textLine, int jump, ComparatorElement comp)
	{
		this->textLine = textLine;
		this->jump = jump;
		this->comp = comp;
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
	std::wstring text;
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
	std::wstring scr;
	std::wstring dest;
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
	std::wstring chache = L"";
	JumpScript()
	{
		this->scriptType = scriptType::jump;
	}
};

class AriphmeticScript : public BaseScript
{
public:
	std::wstring dest;
	std::wstring operation;
	std::wstring left;
	std::wstring right;
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
	std::wstring chache = L"";
	IfDoJumpScript()
	{
		this->scriptType = scriptType::ifDoJump;
	}
};

class ChangeScriptEntryPointScript : public BaseScript
{
public:
	std::wstring scriptId;
	int lineId;
	std::wstring chache = L"";
	ChangeScriptEntryPointScript()
	{
		this->scriptType = scriptType::changeScriptEntryPoint;
	}
};

class SpendTimeScript : public BaseScript
{
public:
	std::wstring amount;
	SpendTimeScript()
	{
		this->scriptType = scriptType::spendTime;
	}
};