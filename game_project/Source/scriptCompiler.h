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
		c_changeScriptEntryPoint,
		c_spendTime,
		c_initRewardBuffer,
	};

}

class ScriptCompiler
{
public:

	// Compile strings to object code. Return true if successful. Use getScriptDescriptor to get result
	bool compileScriptText(std::vector<std::wstring> src);

	// Return compiled script descriptor
	ScriptDescriptor * getScriptDescriptor();


	void setFamilyId(std::wstring id);

private:

	std::wstring errText;
	bool error = false;

	int line = 0;
	int idx = 0;

	std::wstring selection = L"";
	ScriptDescriptor * p_s = NULL;
	syntaxType::sType tp = syntaxType::none;
	bool emptyLine = true;
	int commandsCount;

	// reference to script descriptor group
	std::wstring familyId = L"";

	// local ext reference
	std::map<std::wstring, std::wstring> localExtReference;

	// marker table
	std::map<std::wstring, int> markers;

	// util variables
	int parameterCount;
	int bracketCount;
	int squareBracketCount;
	int status;

	// post processing
	void postProcessCommands();

	// fragment parser
	bool parseDirecive(std::wstring s);
	bool parseCommand(std::wstring s);
	bool parseMarker(std::wstring s);

	// command parsers
	bool parsePut(std::wstring s);
	bool parseText(std::wstring s);
	bool parseTerminate(std::wstring s);
	bool parseJump(std::wstring s);
	bool parseChoose(std::wstring s);
	bool parseAriphmetic(std::wstring s);
	bool parseChangeScriptEntryPoint(std::wstring s);
	bool parseSpendTime(std::wstring s);
	bool parseInitRewardBuffer(std::wstring s);

	ComparatorElement parseCondition(std::wstring s);

	// post update
	bool postUpdateChoose(BaseScript * ptr);
	bool postUpdateJump(BaseScript * ptr);
	bool postUpdateIfDoJump(BaseScript * ptr);
	bool postUpdateChangeScriptEntryPoint(BaseScript * ptr);

	int convertMarkerToLine(std::wstring marker);
};

