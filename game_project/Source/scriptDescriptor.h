#pragma once

#include <vector>
#include <map>
#include "baseObject.h"
#include "scriptTypes.h"

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