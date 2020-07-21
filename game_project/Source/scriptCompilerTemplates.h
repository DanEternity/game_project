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
		BaseScript * PutToPointer(CompilerCommandTemplateDataBuffer * buffer);  // ok
		BaseScript * AddToRewardBuffer(CompilerCommandTemplateDataBuffer * buffer);  // not ok - Do not completed
		BaseScript * Call(CompilerCommandTemplateDataBuffer * buffer); // ok - tested partially
		BaseScript * PutFromPointer(CompilerCommandTemplateDataBuffer * buffer); // ok
		BaseScript * Random(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * CreateSysModule(CompilerCommandTemplateDataBuffer * buffer); // work
		BaseScript * CreateModStatEffect(CompilerCommandTemplateDataBuffer * buffer); // work - not full tested
		BaseScript * ApplyEffect(CompilerCommandTemplateDataBuffer * buffer); // ? - not used for now
		BaseScript * ApplyEffectToSysModule(CompilerCommandTemplateDataBuffer * buffer); // work
		BaseScript * PutItemToPlayerInventory(CompilerCommandTemplateDataBuffer * buffer); // work
		BaseScript * EditItemProperties(CompilerCommandTemplateDataBuffer * buffer); // ? // work
		BaseScript * EditModuleProperties(CompilerCommandTemplateDataBuffer * buffer); // ? // work
		BaseScript * EditItemConstructableProperties(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * IfDoJump(CompilerCommandTemplateDataBuffer * buffer); // ? // work
		BaseScript * CreateResourceItem(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * CreateEquipmentItem(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * ApplyEffectToEquipment(CompilerCommandTemplateDataBuffer * buffer); // work
		BaseScript * EditEquipmentProperties(CompilerCommandTemplateDataBuffer * buffer); // work // not finished
		BaseScript * CreatePool(CompilerCommandTemplateDataBuffer * buffer); // work
		BaseScript * AddToPool(CompilerCommandTemplateDataBuffer * buffer); // not fully testd // work
		BaseScript * GetFromPool(CompilerCommandTemplateDataBuffer * buffer); // not fully tested // work
		BaseScript * StringConcat(CompilerCommandTemplateDataBuffer * buffer); // work
		BaseScript * CreateExternalTable(CompilerCommandTemplateDataBuffer * buffer); // work
		BaseScript * PutToExternalTable(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * PutFromExternalTable(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * CreateMarker(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * AddMarkerToSector(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * EditMarkerProperties(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * CallMarkerInitialization(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * LinkScriptToMarker(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * SetMarkerPosition(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * CreateDecoration(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * AddDecorationToSector(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * AddBackgroundToSector(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * EquipModule(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * Abs(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * GetShipStat(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * GetResourceCountFromPlayerInventory(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * RemoveResourcesFromPlayerInventory(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * AddMoney(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * RemoveMoney(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * GetCharacterStat(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * InitCharacterStats(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * CreateCharacter(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * AddCharacterToPlayerCrew(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * CreateWeaponModule(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * EditWeaponModuleProperties(CompilerCommandTemplateDataBuffer * buffer); // ?
		BaseScript * CalcParamStd(CompilerCommandTemplateDataBuffer * buffer); //
		BaseScript * CreateShop(CompilerCommandTemplateDataBuffer * buffer); //
		BaseScript * AddGoodsToShop(CompilerCommandTemplateDataBuffer * buffer); //
		BaseScript * ShowShop(CompilerCommandTemplateDataBuffer * buffer); //
	}

	namespace afterUpdateHandler 
	{
		// put doesn't need post update // its just example
		//void Put(CompilerCommandTemplateDataBuffer * buffer, BaseScript * p);

		void Jump(CompilerCommandTemplateDataBuffer * buffer, BaseScript * p1);
		void Choose(CompilerCommandTemplateDataBuffer * buffer, BaseScript * p1);
		void ChangeScriptEntryPoint(CompilerCommandTemplateDataBuffer * buffer, BaseScript * p1);
		void IfDoJump(CompilerCommandTemplateDataBuffer * buffer, BaseScript * p1);
	}

}