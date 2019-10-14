#pragma once

#include <vector>
#include <string>
#include <map>
#include "envUtils.h"

//
// This file contain code generation procedures
//
///////////////////////////////////////////////////////
//
//	File example
//	
//	// comment
//
//	#version 1
//	
//	#import "src:sampleMod table:table1 to:my_imported_table"
//
//	#ext "my_own_table"
//
//	// Empty lines will be ignored
//
//	@start	// actually do nothing because start line is always first (id = 0) line
//	Put "$EXT:my_imported_table:some_value" to "$_value1"
//
//	Ariphmetic "$_value1 * 0.4" to "$EXT:my_own_table:value1"
//
//	SetEntryPoint "@new_start"
//
//	Terminate
//	
//
//	@new_start	// using specific command you can change start position to any marker in text
//				// Marker does not consume line. It will not increase line numbers after compilation
//	
//	...
//	Call "$EXT:my_imported_table:someFunction"
//	...
//	Put "$_local_value" to "$EXT:my_imported_table:some_value2"
//	...
//
///////////////////////////////////////////////////////

namespace syntaxType {

	enum sType
	{
		none,
		directive,
		marker,
		comment,
		command,
		c_put,
		c_text,
		

	};

}

class ScriptCompiler
{
public:
	bool compileScriptText(std::vector<std::string> src);
	ScriptDescriptor * getScriptDescriptor();

private:
	
	std::string errText;
	bool error = false;

	int line = 0;
	int idx = 0;

	std::string selection = "";
	std::map<std::string, int> markers;
	ScriptDescriptor * p_s = NULL;
	syntaxType::sType tp = syntaxType::none;
	bool emptyLine = true;
	
	int commandsCount;

	// util variables
	int parameterCount;
	int bracketCount;

	// fragment parser
	bool parseDirecive(std::string s);
	bool parseCommand(std::string s);
	bool parseMarker(std::string s);

	// command parsers
	//bool checkPut(std::string s);
	bool parsePut(std::string s);
	bool parseText(std::string s);
};

