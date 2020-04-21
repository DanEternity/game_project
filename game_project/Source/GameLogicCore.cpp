#include "GameLogicCore.h"

void InitGameLogic()
{
	LoadModuleDependities();
	//LoadScriptTemplates();

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
	p.body = "\"$A\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::Jump;
	p.postUpdateHandler = scriptCompilerTemplates::afterUpdateHandler::Jump;
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

	// IfDoJump
	p = CompilerCommandTemplate();
	p.mainPrefix = L"IFDOJUMP";
	p.body = "\"$A\" \"$B\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::IfDoJump;
	p.postUpdateHandler = scriptCompilerTemplates::afterUpdateHandler::IfDoJump;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// CreateResourceItem
	p = CompilerCommandTemplate();
	p.mainPrefix = L"CREATERESOURCEITEM";
	p.body = "\"$dst\" \"$name\" \"$count\" \"$maxCount\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::CreateResourceItem;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// CreateEquipmentItem
	p = CompilerCommandTemplate();
	p.mainPrefix = L"CREATEEQUIPMENTITEM";
	p.body = "\"$dst\" \"$name\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::CreateEquipmentItem;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// ApplyEffectToEquipment
	p = CompilerCommandTemplate();
	p.mainPrefix = L"APPLYEFFECTTOEQUIPMENT";
	p.body = "\"$A\" \"$B\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::ApplyEffectToEquipment;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// EditEquipmentProperties
	p = CompilerCommandTemplate();
	p.mainPrefix = L"EDITEQUIPMENTPROPERTIES";
	p.body = "\"$src\" \"$name\" \"$slot\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::EditEquipmentProperties;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// CreatePool
	p = CompilerCommandTemplate();
	p.mainPrefix = L"CREATEPOOL";
	p.body = "\"$dst\" \"$argCount\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::CreatePool;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// AddToPool
	p = CompilerCommandTemplate();
	p.mainPrefix = L"ADDTOPOOL";
	p.body = "\"$dst\" \"$weight\" %\"$arg\"%,;";
	p.mainHandler = scriptCompilerTemplates::mainHandler::AddToPool;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// GetFromPool
	p = CompilerCommandTemplate();
	p.mainPrefix = L"GETFROMPOOL";
	p.body = "\"$src\" \"$key\" %\"$arg\"%,;";
	p.mainHandler = scriptCompilerTemplates::mainHandler::GetFromPool;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// StringConcat
	p = CompilerCommandTemplate();
	p.mainPrefix = L"STRINGCONCAT";
	p.body = "\"$A\" \"$B\" \"$dest\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::StringConcat;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// CreateExternalTable
	p = CompilerCommandTemplate();
	p.mainPrefix = L"CREATEEXTERNALTABLE";
	p.body = "\"$dest\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::CreateExternalTable;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// PutToExternalTable
	p = CompilerCommandTemplate();
	p.mainPrefix = L"PUTTOEXTERNALTABLE";
	p.body = "\"$table\" \"$src\" \"$dest\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::PutToExternalTable;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// PutToExternalTable
	p = CompilerCommandTemplate();
	p.mainPrefix = L"PUTFROMEXTERNALTABLE";
	p.body = "\"$table\" \"$src\" \"$dest\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::PutFromExternalTable;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// CreateMarker
	p = CompilerCommandTemplate();
	p.mainPrefix = L"CREATEMARKER";
	p.body = "\"$dest\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::CreateMarker;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// AddMarkerToSector
	p = CompilerCommandTemplate();
	p.mainPrefix = L"ADDMARKERTOSECTOR";
	p.body = "\"$src\" \"$dst\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::AddMarkerToSector;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// EditMarkerProperties
	p = CompilerCommandTemplate();
	p.mainPrefix = L"EDITMARKERPROPERTIES";
	p.body = "\"$src\" \"$level\" \"$danger\" \"$posX\" \"$posY\" \"$label\" \"$desc\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::EditMarkerProperties;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// CallMarkerInitialization
	p = CompilerCommandTemplate();
	p.mainPrefix = L"CALLMARKERINITIALIZATION";
	p.body = "\"$path\" %\"$A\"%,;";
	p.mainHandler = scriptCompilerTemplates::mainHandler::CallMarkerInitialization;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// CallMarkerInitialization // SHORT VERSION
	p = CompilerCommandTemplate();
	p.mainPrefix = L"CALLMARKERINIT";
	p.body = "\"$path\" %\"$A\"%,;";
	p.mainHandler = scriptCompilerTemplates::mainHandler::CallMarkerInitialization;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// LinkScriptToMarker
	p = CompilerCommandTemplate();
	p.mainPrefix = L"LINKSCRIPTTOMARKER";
	p.body = "\"$src\" \"$dst\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::LinkScriptToMarker;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// SetMarkerPosition
	p = CompilerCommandTemplate();
	p.mainPrefix = L"SETMARKERPOSITION";
	p.body = "\"$src\" \"$X\" \"$Y\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::SetMarkerPosition;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// CreateDecoration
	p = CompilerCommandTemplate();
	p.mainPrefix = L"CREATEDECORATION";
	p.body = "\"$dst\" \"$model\" \"$sX\" \"$sY\" \"$rotation\" \"$posX\" \"$posY\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::CreateDecoration;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

	// AddDecorationToSector
	p = CompilerCommandTemplate();
	p.mainPrefix = L"ADDDECORATIONTOSECTOR";
	p.body = "\"$src\" \"$dst\"";
	p.mainHandler = scriptCompilerTemplates::mainHandler::AddDecorationToSector;
	gEnv->game.gameLogic.compilerCommandTemplates[p.mainPrefix] = p;

}
