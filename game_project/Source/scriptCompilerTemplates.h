#pragma once

//
// This file contain compiler handlers for command parsing
//
//
//

#include "scriptTypes.h"
#include "compilerTemplatesFormat.h"
#include "scriptCompilerUtilityParsers.h"

namespace scriptCompilerTemplates
{

	namespace mainHandler 
	{

		BaseScript * Put(CompilerCommandTemplateDataBuffer * buffer); // ok
		BaseScript * Text(CompilerCommandTemplateDataBuffer * buffer); // ok
		BaseScript * Terminate(CompilerCommandTemplateDataBuffer * buffer); // ok
		BaseScript * Jump(CompilerCommandTemplateDataBuffer * buffer); // ok
		BaseScript * Choose(CompilerCommandTemplateDataBuffer * buffer); // ok
		BaseScript * Ariphmetic(CompilerCommandTemplateDataBuffer * buffer); // ok 
		BaseScript * ChangeScriptEntryPoint(CompilerCommandTemplateDataBuffer * buffer); // ok - only with $self
		BaseScript * SpendTime(CompilerCommandTemplateDataBuffer * buffer); // ok
		BaseScript * InitRewardBuffer(CompilerCommandTemplateDataBuffer * buffer); // not ok - Do not completed
		BaseScript * PutToPointer(CompilerCommandTemplateDataBuffer * buffer);  // ok - not tested
		BaseScript * AddToRewardBuffer(CompilerCommandTemplateDataBuffer * buffer);  // not ok - Do not completed
		BaseScript * Call(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * PutFromPointer(CompilerCommandTemplateDataBuffer * buffer);
	}

	namespace afterUpdateHandler 
	{
		// put doesn't need post update // its just example
		//void Put(CompilerCommandTemplateDataBuffer * buffer, BaseScript * p);

		void Jump(CompilerCommandTemplateDataBuffer * buffer, BaseScript * p1);
		void Choose(CompilerCommandTemplateDataBuffer * buffer, BaseScript * p1);
		void ChangeScriptEntryPoint(CompilerCommandTemplateDataBuffer * buffer, BaseScript * p1);
	}

}