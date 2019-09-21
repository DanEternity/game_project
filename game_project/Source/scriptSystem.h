#pragma once

#include "enviroment.h"
//#include "scriptDescriptor.h"

class ScriptSystem
{
public:

private:
	// current line
	int p_l; 
	// next line
	int p_nl;
	// status
	int p_s;
	// target descriptor 
	ScriptDescriptor * p_d;
};