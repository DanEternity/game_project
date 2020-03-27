#pragma once

#include <string>
#include <deque>
#include "scriptDescriptor.h"
#include <TGUI\TGUI.hpp>
#include "scriptDescriptorGroups.h"

//
// This file contains data for script system stored in enviroment
//

class ScriptSystemData
{
public:
	std::wstring task = L"notInitialized";

	// external status
	std::wstring status = L"null";

	// scriptQueue
	//std::deque<ScriptDescriptor *> queue;
	std::deque<StackElement *> queue;

	// ExternalReaction
	bool buttonPressed = false;

	int buttonId = -1;

	std::map<std::wstring, int> enviromentMap;

	std::map<int, ScriptDescriptor *> scriptDB;

	ScriptDescriptor * currentScript = NULL;

	// This value shouldn't be changed manually
	int nextScriptID = 0; 

	// Descriptor groups
	std::map<std::wstring, ScriptDescriptorGroup> scriptGroups;

	// Script gui objects (window with choses, textboxes etc)
	tgui::Gui scriptGui;
	
	// Does game should handle script GUI events
	bool scriptGuiEventsRequiresUpdate = false;

};