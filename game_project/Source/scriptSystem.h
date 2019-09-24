#pragma once

#include "enviroment.h"
#include <stack>
//#include "scriptDescriptor.h"

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
	int p_s;
	// target descriptor 
	ScriptDescriptor * p_d;
	// stack
	std::stack<StackElement*> p_stack;
};

