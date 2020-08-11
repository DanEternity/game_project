#pragma once

#include "enviroment.h"
#include "scriptUtilsUI.h"
#include "generationUtility.h"
#include "scriptWorkflowUtility.h"
#include "scriptCompiler.h"
#include "characterManagement.h"
#include "shipModulesUI.h"
#include "personEquipmentUI.h"
#include "Shop.h"
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
	//// stack
	//std::stack<StackElement*> p_stack;
	// terminate flag
	bool p_terminate;
	// chache flag;
	bool p_chached = false;
	// text chache;
	std::wstring p_textChache;

	// base update func
	void p_processFrame();
	void p_processScriptDescriptor();

	// switch and cast function
	// need to add your cast operation
	void p_processCommand(BaseScript * command);

	// util
	void p_blockGame_ScriptRunning(bool mode = true);
	void p_blockGame_WaitForReaction(bool mode = true);

	// converts string to parsed and updated string
	std::wstring p_convertText(std::wstring src);

	// parse convertable fragment ($value)
	std::wstring p_convertValueToString(std::wstring src);

	// get result of comparator
	bool p_calculateComporator(ComparatorElement * comparator);

	// calculate expression
	bool p_calculateExpression(BaseObject * left, BaseObject * right, std::wstring operation, BaseObject ** dest);

	// get numerical result type
	objectType::ObjectType p_getNumResultType(BaseObject * left, BaseObject * right, std::wstring operation);

	// UI class
	ChooseUI * chooseUI = NULL;

	// Returns memory cell data as string or "NULL" if does not exist
	std::wstring p_getLocalMemoryCellAsString(std::wstring idx);

	// Returns memory cell data from external table
	std::wstring p_getExternalTableValueAsString(std::wstring tableId, std::wstring idx);

	std::wstring p_getGlobalValueAsString(std::wstring ValueName);

	// Utility
	bool GetObjectOrConstFromMemory(std::wstring src, BaseObject ** obj);

	void _CallFunction(StackElement * target, int entryPoint, RetContext * retContext);
	void _RetFunction(StackElement * target);

	// commands
	void p_processText(TextScript * command);
	void p_processPut(PutScript * command);
	void p_processChoose(ChooseScript * command);
	void p_processTerminate(TerminateScript * command);
	void p_processJump(JumpScript * command);
	void p_processAriphmetic(AriphmeticScript * command);
	void p_processIfDoJump(IfDoJumpScript * command);
	void p_processChangeScriptEntryPoint(ChangeScriptEntryPointScript * command);
	void p_processSpendTime(SpendTimeScript * command);
	void p_processInitRewardBuffer(InitRewardBufferScript * command);
	void p_processPutToPointer(PutToPointerScript * command);
	void p_processCall(CallScript * command);
	void p_processPutFromPointer(PutFromPointerScript * command);
	void p_processRandom(RandomScript * command);
	void p_processCreateSysModule(CreateSysModuleScript * command);
	void p_processCreateModStatEffect(CreateModStatEffectScript * command);
	void p_processApplyEffectToSysModule(ApplyEffectScript * command);
	void p_processPutItemToPlayerInventory(PutItemToPlayerInventoryScript * command);
	void p_processEditItemProperties(EditItemPropertiesScript * command);
	void p_processEditModuleProperties(EditModulePropertiesScript * command);
	void p_processEditItemConstructableProperties(EditItemConstructablePropertiesScript * command);
	void p_processCreateResourceItem(CreateResourceItemScript * command);
	void p_processEditEquipmentProperties(EditEquipmentPropertiesScript * command); // not finished
	void p_processCreateEquipmentItem(CreateEquipmentItemScript * command);
	void p_processApplyEffectEquipment(ApplyEffectScript * command);
	void p_processCreatePool(CreatePoolScript * command);
	void p_processAddToPool(AddToPoolScript * command);
	void p_processGetFromPool(GetFromPoolScript * command);
	void p_processStringConcat(StringConcatScript * command);
	void p_processCreateExternalTable(CreateExternalTableScript * command);
	void p_processPutToExternalTable(PutToExternalTableScript * command);
	void p_processPutFromExternalTable(PutFromExternalTableScript * command);
	void p_processCreateMarker(CreateMarkerScript * command);
	void p_processAddMarkerToSector(AddMarkerToSectorScript * command);
	void p_processEditMarkerProperties(EditMarkerPropertiesScript * command);
	void p_processCallCustom(CallCustomScript * command);
	void p_processLinkScriptToMarker(LinkScriptToMarkerScript * command);
	void p_processSetMarkerPosition(SetMarkerPositionScript * command);
	void p_processCreateDecoration(CreateDecorationScript * command);
	void p_processAddDecorationToSector(AddDecorationToSectorScript * command);
	void p_processAddBackgroundToSector(AddBackgroundToSectorScript * command);
	void p_processEquipModule(EquipModuleScript * command);
	void p_processAbs(AbsScript * command);
	void p_processGetShipStat(GetShipStatScript * command);
	void p_processGetResourceCountFromPlayerInventory(GetResourceCountFromPlayerInventoryScript * command);
	void p_processRemoveResourcesFromPlayerInventory(RemoveResourcesFromPlayerInventoryScript * command);
	void p_processGlobalVariableModifier(GlobalVariableModifierScript * command);
	void p_processGetCharacterStat(GetCharacterStatScript * command);
	void p_processInitCharacterStats(InitCharacterStatsScript * command);
	void p_processCreateCharacter(CreateCharacterScript * command);
	void p_processAddCharacterToPlayerCrew(AddCharacterToPlayerCrewScript * command);
	void p_processCreateWeaponModule(CreateWeaponModuleScript * command);
	void p_processEditWeaponModuleProperties(EditWeaponModulePropertiesScript * command);
	void p_processCalcParamStd(CalcParamStdScript * command);
	void p_processCreateShop(CreateShopScript * command);
	void p_processAddGoodsToShop(AddGoodsToShopScript * command);
	void p_processShowShop(ShowShopScript * command);
	void p_processCreateShip(CreateShipScript * command);
	void p_processEditShipStats(EditShipStatsScript * command);
	void p_processAddSlotToShip(AddSlotToShipScript * command);

};

extern ScriptSystem * scriptSystem;

