#pragma once

//
//	This file contain usefull scenarios for working with memory, converfting, etc.
//	
//	These functions can be used to simplify process of script function work
//

#include "scriptMemoryUtils.h"

namespace scriptUtil
{

	// IntObject
	BaseObject * getArgumentIntObject(std::wstring arg, ScriptDescriptor * sd, bool &error);
	int getArgumentIntValue(std::wstring arg, ScriptDescriptor * sd, bool &error);

	// FloatObject
	BaseObject * getArgumentFloatObject(std::wstring arg, ScriptDescriptor * sd, bool &error);
	float getArgumentFloatValue(std::wstring arg, ScriptDescriptor * sd, bool &error);

	// StringObject
	BaseObject * getArgumentStringObject(std::wstring arg, ScriptDescriptor * sd, bool &error);
	std::wstring getArgumentStringValue(std::wstring arg, ScriptDescriptor * sd, bool &error);

	// Make copy of object
	BaseObject * replicateStandart(std::wstring arg, ScriptDescriptor * sd, bool &error);

	statNames::StatName getFromStringStatName(std::wstring name);
	targetType::TargetType getFromStringTargetType(std::wstring name);
}

