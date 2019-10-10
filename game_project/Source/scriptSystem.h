#pragma once

#include "enviroment.h"
#include "scriptUtilsUI.h"
#include <stack>
//#include "scriptDescriptor.h"

#define MAX_COMMANDS_LIMIT 10000

namespace p_sysStatus
{
	enum Status
	{
		idle,
		processingScript,
		scriptTerminated,
		scriptWaitForReaction,
	};

}

class ScriptSystem
{
public:
	void updateScriptEngine();
private:

	// current line
	int p_l; 
	// next line
	int p_nl;
	// status
	p_sysStatus::Status p_s;
	// target descriptor 
	ScriptDescriptor * p_d;
	// stack
	std::stack<StackElement*> p_stack;
	// terminate flag
	bool p_terminate;

	// base update func
	void p_processFrame();
	void p_processScriptDescriptor();
	void p_processCommand(BaseScript * command);

	// util
	void p_blockGame_ScriptRunning(bool mode = true);
	void p_blockGame_WaitForReaction(bool mode = true);

	// converts string to parsed and updated string
	std::string p_convertText(std::string src);

	// parse convertable fragment ($value)
	std::string p_convertValueToString(std::string src);

	// parse value from fragment
	///

	// Returns memory cell data as string or "NULL" if does not exist
	std::string p_getLocalMemoryCellAsString(std::string idx);

	// Returns memory cell data from external table
	std::string p_getExternalTableValueAsString(std::string tableId, std::string idx);

	std::string p_getGlobalValueAsString(std::string ValueName);

	// commands
	void p_processText(TextScript * command);
	void p_processPut(PutScript * command);
	void p_processChoose(ChooseScript * command);
	void p_processTerminate(TerminateScript * command);
};

extern ScriptSystem * scriptSystem;

