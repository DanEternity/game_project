#pragma once

//
// This file contain data definition for script command templates
//

#include <string>
#include <map>
#include "scriptTypes.h"

struct CompilerCommandTemplateDataBuffer;

struct CompilerCommandTemplate
{

	std::wstring mainPrefix; // Example: "Put"

	std::string body; // Example: "$A" to "$B"

	// Syntax example:

	//
	// Repeat block:
	// %"$A"[$B]"$C",%;
	// last symbol will be used as separator -> ','
	// symbol after '%' is terminate symbol
	// Example: %XY
	// X - block devider
	// Y - block terminator
	// Important: X shouldn't be equal to Y.
	//
	// If any of this missing or incorrect, template will not work
	// and may crash game.
	//
	// Same arg names are overrides withot notice
	// Repeated blocks are coded with suffix 1,2,3... (ex.: $A1 , $A2 ...)
	// You may use multiple repeated blocks type but they shouldn't 
	// intercect. 
	// Nested blocks are not allowed.

	// Called when all arguments collected.

	BaseScript*(*mainHandler)(CompilerCommandTemplateDataBuffer *);
	
	// Called after all functions parsed. Markers can be assigned here.

	void(*postUpdateHandler)(CompilerCommandTemplateDataBuffer * buffer, BaseScript * p);

	CompilerCommandTemplate()
	{
		mainPrefix = L"";
		body = "";
		mainHandler = NULL;
		postUpdateHandler = NULL;
	}

};

struct CompilerCommandTemplateDataBuffer
{

	std::map<std::string, std::wstring> arg; // containg parsed args

	std::map<std::wstring, int> * markers; // pointer to markers

	std::map<std::wstring, std::wstring> * localExtReference; // pointer to external table references

	int line;

	bool error;

	int commandId;

};