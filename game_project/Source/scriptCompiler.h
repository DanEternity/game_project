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
		c_terminate,
		c_jump,
		c_choose,
		c_ariphmetic,

	};

}

class ScriptCompiler
{
public:
	bool compileScriptText(std::vector<std::string> src);

	ScriptDescriptor * getScriptDescriptor();

	void setFamilyId(std::string id);

private:

	std::string errText;
	bool error = false;

	int line = 0;
	int idx = 0;

	std::string selection = "";
	ScriptDescriptor * p_s = NULL;
	syntaxType::sType tp = syntaxType::none;
	bool emptyLine = true;
	int commandsCount;

	// reference to script descriptor group
	std::string familyId = "";

	// local ext reference
	std::map<std::string, std::string> localExtReference;

	// marker table
	std::map<std::string, int> markers;

	// util variables
	int parameterCount;
	int bracketCount;
	int squareBracketCount;
	int status;

	// post processing
	void postProcessCommands();

	// fragment parser
	bool parseDirecive(std::string s);
	bool parseCommand(std::string s);
	bool parseMarker(std::string s);

	// command parsers
	bool parsePut(std::string s);
	bool parseText(std::string s);
	bool parseTerminate(std::string s);
	bool parseJump(std::string s);
	bool parseChoose(std::string s);
	bool parseAriphmetic(std::string s);

	ComparatorElement parseCondition(std::string s);

	// post update
	bool postUpdateChoose(BaseScript * ptr);
	bool postUpdateJump(BaseScript * ptr);
	bool postUpdateIfDoJump(BaseScript * ptr);

	int convertMarkerToLine(std::string marker);
};

