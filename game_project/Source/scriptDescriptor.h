#pragma once

#include <vector>
#include <map>
#include "baseObject.h"
#include "scriptTypes.h"

// Structure that contain script local memory, commands and default entry point
class ScriptDescriptor : public BaseObject
{
public:
	std::vector<BaseScript*> scriptLines;
	int entryPoint;
	std::map<std::string, BaseObject*> localMemory;
};