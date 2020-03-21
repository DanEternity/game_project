#include "GameLogicCore.h"

void InitGameLogic()
{
	LoadModuleDependities();
	LoadScriptTemplates();

}

void LoadModuleDependities()
{

	gEnv->game.gameLogic.moduleWorkRequirements_otherModuleByClass.clear();

	std::pair<std::string, std::string> q;

	q.first = "Shield Amplifier";
	q.second = "Shield Generator";

	gEnv->game.gameLogic.moduleWorkRequirements_otherModuleByClass.insert(q);

	q.first = "Sensor Amplifier";
	q.second = "Sensor System";

	gEnv->game.gameLogic.moduleWorkRequirements_otherModuleByClass.insert(q);

}

void LoadScriptTemplates()
{
	CompilerCommandTemplate p;

	// Put
	p = CompilerCommandTemplate();
	p.mainPrefix = L"PUT";
	p.body = " \"$A\" \"$B\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::Put;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// Choose
	p = CompilerCommandTemplate();
	p.mainPrefix = L"CHOOSE";
	p.body = "\"$T\" %[$A] \"$B\" [$C]%,;";
	p.mainHandler = scriptCompilerTemplates::mainHandler::Choose;
	p.postUpdateHandler = scriptCompilerTemplates::afterUpdateHandler::Choose;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// Text
	p = CompilerCommandTemplate();
	p.mainPrefix = L"TEXT";
	p.body = "\"$A\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::Text;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// Terminate
	p = CompilerCommandTemplate();
	p.mainPrefix = L"TERMINATE";
	p.body = "";
	p.mainHandler = scriptCompilerTemplates::mainHandler::Terminate;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	//Jump
	p = CompilerCommandTemplate();
	p.mainPrefix = L"JUMP";
	p.body = "\"$A\" \"$B\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::Jump;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// Ariphmetic
	p = CompilerCommandTemplate();
	p.mainPrefix = L"ARIPHMETIC";
	p.body = "\"$A\" \"$B\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::Ariphmetic;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// ChangeScriptEntryPoint
	p = CompilerCommandTemplate();
	p.mainPrefix = L"CHANGESCRIPTENTRYPOINT";
	p.body = "\"$A\" \"$B\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::ChangeScriptEntryPoint;
	p.postUpdateHandler = scriptCompilerTemplates::afterUpdateHandler::ChangeScriptEntryPoint;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// InitRewardBuffer
	p = CompilerCommandTemplate();
	p.mainPrefix = L"INITREWARDBUFFER";
	p.body = "";
	p.mainHandler = scriptCompilerTemplates::mainHandler::InitRewardBuffer;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// SpendTime
	p = CompilerCommandTemplate();
	p.mainPrefix = L"SPENDTIME";
	p.body = "\"$A\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::SpendTime;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

}
