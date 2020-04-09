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

	// PutToPointer
	p = CompilerCommandTemplate();
	p.mainPrefix = L"PUTTOPOINTER";
	p.body = "\"$A\" \"$B\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::PutToPointer;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// AddToRewardBuffer
	p = CompilerCommandTemplate();
	p.mainPrefix = L"ADDTOREWARDBUFFER";
	p.body = "\"$A\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::AddToRewardBuffer;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// Call
	p = CompilerCommandTemplate();
	p.mainPrefix = L"CALL";
	p.body = "\"$PTR\" %\"$A\"%,;";
	p.mainHandler = scriptCompilerTemplates::mainHandler::Call;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// PutFromPointer
	p = CompilerCommandTemplate();
	p.mainPrefix = L"PUTFROMPOINTER";
	p.body = "\"$A\" \"$B\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::PutFromPointer;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// Random
	p = CompilerCommandTemplate();
	p.mainPrefix = L"RANDOM";
	p.body = "\"$A\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::Random;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// CreateSysModule
	p = CompilerCommandTemplate();
	p.mainPrefix = L"CREATESYSMODULE";
	p.body = "\"$A\" \"$B\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::CreateSysModule;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// CreateModStatEffect
	p = CompilerCommandTemplate();
	p.mainPrefix = L"CREATEMODSTATEFFECT";
	p.body = "\"$A\" \"$Target\" \"$Stat\" \"$Add\" \"$Mul\" \"$Sub\" \"$NegMul\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::CreateModStatEffect;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// ApplyEffectToSysModule
	p = CompilerCommandTemplate();
	p.mainPrefix = L"APPLYEFFECTTOSYSMODULE";
	p.body = "\"$A\" \"$B\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::ApplyEffectToSysModule;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// PutItemToPlayerInventory
	p = CompilerCommandTemplate();
	p.mainPrefix = L"PUTITEMTOPLAYERINVENTORY";
	p.body = "\"$A\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::PutItemToPlayerInventory;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// EditItemProperties
	p = CompilerCommandTemplate();
	p.mainPrefix = L"EDITITEMPROPERTIES";
	p.body = "\"$src\" \"$level\" \"$rarity\" \"$itemId\" \"$itemClass\" \"$itemName\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::EditItemProperties;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// EditModuleProperties
	p = CompilerCommandTemplate();
	p.mainPrefix = L"EDITMODULEPROPERTIES";
	p.body = "\"$src\" \"$moduleType\" \"$moduleSlot\" \"$moduleSize\" \"$powerSupply\" \"$highPowerSupply\" \"$powerPriority\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::EditModuleProperties;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// EditItemConstructableProperties
	p = CompilerCommandTemplate();
	p.mainPrefix = L"EDITITEMCONSTRUCTABLEPROPERTIES";
	p.body = "\"$src\" \"$key\" \"$quality\" \"$modifier\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::EditItemConstructableProperties;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;
}
