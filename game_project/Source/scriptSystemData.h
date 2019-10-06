#pragma once

#include <string>
#include <deque>
#include "scriptDescriptor.h"
#include <TGUI\TGUI.hpp>

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
	bool buttonPressed = false;

	int buttonId = -1;

	std::map<std::string, int> enviromentMap;

	std::map<int, ScriptDescriptor *> scriptDB;

	// This value shouldn't be changed manually
	int nextScriptID = 0; 

	tgui::Gui scriptGui;
	
	// Does game should handle script GUI events
	bool scriptGuiEventsRequiresUpdate = false;

};