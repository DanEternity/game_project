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
		initRewardBuffer,
		call,
		putToPointer,
		createItem,
		addRewardToBuffer,
		putFromPointer,
		random,
		createSysModule,
		createModStatEffect,
		applyEffect,
		applyEffectToSysModule,
		putItemToPlayerInventory,
		editItemProperties,
		editModuleProperties,
		editItemConstructableProperties,
		createResourceItem,
		createEquipmentItem,
		editEquipmentProperties,
		applyEffectToEquipment,
	};
}

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
	std::wstring prefix;
	int commandId;
	BaseScript()
	{
		this->memoryControl = memoryControl::free;
		this->scriptType = scriptType::null;
		prefix = L"";
	}
};

#define LocalMemory std::map<std::wstring, BaseObject*> 

// Structure that contain script local memory, commands and default entry point
class ScriptDescriptor : public BaseObject
{
public:
	std::vector<BaseScript*> scriptLines;
	int entryPoint;
	LocalMemory localMemory;

	ScriptDescriptor()
	{
		this->objectType = objectType::scriptDescriptor;
		this->memoryControl = memoryControl::fixed;
	}
};

struct RetContext
{
	std::wstring linkTable;
	std::vector<std::wstring> srcVarLink;
};

class StackElement
{
public:

	std::map<std::wstring, BaseObject*> localMemory;
	ScriptDescriptor * scriptId;
	int returnPoint;
	RetContext * rContext;

	StackElement()
	{
		scriptId = NULL;
		returnPoint = 0;
		rContext = NULL;
	}

};


class TextScript : public BaseScript
{
public:
	std::wstring text;
	TextScript() : BaseScript()
	{
		this->scriptType = scriptType::text;
	}
};

class ChooseScript : public TextScript
{
public:
	std::vector<ChooseElement> variants;
	ChooseScript() : TextScript()
	{
		this->scriptType = scriptType::choose;
	}
};

class PutScript : public BaseScript
{
public:
	std::wstring scr;
	std::wstring dest;
	PutScript() : BaseScript()
	{
		this->scriptType = scriptType::put;
	}
};

class TerminateScript : public BaseScript
{
public:
	TerminateScript() : BaseScript()
	{
		this->scriptType = scriptType::terminate;
	}
};

class JumpScript : public BaseScript
{
public:
	int lineId;
	std::wstring chache = L"";
	JumpScript() : BaseScript()
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
	AriphmeticScript() : BaseScript()
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
	IfDoJumpScript() : BaseScript()
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
	ChangeScriptEntryPointScript() : BaseScript()
	{
		this->scriptType = scriptType::changeScriptEntryPoint;
	}
};

class SpendTimeScript : public BaseScript
{
public:
	std::wstring amount;
	SpendTimeScript() : BaseScript()
	{
		this->scriptType = scriptType::spendTime;
	}
};

class InitRewardBufferScript : public BaseScript
{
public:
	InitRewardBufferScript() : BaseScript()
	{
		this->scriptType = scriptType::initRewardBuffer;
	}
};

class CallScript : public BaseScript
{
public:
	std::wstring scriptId;
	std::vector<std::wstring> arg;
	CallScript() : BaseScript()
	{
		this->scriptType = scriptType::call;
	}
};

class PutToPointerScript : public BaseScript
{
public:
	std::wstring src;
	std::wstring dst;
	PutToPointerScript() : BaseScript()
	{
		this->scriptType = scriptType::putToPointer;
	}
};

class CreateItemScript : public BaseScript // Not finished
{
public:
	
	CreateItemScript() : BaseScript()
	{
		this->scriptType = scriptType::createItem;
	}
};

class AddRewardToBufferScript : public BaseScript
{
public:
	std::wstring src;
	AddRewardToBufferScript() : BaseScript()
	{
		this->scriptType = scriptType::addRewardToBuffer;
	}
};

class PutFromPointerScript : public BaseScript
{
public:
	std::wstring src;
	std::wstring dst;
	PutFromPointerScript() : BaseScript()
	{
		this->scriptType = scriptType::putFromPointer;
	}
};

class RandomScript : public BaseScript
{
public:
	std::wstring dst;
	RandomScript() : BaseScript()
	{
		this->scriptType = scriptType::random;
	}
};

class CreateSysModuleScript : public BaseScript
{
public:
	std::wstring dst;
	std::wstring name;
	CreateSysModuleScript() : BaseScript()
	{
		this->scriptType = scriptType::createSysModule;
	}
};

class CreateModStatEffectScript : public BaseScript
{
public:
	std::wstring dst;

	//targetType::TargetType targetType; // entity type name // ship, character... etc

	//statNames::StatName statName;

	//float p_add;	// +X			// base + X1+X2+X3+...+Xn
	//float p_mul;	// *(1+X)		// base * (X1+X2+X3+...+Xn)
	//float p_sub;	// -X			// total - X1 ... Xn 
	//float p_negMul;	// *(1-X)		// total * (1-X1) * (1-X2) * ... * (1-Xn)

	std::wstring targetType; // string
	std::wstring statName; // string
	std::wstring p_add; // float
	std::wstring p_mul; // float
	std::wstring p_sub; // float
	std::wstring p_negMul; // float

	CreateModStatEffectScript() : BaseScript()
	{
		this->scriptType = scriptType::createModStatEffect;
	}

};

class ApplyEffectScript : public BaseScript
{
public:
	std::wstring src;
	std::wstring dst;

	ApplyEffectScript() : BaseScript()
	{
		this->scriptType = scriptType::applyEffect;
	}

};

class PutItemToPlayerInventoryScript : public BaseScript
{
public:
	std::wstring src;

	PutItemToPlayerInventoryScript() : BaseScript()
	{
		this->scriptType = scriptType::putItemToPlayerInventory;
	}

};

class EditItemPropertiesScript : public BaseScript
{
public:
	std::wstring src;
	std::wstring level;
	std::wstring rarity;
	std::wstring itemId;
	std::wstring itemClass;
	std::wstring itemName;

	EditItemPropertiesScript() : BaseScript()
	{
		this->scriptType = scriptType::editItemProperties;
	}
};

class EditModulePropertiesScript : public BaseScript
{
public:
	std::wstring src;
	std::wstring moduleType;
	std::wstring moduleSlot;
	std::wstring moduleSize;
	std::wstring powerSupply;
	std::wstring highPowerSupply;
	std::wstring powerPriority;

	EditModulePropertiesScript() : BaseScript()
	{
		this->scriptType = scriptType::editModuleProperties;
	}
};

class EditItemConstructablePropertiesScript : public BaseScript
{
public:
	std::wstring src;
	std::wstring key;
	std::wstring quality;
	std::wstring modifier;

	EditItemConstructablePropertiesScript() : BaseScript()
	{
		this->scriptType = scriptType::editItemConstructableProperties;
	}
};

class CreateResourceItemScript : public BaseScript
{
public:
	std::wstring dst;
	std::wstring count;
	std::wstring maxCount;
	std::wstring name;
	CreateResourceItemScript() : BaseScript()
	{
		this->scriptType = scriptType::createResourceItem;
	}
};

class CreateEquipmentItemScript : public BaseScript
{
public:
	std::wstring dst;
	std::wstring name;

	CreateEquipmentItemScript() : BaseScript()
	{
		this->scriptType = scriptType::createEquipmentItem;
	}
};

class EditEquipmentPropertiesScript : public BaseScript
{
public:
	std::wstring src;
	// add more fields
	std::wstring slot;
	std::wstring name;

	EditEquipmentPropertiesScript() : BaseScript()
	{
		this->scriptType = scriptType::editEquipmentProperties;
	}
};