#pragma once

#include <map>

class ScriptDescriptorGroup
{
public:
	std::wstring modName;
	std::wstring id; // used as key
	std::map<std::wstring, std::wstring> extReference;

};