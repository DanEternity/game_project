#pragma once

#include <map>

class ScriptDescriptorGroup
{
public:
	std::string modName;
	std::string id; // used as key
	std::map<std::string, std::string> extReference;

};