#pragma once

//
// Configurable game logic
//
// This data is part of gEnv structure. It cannot include gEnv or upper structures and functions;
// This class contain data about current configuration of game logic. Scripts and mods can change
// that if necessary.
// 

#include <map>
#include <string>

#include "compilerTemplatesFormat.h"

class GameLogicData
{
public:

	std::multimap<std::string, std::string> moduleWorkRequirements_otherModuleByClass;	// m[A] = B; -> means A need B to work
																						// Multiple requirements can be used if necessary.	
																						// Incorrect or impossible requirement are still
																						// applies and will prevent module from working.

	// by default there are certain rules:
	// Shield Amplifier need Shield Generator
	// Sensor Amplifier need Sensor System

	std::map<std::wstring, CompilerCommandTemplate> compilerCommandTemplates;


};