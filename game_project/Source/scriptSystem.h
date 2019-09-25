#pragma once

#include "enviroment.h"
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

	// Base update func
	void p_processFrame();
	void p_processScriptDescriptor();
	void p_processCommand(BaseScript * command);

	// util
	void p_blockGame_ScriptRunning(bool mode = true);
	void p_blockGame_WaitForReaction(bool mode = true);

	// Commands
	void p_processText(TextScript * command);
};

extern ScriptSystem * scriptSystem;

