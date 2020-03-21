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

		BaseScript * Put(CompilerCommandTemplateDataBuffer * buffer);
		BaseScript * Text(CompilerCommandTemplateDataBuffer * buffer);
		BaseScript * Terminate(CompilerCommandTemplateDataBuffer * buffer);
		BaseScript * Jump(CompilerCommandTemplateDataBuffer * buffer);
		BaseScript * Choose(CompilerCommandTemplateDataBuffer * buffer);
		BaseScript * Ariphmetic(CompilerCommandTemplateDataBuffer * buffer);
		BaseScript * ChangeScriptEntryPoint(CompilerCommandTemplateDataBuffer * buffer);
		BaseScript * SpendTime(CompilerCommandTemplateDataBuffer * buffer);
		BaseScript * InitRewardBuffer(CompilerCommandTemplateDataBuffer * buffer);

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