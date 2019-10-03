#pragma once

#include <string>
#include <deque>
#include "scriptDescriptor.h"

//
// This file contains data for script system stored in enviroment
//

class ScriptSystemData
{
public:
	std::string task = "notInitialized";

	// external status
	std::string status = "null";

	// scriptQueue
	std::deque<ScriptDescriptor *> queue;

	// ExternalReaction
	bool buttonPressed;

	int buttonId;

	std::map<std::string, int> enviromentMap;

};