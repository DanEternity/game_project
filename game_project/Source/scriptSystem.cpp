#include "scriptSystem.h"

#include "enviroment.h"
#include "envUtils.h"
#include "scriptMemoryUtils.h"

void ScriptSystem::updateScriptEngine()
{

	if (gEnv->game.scriptSystemRequiresUpdate)
	{
		if (gEnv->scripts.task == L"notInitialized")
		{

			// init

			chooseUI = new ChooseUI("auto");
			chooseUI->setVisible(false);
			//gEnv->scripts.scriptGui.get<tgui::TextBox>(L"scriptTextMessage")->setVisible(false);

			gEnv->scripts.task = L"ready";

		}

		if (gEnv->scripts.task == L"ready")
		{

			p_processFrame();

		}

	}
	
	if (p_s != p_sysStatus::idle)
	{
		gEnv->scripts.active = 2;
	}
	else
		gEnv->scripts.active = std::max(0, gEnv->scripts.active - 1);

}

void ScriptSystem::p_processFrame()
{

	//
	// 
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//

	switch (p_s)
	{
	case p_sysStatus::idle:
		{
			// check for new script
			if (gEnv->scripts.queue.empty())
				break;
			auto * sd = gEnv->scripts.queue.front();
			this->p_l = sd->returnPoint;
			this->p_nl = sd->returnPoint;
			this->p_d = sd->scriptId;
			this->p_d->localMemory = sd->localMemory;
			if (sd->rContext != NULL)
				_RetFunction(sd);
			gEnv->scripts.queue.pop_front();
			delete(sd);
			gEnv->scripts.currentScript = p_d;
			p_s = p_sysStatus::processingScript;

			p_blockGame_ScriptRunning();
		}
		break;
	case p_sysStatus::processingScript:

		p_processScriptDescriptor();

		break;
	case p_sysStatus::scriptTerminated:

		if (true)
		{
			p_blockGame_ScriptRunning(false);
			p_s = p_sysStatus::idle;
			gEnv->scripts.currentScript = NULL;
		}

		break;
	case p_sysStatus::scriptWaitForReaction:

		p_processScriptDescriptor();

		break;
	default:
		break;
	}

}

void ScriptSystem::p_processScriptDescriptor()
{

	p_terminate = false;

	int time = 0;

	while (time < MAX_COMMANDS_LIMIT && !p_terminate)
	{

		time++;

		int targetLineId = p_nl;

		p_l = targetLineId;

		if (targetLineId >= p_d->scriptLines.size() && targetLineId >= 0)
		{
			// Out of range
			// Terminate
			if (debugMode)
				printf("Debug: Error! Script pointer was out of range\n");

			p_s = p_sysStatus::scriptTerminated;

			return;
		}

		BaseScript * line = p_d->scriptLines[targetLineId];

		p_nl++;

		p_processCommand(line);

		if (p_s == p_sysStatus::scriptWaitForReaction)
			break;

		p_chached = false;

	}

	if (time == 10000)
	{
		if (debugMode)
			printf("Debug: Error! Script commands limit exceeded (%i). Script was terminated. \n", MAX_COMMANDS_LIMIT);
	}

}

void ScriptSystem::p_processCommand(BaseScript * command)
{

	auto sType = command->scriptType;

	switch (sType)
	{
	case scriptType::null:
		// ???
		printf("Debug: Error! Script commands has type ::null");
		break;
	case scriptType::text:
		p_processText(static_cast<TextScript*>(command));
		break;
	case scriptType::put:
		p_processPut(static_cast<PutScript*>(command));
		break;
	case scriptType::choose:
		p_processChoose(static_cast<ChooseScript*>(command));
		break;
	case scriptType::terminate:
		p_processTerminate(static_cast<TerminateScript*>(command));
		break;
	case scriptType::ariphmetic:
		p_processAriphmetic(static_cast<AriphmeticScript*>(command));
		break;
	case scriptType::jump:
		p_processJump(static_cast<JumpScript*>(command));
		break;
	case scriptType::ifDoJump:
		p_processIfDoJump(static_cast<IfDoJumpScript*>(command));
		break;
	case scriptType::changeScriptEntryPoint:
		p_processChangeScriptEntryPoint(static_cast<ChangeScriptEntryPointScript*>(command));
		break;
	case scriptType::spendTime:
		p_processSpendTime(static_cast<SpendTimeScript*>(command));
		break;
	case scriptType::initRewardBuffer:
		p_processInitRewardBuffer(static_cast<InitRewardBufferScript*>(command));
		break;
	case scriptType::putToPointer:
		p_processPutToPointer(static_cast<PutToPointerScript*>(command));
		break;
	case scriptType::call:
		p_processCall(static_cast<CallScript*>(command));
		break;
	case scriptType::putFromPointer:
		p_processPutFromPointer(static_cast<PutFromPointerScript*>(command));
		break;
	case scriptType::random:
		p_processRandom(static_cast<RandomScript*>(command));
		break;
	case scriptType::createSysModule:
		p_processCreateSysModule(static_cast<CreateSysModuleScript*>(command));
		break;
	case scriptType::createModStatEffect:
		p_processCreateModStatEffect(static_cast<CreateModStatEffectScript*>(command));
		break;
	case scriptType::applyEffectToSysModule:
		p_processApplyEffectToSysModule(static_cast<ApplyEffectScript*>(command));
		break;
	case scriptType::putItemToPlayerInventory:
		p_processPutItemToPlayerInventory(static_cast<PutItemToPlayerInventoryScript*>(command));
		break;
	case scriptType::editItemProperties:
		p_processEditItemProperties(static_cast<EditItemPropertiesScript*>(command));
		break;
	case scriptType::editModuleProperties:
		p_processEditModuleProperties(static_cast<EditModulePropertiesScript*>(command));
		break;
	case scriptType::editItemConstructableProperties:
		p_processEditItemConstructableProperties(static_cast<EditItemConstructablePropertiesScript*>(command));
		break;
	case scriptType::createResourceItem:
		p_processCreateResourceItem(static_cast<CreateResourceItemScript*>(command));
		break;
	case scriptType::editEquipmentProperties:
		p_processEditEquipmentProperties(static_cast<EditEquipmentPropertiesScript*>(command));
		break;
	case scriptType::createEquipmentItem:
		p_processCreateEquipmentItem(static_cast<CreateEquipmentItemScript*>(command));
		break;
	case scriptType::applyEffectToEquipment:
		p_processApplyEffectEquipment(static_cast<ApplyEffectScript*>(command));
		break;
	case scriptType::getFromPool:
		p_processGetFromPool(static_cast<GetFromPoolScript*>(command));
		break;
	case scriptType::addToPool:
		p_processAddToPool(static_cast<AddToPoolScript*>(command));
		break;
	case scriptType::createPool:
		p_processCreatePool(static_cast<CreatePoolScript*>(command));
		break;
	case scriptType::stringConcat:
		p_processStringConcat(static_cast<StringConcatScript*>(command));
		break;
	case scriptType::createExternalTable:
		p_processCreateExternalTable(static_cast<CreateExternalTableScript*>(command));
		break;
	case scriptType::putFromExternalTable:
		p_processPutFromExternalTable(static_cast<PutFromExternalTableScript*>(command));
		break;
	case scriptType::putToExternalTable:
		p_processPutToExternalTable(static_cast<PutToExternalTableScript*>(command));
		break;
	case scriptType::createMarker:
		p_processCreateMarker(static_cast<CreateMarkerScript*>(command));
		break;
	case scriptType::addMarkerToSector:
		p_processAddMarkerToSector(static_cast<AddMarkerToSectorScript*>(command));
		break;
	case scriptType::editMarkerProperties:
		p_processEditMarkerProperties(static_cast<EditMarkerPropertiesScript*>(command));
		break;
	case scriptType::callCustom:
		p_processCallCustom(static_cast<CallCustomScript*>(command));
		break;
	case scriptType::linkScriptToMarker:
		p_processLinkScriptToMarker(static_cast<LinkScriptToMarkerScript*>(command));
		break;
	case scriptType::setMarkerPosition:
		p_processSetMarkerPosition(static_cast<SetMarkerPositionScript*>(command));
		break;
	case scriptType::createDecoration:
		p_processCreateDecoration(static_cast<CreateDecorationScript*>(command));
		break;
	case scriptType::addDecorationToSector:
		p_processAddDecorationToSector(static_cast<AddDecorationToSectorScript*>(command));
		break;
	case scriptType::addBackgroundToSector:
		p_processAddBackgroundToSector(static_cast<AddBackgroundToSectorScript*>(command));
		break;
	case scriptType::equipModule:
		p_processEquipModule(static_cast<EquipModuleScript*>(command));
		break;
	default:
		printf("Debug: ScriptSystem Error! Script command has unknown type -> %i", sType);
		break;
	}

}

void ScriptSystem::p_blockGame_ScriptRunning(bool mode)
{

	if (mode)
	{
		gEnv->game.gameModesRequiredUpdate = false;
		gEnv->game.menuOverlayRequiresUpdate = true;
	}
	else
	{
		gEnv->game.gameModesRequiredUpdate = true;
	}

}

void ScriptSystem::p_blockGame_WaitForReaction(bool mode)
{
	gEnv->scripts.scriptGuiEventsRequiresUpdate = mode;
}

std::wstring ScriptSystem::p_convertText(std::wstring src)
{

	std::wstring res = L"";

	for (int i(0); i < src.size(); i++)
	{

		if (src[i] != '$')
		{
			res += src[i];
			continue;
		}

		// looking for first space

		int right = src.find_first_of(L" ", i);
		if (right <= 0)
			right = src.size();

		std::wstring fragment = p_convertValueToString(src.substr(i, right - i));

		i = right;

		res += fragment;

	}

	return res;
}

std::wstring ScriptSystem::p_convertValueToString(std::wstring src)
{

	// $value

	std::wstring result = L"";

	if (src.size() <= 1) // nothing to convert
		return L"";

	// start from digit or _ means local memory
	if ((src[2] >= '0' && src[2] <= '9') || src[1] == '_')
	{

		// attempting to extract memory data

		BaseObject * target;
		auto code = getMemoryCellFromLocalMemory(&p_d->localMemory, src.substr(2, src.size() - 2), &target);
		
		if (code != memoryUtil::ok)
			return L"NULL";

		code = convertToString(target, result);

		if (code != memoryUtil::ok)
			return L"NULL";

		return result;

	}

	if (src.find(L"$EXT:") != std::wstring::npos)
	{

		// external table

		BaseObject * target;
		int posLeft, posRight;
		try
		{
			posLeft = src.find(L':', 0);
			posRight = src.find(L':', posLeft + 1);
		}
		catch (const std::exception&)
		{
			return L"NULL";
		}
		auto code = getMemoryCellFromExternalTable(src.substr(5, posRight-posLeft-1), src.substr(posRight+1, src.size() - posRight), &target);

		if (code != memoryUtil::ok)
			return L"NULL";

		code = convertToString(target, result);

		if (code != memoryUtil::ok)
			return L"NULL";

		return result;


	}

	// Game value or incorrect query

	BaseObject * target;
	auto code = getMemoryCellFromGameEnviroment(src.substr(1, src.size() - 1), &target);

	if (code != memoryUtil::ok)
		return L"NULL";

	code = convertToString(target, result);

	if (code != memoryUtil::ok)
		return L"NULL";

	if ((target->memoryControl | memoryControl::singleUse) != 0)
		delete target;

	return result;
}

bool ScriptSystem::p_calculateComporator(ComparatorElement * comparator)
{
	
	if (comparator->unaryComparator)
	{
		std::wstring res = L"";
		std::wstring val = comparator->left;
		if (val.size() <= 1)
			return false;
		if (val[0] == '$')
		{
			res = p_convertValueToString(val);
			if (res == L"1")
				res = L"true";
			else
				res = L"false";
		}
		else
		{
			res = val;
		}
		if (res == L"true" || res == L"True" || res == L"TRUE")
		{
			return true;
		}
		if (res == L"false" || res == L"False" || res == L"FALSE")
		{
			return false;
		}
	}
	else
	{
	//	std::wstring l_arg = p_convertValueToString(comparator->left);
	//	std::wstring r_arg = p_convertValueToString(comparator->right);

		std::wstring op = comparator->operation;
		bool error = false;

		float l = scriptUtil::getArgumentFloatValue(comparator->left, p_d, error);
		float r = scriptUtil::getArgumentFloatValue(comparator->right, p_d, error);

	//	float l = _wtof(l_arg.c_str());
	//	float r = _wtof(r_arg.c_str());

		if (error)
			return false;

		if (op == L"==")
		{
			return (l == r);
		}

		if (op == L"<")
		{
			return (l < r);
		}

		if (op == L">")
		{
			return (l > r);
		}

		if (op == L">=")
		{
			return (l >= r);
		}

		if (op == L"<=")
		{
			return (l <= r);
		}

		if (op == L"!=" || op == L"<>")
		{
			return (l != r);
		}
	}

	return false;
}

bool ScriptSystem::p_calculateExpression(BaseObject * left, BaseObject * right, std::wstring operation, BaseObject ** dest)
{

	auto tr = p_getNumResultType(left, right, operation);
	if (tr == objectType::undefined)
		return false;
	
	float resultF = 0;
	int resultI = 0;

	float leftF = 0;
	float rightF = 0;
	int leftI = 0;
	int rightI = 0;

	if (tr == objectType::real)
	{
		*dest = new FloatObject();
		(*dest)->memoryControl = memoryControl::singleUse;

		if (left->objectType == objectType::integer)
			leftF = static_cast<IntObject*>(left)->value;
		else
			leftF = static_cast<FloatObject*>(left)->value;

		if (right->objectType == objectType::integer)
			rightF = static_cast<IntObject*>(right)->value;
		else
			rightF = static_cast<FloatObject*>(right)->value;
	}
	else
	{
		*dest = new IntObject();
		(*dest)->memoryControl = memoryControl::singleUse;

		leftI = static_cast<IntObject*>(left)->value;

		rightI = static_cast<IntObject*>(right)->value;


	}

	if (operation == L"+")
	{
		if ((*dest)->objectType == objectType::real)
			static_cast<FloatObject*>(*dest)->value = leftF + rightF;
		else
			static_cast<IntObject*>(*dest)->value = leftI + rightI;
	}

	if (operation == L"-")
	{
		if ((*dest)->objectType == objectType::real)
			static_cast<FloatObject*>(*dest)->value = leftF - rightF;
		else
			static_cast<IntObject*>(*dest)->value = leftI - rightI;
	}

	if (operation == L"*")
	{
		if ((*dest)->objectType == objectType::real)
			static_cast<FloatObject*>(*dest)->value = leftF * rightF;
		else
			static_cast<IntObject*>(*dest)->value = leftI * rightI;
	}

	if (operation == L"/")
	{
		if ((*dest)->objectType == objectType::real)
		{
			if (rightF < 0.000001)
			{
				printf("Error! Ariphmetic script - Division by zero\n");
				delete *dest;
				return false;
			}
		}
		else
		{
			if (rightI == 0)
			{
				printf("Error! Ariphmetic script - Division by zero\n");
				delete *dest;
				return false;
			}
		}
		if ((*dest)->objectType == objectType::real)
			static_cast<FloatObject*>(*dest)->value = leftF / rightF;
		else
			static_cast<IntObject*>(*dest)->value = leftI / rightI;
	}

	if (operation == L"%")
	{
		if ((*dest)->objectType == objectType::real)
		{
			if (rightF < 0.000001)
			{
				printf("Error! Ariphmetic script - Division by zero\n");
				delete *dest;
				return false;
			}
		}
		else
		{
			if (rightI == 0)
			{
				printf("Error! Ariphmetic script - Division by zero\n");
				delete *dest;
				return false;
			}
		}
		if ((*dest)->objectType == objectType::real)
		{
			printf("Error! Ariphmetic script - Cannot perform reamainder of the division operation - argument should be int\n");
			delete *dest;
			return false;
		}
		else
			static_cast<IntObject*>(*dest)->value = leftI % rightI;
	}

	return true;
}

objectType::ObjectType ScriptSystem::p_getNumResultType(BaseObject * left, BaseObject * right, std::wstring operation)
{

	if (left == NULL || right == NULL)
		return objectType::undefined;

	auto t1 = left->objectType;
	auto t2 = right->objectType;

	if ((t1 != objectType::integer && t1 != objectType::real) || (t2 != objectType::integer && t2 != objectType::real))
	{
		return objectType::ObjectType(objectType::undefined);
	}

	if (t1 == objectType::real || t2 == objectType::real)
	{
		return objectType::real;
	}
	else
		if (operation == L"/")
		{
			return objectType::real;
		}
		else
			return objectType::integer;

	return objectType::ObjectType(objectType::undefined);
}

std::wstring ScriptSystem::p_getLocalMemoryCellAsString(std::wstring idx)
{

	if (p_d->localMemory.find(idx) == p_d->localMemory.end())
		return L"NULL";

	auto obj = p_d->localMemory[idx];

	std::wstring res = L"";

	switch (obj->objectType)
	{
	case objectType::integer:
		res = std::to_wstring(static_cast<IntObject*>(obj)->value);
		break;
	case objectType::real:
		res = std::to_wstring(static_cast<FloatObject*>(obj)->value);
		break;
	case objectType::boolean:
		res = std::to_wstring(static_cast<BooleanObject*>(obj)->value);
		break;
	case objectType::string:
		res = static_cast<StringObject*>(obj)->value;
		break;
	default:
		break;
	}

	return res;
}

std::wstring ScriptSystem::p_getExternalTableValueAsString(std::wstring tableId, std::wstring idx)
{
	return std::wstring();
}

std::wstring ScriptSystem::p_getGlobalValueAsString(std::wstring ValueName)
{
	return std::wstring();
}

bool ScriptSystem::GetObjectOrConstFromMemory(std::wstring src, BaseObject ** obj)
{

	*obj = NULL;

	// check if src is const
	if (src.size() >= 1)
	{
		if (src[0] != '$')
		{
			// value is const
			auto code = convertConstToObject(src, obj);
			if (code != memoryUtil::ok)
			{
				// failed
				return false;
			}
		}
		else
		{
			// get src object if not a const
			auto code = getMemoryCell(src, obj, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return false;
			}
		}
	}
	else
	{
		// failed
		// no source provided
		return false;
	}

	return true;

}

void ScriptSystem::_CallFunction(StackElement * target, int entryPoint, RetContext * retContext)
{

	auto * ret = new StackElement();
	ret->returnPoint = p_nl;
	ret->scriptId = p_d;
	ret->localMemory = p_d->localMemory;
	ret->rContext = retContext;
	gEnv->scripts.queue.push_front(ret);

	auto * p = target;
	p->returnPoint = entryPoint;
	//p->scriptId;
	//p->localMemory;
	//p->localMemory.clear();
	gEnv->scripts.queue.push_front(p);

	// this should interrupt current script 
	p_s = p_sysStatus::scriptTerminated;
	p_terminate = true;

}

void ScriptSystem::_RetFunction(StackElement * target)
{

	if (debugMode)
	{
		printf("Returning from function. Recovering context...\n");
	}

	auto ctx = target->rContext;

	if (ctx == NULL)
		return;

	for (int i(0); i < ctx->srcVarLink.size(); i++)
	{
		if (ctx->srcVarLink[i] != L"")
		{
			BaseObject * tmp = NULL;
			std::wstring qs = L"$EXT:" + ctx->linkTable + L":" + std::to_wstring(i);
			auto code = getMemoryCell(qs, &tmp, NULL);
			if (code != memoryUtil::ok)
			{
				// failed
				// Do not copy element
				continue;
			}
			putMemoryCell(ctx->srcVarLink[i], tmp, &p_d->localMemory);
			
		}
	}

	deleteExternalTable(ctx->linkTable);
	delete(target->rContext);

}

void ScriptSystem::p_processText(TextScript * command)
{

	// Need to block/pause game

	p_blockGame_WaitForReaction();
	p_s = p_sysStatus::scriptWaitForReaction;

	// Draw text OwO
	std::wstring text;
	if (!p_chached)
	{
		text = p_convertText(command->text);
		p_textChache = text;
		p_chached = true;
		gEnv->scripts.buttonPressed = false;
		gEnv->scripts.scriptGui.get<tgui::TextBox>(L"scriptTextMessage")->setVisible(true);
		gEnv->scripts.scriptGui.get<tgui::TextBox>(L"scriptTextMessage")->setText(text);
		gEnv->scripts.scriptGui.get<tgui::Button>(L"ScriptButtonNext")->setVisible(true);
		gEnv->scripts.scriptGui.get<tgui::Button>(L"ScriptButtonNext")->setEnabled(true);
		//gEnv->scripts.scriptGui.get<tgui::Button>(L"ScriptButtonNext")->setText(text);
		if (false)
			wprintf(L"TEST: %ws \n", text.c_str());
	}
	else
		text = p_textChache;

	



	// Check buttons

	if (gEnv->scripts.buttonPressed)
	{
		p_chached = false;
		p_blockGame_WaitForReaction(false);
		p_s = p_sysStatus::processingScript;
		gEnv->scripts.scriptGui.get<tgui::TextBox>(L"scriptTextMessage")->setVisible(false);
		gEnv->scripts.scriptGui.get<tgui::Button>(L"ScriptButtonNext")->setVisible(false);
		gEnv->scripts.scriptGui.get<tgui::Button>(L"ScriptButtonNext")->setEnabled(false);
	}
	else
	{

		p_nl = p_l;

	}
}

void ScriptSystem::p_processPut(PutScript * command)
{

	auto src = command->scr;
	auto dst = command->dest;

	BaseObject * obj = NULL;

	// check if src is const
	if (src.size() >= 1)
	{
		if (src[0] != '$') 
		{
			// value is const
			auto code = convertConstToObject(src, &obj);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
		else
		{
			// get src object if not a const
			auto code = getMemoryCell(src, &obj, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
	}
	else
	{
		// failed
		// no source provided
		return;
	}

	auto code = putMemoryCell(dst, obj, &p_d->localMemory);

	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

}

void ScriptSystem::p_processChoose(ChooseScript * command)
{
	// Need to block/pause game

	p_blockGame_WaitForReaction();
	p_s = p_sysStatus::scriptWaitForReaction;
	// chache check

	std::wstring text;

	if (!p_chached)
	{
		
		chooseUI->deleteButtons();
		chooseUI->setVisible(true);
		chooseUI->initButtons(command->variants.size());


		for (int i(0); i < command->variants.size(); i++)
		{
			auto elem = command->variants[i];
			bool active = p_calculateComporator(&elem.comp);
			std::wstring text = p_convertText(elem.textLine);
			chooseUI->setButton(i, text, active);
		}


		text = p_convertText(command->text);
		p_textChache = text;
		p_chached = true;
		gEnv->scripts.scriptGui.get<tgui::TextBox>(L"scriptTextMessage")->setVisible(true);
		gEnv->scripts.scriptGui.get<tgui::TextBox>(L"scriptTextMessage")->setText(text);
		gEnv->scripts.scriptGui.get<tgui::TextBox>(L"scriptTextMessage")->setCaretPosition(0);
		gEnv->scripts.scriptGui.get<tgui::TextBox>(L"scriptTextMessage")->setReadOnly(true);
		gEnv->scripts.buttonPressed = false;
	}
	else
		text = p_textChache;

	// Check buttons

	if (gEnv->scripts.buttonPressed)
	{
		gEnv->scripts.buttonPressed = false;
		p_blockGame_WaitForReaction(false);
		// change line
		int id = gEnv->scripts.buttonId;
		p_nl = command->variants[id].jump;
		p_s = p_sysStatus::processingScript;
		p_chached = false;
		chooseUI->deleteButtons();
		chooseUI->setVisible(false);
		gEnv->scripts.scriptGui.get<tgui::TextBox>(L"scriptTextMessage")->setVisible(false);
	}
	else
	{

		p_nl = p_l;

	}

}

void ScriptSystem::p_processTerminate(TerminateScript * command)
{

	p_s = p_sysStatus::scriptTerminated;
	p_terminate = true;

}

void ScriptSystem::p_processJump(JumpScript * command)
{

	p_nl = command->lineId;

}

void ScriptSystem::p_processAriphmetic(AriphmeticScript * command)
{

	auto src = command->left;
	auto dst = command->dest;

	BaseObject * objLeft = NULL;
	BaseObject * objRight = NULL;

	// Collecting left operand
	// check if src is const
	if (src.size() >= 1)
	{
		if (src[0] != '$')
		{
			// value is const
			auto code = convertConstToObject(src, &objLeft);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
		else
		{
			// get src object if not a const
			auto code = getMemoryCell(src, &objLeft, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
	}
	else
	{
		// failed
		// no source provided
		return;
	}

	src = command->right;

	// Collecting right operand
	// check if src is const
	if (src.size() >= 1)
	{
		if (src[0] != '$')
		{
			// value is const
			auto code = convertConstToObject(src, &objRight);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
		else
		{
			// get src object if not a const
			auto code = getMemoryCell(src, &objRight, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
	}
	else
	{
		// failed
		// no source provided
		return;
	}

	auto op = command->operation;
	BaseObject * objResult = NULL;

	bool result = p_calculateExpression(objLeft, objRight, op, &objResult);

//	delete objLeft;
//	delete objRight;

	if (!result)
		return;

	auto code = putMemoryCell(dst, objResult, &p_d->localMemory);

	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

}

void ScriptSystem::p_processIfDoJump(IfDoJumpScript * command)
{

	bool result = p_calculateComporator(&command->condition);

	if (result)
	{
		p_nl = command->lineId;
	}

}

void ScriptSystem::p_processChangeScriptEntryPoint(ChangeScriptEntryPointScript * command)
{
	/*if (command->scriptId == L"" || command->scriptId == L"$self")
	{
		// ���-��
	}
	else
	{
		// doesnt work xd
	}*/

	auto src = command->scriptId;

	BaseObject * obj = NULL;

	// check if src is const
	if (src.size() >= 1)
	{
		if (src[0] != '$')
		{
			// Const not allowed
			// failed
			return;

		}
		else
		{
			// get src object if not a const
			auto code = getMemoryCell(src, &obj, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
	}
	else
	{
		// failed
		// no source provided
		return;
	}

	auto tp = obj->objectType;

	if (tp == objectType::scriptDescriptor)
	{
		auto sd = static_cast<ScriptDescriptor*>(obj);
		sd->entryPoint = command->lineId;
	}
	else
	{
		// failed
		return;
	}

}

void ScriptSystem::p_processSpendTime(SpendTimeScript * command)
{

	auto t = command->amount;

	if (t == L"1/4day")
	{
		gEnv->game.adventureData.gameTime += 6;
		return;
	}
	if (t == L"1/2day")
	{
		gEnv->game.adventureData.gameTime += 12;
		return;
	}
	if (t == L"1day")
	{
		gEnv->game.adventureData.gameTime += 24;
		return;
	}
	
	int p = _wtoi(t.c_str());

	gEnv->game.adventureData.gameTime += p;

}

void ScriptSystem::p_processInitRewardBuffer(InitRewardBufferScript * command)
{
	printf("Initializing reward buffer...\n");

	// Code goes here...

}

void ScriptSystem::p_processPutToPointer(PutToPointerScript * command)
{

	auto src = command->src;
	auto dst = command->dst;

	BaseObject * destObject = NULL;

	if (dst.size() >= 1)
	{
		if (dst[0] == '$')
		{
			auto code = getMemoryCell(dst, &destObject, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
		else
		{
			// failed
			return;
		}
	}
	else
	{
		// failed
		return;
	}

	auto tp = destObject->objectType;

	if (tp == objectType::string)
	{
		auto v_dst = static_cast<StringObject*>(destObject);
		dst = v_dst->value;
	}
	else
	{
		// failed
		return;
	}

	BaseObject * obj = NULL;

	// check if src is const
	if (src.size() >= 1)
	{
		if (src[0] != '$')
		{
			// value is const
			auto code = convertConstToObject(src, &obj);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
		else
		{
			// get src object if not a const
			auto code = getMemoryCell(src, &obj, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
	}
	else
	{
		// failed
		// no source provided
		return;
	}

	auto code = putMemoryCell(dst, obj, &p_d->localMemory);

	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}



}

void ScriptSystem::p_processCall(CallScript * command)
{
	
	auto dst = command->scriptId;
	BaseObject * destObject = NULL;

	if (dst.size() >= 1)
	{
		if (dst[0] == '$')
		{
			auto code = getMemoryCell(dst, &destObject, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
		else
		{
			// failed
			return;
		}
	}

	auto tp = destObject->objectType;

	if (tp != objectType::scriptDescriptor)
	{
		if (debugMode)
		{
			wprintf(L"Error! Failed to call [%s] function. Invalid descriptor or adress not correct\n", dst.c_str());
		}
		// failed
		return;
	}

	ScriptDescriptor * target = static_cast<ScriptDescriptor*>(destObject);
	StackElement * t = new StackElement();
	t->localMemory.clear();
	RetContext * retContext = new RetContext();
	auto extTable = createExternalTable();
	//t->rContext = retContext;
	
	retContext->linkTable = extTable;

	for (int i(0); i < command->arg.size(); i++)
	{

		std::wstring eDest = L"$EXT:" + extTable + L":" + std::to_wstring(i);

		if (command->arg[i].size() > 0)
		{
			if (command->arg[i][0] == '$')
			{
				retContext->srcVarLink.push_back(command->arg[i]);
				BaseObject * qsrc = NULL;
				auto code = getMemoryCell(command->arg[i], &qsrc, &p_d->localMemory);
				if (code != memoryUtil::ok)
				{
					// Operation can be failed because we want to share a pointer to memory
					// but not actual object. Thats mean that we cannot use actual object here

					// So there shouldn't be return function

					// failed
					return;
				}
				code = putMemoryCell(eDest, qsrc, &p_d->localMemory);
				if (code != memoryUtil::ok)
				{
					// failed
					return;
				}

			}
			else
				retContext->srcVarLink.push_back(L"");
		}
		else
			retContext->srcVarLink.push_back(L"");

		StringObject * obj = new StringObject();
		obj->memoryControl = memoryControl::free;
		if (command->arg[i].size() > 0)
		{
			if (command->arg[i][0] == '$')
			{
				obj->value = eDest;
			}
			else
				obj->value = command->arg[i];
		}
		else
			obj->value = command->arg[i];
		std::wstring ndst = L"$_arg" + std::to_wstring(i);
		auto code = putMemoryCell(ndst, obj, &t->localMemory);
		if (code != memoryUtil::ok)
		{
			// failed
			return;
		}	
	}

	//target->localMemory;

	if (debugMode)
	{
		wprintf(L"Calling a function [%s].\n", dst.c_str());
	}

	t->scriptId = target;

	_CallFunction(t, target->entryPoint, retContext);

}

void ScriptSystem::p_processPutFromPointer(PutFromPointerScript * command)
{

	auto src = command->src;
	auto dst = command->dst;

	// Extracting real src adress

	BaseObject * srcObject = NULL;

	if (src.size() >= 1)
	{
		if (src[0] == '$')
		{
			auto code = getMemoryCell(src, &srcObject, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
		else
		{
			// failed
			return;
		}
	}
	else
	{
		// failed
		return;
	}

	auto tp = srcObject->objectType;

	if (tp == objectType::string)
	{
		auto v_src = static_cast<StringObject*>(srcObject);
		src = v_src->value;
	}
	else
	{
		// failed
		return;
	}

	// Performing put operation

	BaseObject * obj = NULL;

	// check if src is const
	if (src.size() >= 1)
	{
		if (src[0] != '$')
		{
			// value is const
			auto code = convertConstToObject(src, &obj);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
		else
		{
			// get src object if not a const
			auto code = getMemoryCell(src, &obj, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
	}
	else
	{
		// failed
		// no source provided
		return;
	}

	auto code = putMemoryCell(dst, obj, &p_d->localMemory);

	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}


}

void ScriptSystem::p_processRandom(RandomScript * command)
{
	auto r = getRand();
	auto dst = command->dst;
	IntObject * obj = new IntObject(r);
	obj->memoryControl = memoryControl::singleUse;
	auto code = putMemoryCell(dst, obj, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}
}

void ScriptSystem::p_processCreateSysModule(CreateSysModuleScript * command)
{

	auto dst = command->dst;

	// create item
	// need to store in global item db

	int id = gEnv->objects.nextItemId++;
	Module * obj = new Module;
	gEnv->objects.items[id] = obj;
	obj->name = command->name;

	auto code = putMemoryCell(dst, obj, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

}

void ScriptSystem::p_processCreateModStatEffect(CreateModStatEffectScript * command)
{

	// I probably need to delete obj if creation failed
	// because it will lose memory instead

	std::wstring dst = command->dst;

	int id = gEnv->objects.nextEffectId++;
	StatModEffect * obj = new StatModEffect();
	
	auto tp = command->objectType;

	BaseObject * targetTypeP = NULL;
	if (!GetObjectOrConstFromMemory(command->targetType, &targetTypeP))
	{
		// failed
		delete(obj);
		return;
	}
	if (targetTypeP->objectType != objectType::string)
	{
		// failed
		delete(obj);
		return;
	}

	std::wstring targetType = static_cast<StringObject*>(targetTypeP)->value;
	if (targetType == L"ship" || targetType == L"Ship")
		obj->targetType = targetType::ship;
	if (targetType == L"character" || targetType == L"Character")
		obj->targetType = targetType::character;
	delete(targetTypeP);

	// other fields

	bool error = false;

	float p_add = scriptUtil::getArgumentFloatValue(command->p_add, p_d, error);
	if (error)
	{
		// failed
		return;
	}
	float p_mul = scriptUtil::getArgumentFloatValue(command->p_mul, p_d, error);
	if (error)
	{
		// failed
		return;
	}
	float p_sub = scriptUtil::getArgumentFloatValue(command->p_sub, p_d, error);
	if (error)
	{
		// failed
		return;
	}
	float p_negMul = scriptUtil::getArgumentFloatValue(command->p_negMul, p_d, error);
	if (error)
	{
		// failed
		return;
	}

	BaseObject * statNameP = NULL;
	if (!GetObjectOrConstFromMemory(command->statName, &statNameP))
	{
		// failed
		return;
	}
	if (statNameP->objectType != objectType::string)
	{
		// failed
		return;
	}

	std::wstring statName = static_cast<StringObject*>(statNameP)->value;
	
	// need convert string to enum
	
	obj->statName = scriptUtil::getFromStringStatName(statName);
	if (statNameP->singleUse())
		delete (statNameP);

	obj->p_add = p_add;
	obj->p_mul = p_mul;
	obj->p_negMul = p_negMul;
	obj->p_sub = p_sub;

	auto code = putMemoryCell(dst, obj, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	gEnv->objects.effects[id] = obj;

}

void ScriptSystem::p_processApplyEffectToSysModule(ApplyEffectScript * command)
{
	auto src = command->src;
	auto dst = command->dst;

	BaseObject * objSrc = NULL;

	auto code = getMemoryCell(src, &objSrc, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	BaseObject * objDst = NULL;
	code = getMemoryCell(dst, &objDst, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (objSrc->objectType != objectType::effect)
	{
		// failed
		return;
	}

	if (objDst->objectType != objectType::item)
	{
		// failed
		return;
	}
	else
	{
		if (static_cast<Item*>(objDst)->itemType != itemType::module)
		{
			// failed
			return;
		}
	}

	Module * trg = static_cast<Module*>(objDst);

	trg->effects.push_back(static_cast<EffectObject*>(objSrc));
}

void ScriptSystem::p_processPutItemToPlayerInventory(PutItemToPlayerInventoryScript * command)
{

	auto src = command->src;
	BaseObject * objSrc = NULL;

	auto code = getMemoryCell(src, &objSrc, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (objSrc->objectType != objectType::item)
	{
		// failed
		return;
	}

	for (int i(0); i<gEnv->game.player.inventory.size(); i++)
		if (gEnv->game.player.inventory[i] == NULL)
		{
			// successful
			gEnv->game.player.inventory[i] = static_cast<Item*>(objSrc);
			giveIconToItem(gEnv->game.player.inventory[i]);
			return;
		}

	// failed 
	//gEnv->game.player.inventory

}

void ScriptSystem::p_processEditItemProperties(EditItemPropertiesScript * command)
{

	auto src = command->src;
	BaseObject * objSrc = NULL;

	auto code = getMemoryCell(src, &objSrc, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (objSrc->objectType != objectType::item)
	{
		// failed
		return;
	}

	Item * obj = static_cast<Item*>(objSrc);

	bool error = false;
	int level = scriptUtil::getArgumentIntValue(command->level, p_d, error);
	int rarity = scriptUtil::getArgumentIntValue(command->rarity, p_d, error);
	int itemId = scriptUtil::getArgumentIntValue(command->itemId, p_d, error);
	std::wstring itemClass = scriptUtil::getArgumentStringValue(command->itemClass, p_d, error);
	std::wstring itemName = scriptUtil::getArgumentStringValue(command->itemName, p_d, error);

	if (error)
	{
		// failed
		return;
	}

	obj->level = level;
	obj->rarity = rarity;
	obj->itemId = itemId;
	obj->itemClass = "";
	for (int i(0); i < itemClass.size(); i++)
		obj->itemClass.push_back(itemClass[i]);

	obj->name = itemName;

}

void ScriptSystem::p_processEditModuleProperties(EditModulePropertiesScript * command)
{

	auto src = command->src;
	BaseObject * objSrc = NULL;

	auto code = getMemoryCell(src, &objSrc, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (objSrc->objectType != objectType::item)
	{
		// failed
		return;
	}
	Item * obj = static_cast<Item*>(objSrc);
	if (obj->itemType != itemType::module)
	{
		// failed
		return;
	}
	Module * p = static_cast<Module*>(obj);
	
	bool error = false;
	std::wstring moduleType = scriptUtil::getArgumentStringValue(command->moduleType, p_d, error);
	std::wstring moduleSlot = scriptUtil::getArgumentStringValue(command->moduleSlot, p_d, error);
	std::wstring moduleSize = scriptUtil::getArgumentStringValue(command->moduleSize, p_d, error);
	float powerSupply = scriptUtil::getArgumentFloatValue(command->powerSupply, p_d, error);
	float powerHighSupply = scriptUtil::getArgumentFloatValue(command->highPowerSupply, p_d, error);
	float powerPriority = scriptUtil::getArgumentFloatValue(command->powerPriority, p_d, error);

	if (error)
	{
		// failed
		return;
	}

	p->powerSupply = powerSupply;
	p->highPowerSupply = powerHighSupply;
	p->powerPriority = powerPriority;

	// Type
	if (moduleType == L"system" || moduleType == L"System")
		p->moduleType = moduleType::system;
	
	if (moduleType == L"special" || moduleType == L"Special")
		p->moduleType = moduleType::special;
	
	if (moduleType == L"weapon" || moduleType == L"Weapon")
		p->moduleType = moduleType::weapon;
	
	// Size
	if (moduleSlot == L"small" || moduleSlot == L"Small")
		p->size = moduleSlot::small;
	
	if (moduleSlot == L"medium" || moduleSlot == L"Medium")
		p->size = moduleSlot::medium;

	if (moduleSlot == L"large" || moduleSlot == L"Large")
		p->size = moduleSlot::large;

	if (moduleSlot == L"huge" || moduleSlot == L"Huge")
		p->size = moduleSlot::huge;

	// Slot type
	if (moduleSlot == L"core" || moduleSlot == L"Core")
		p->slot = moduleSlot::core;

	if (moduleSlot == L"engine" || moduleSlot == L"Engine")
		p->slot = moduleSlot::engine;

	if (moduleSlot == L"hyperdrive" || moduleSlot == L"Hyperdrive")
		p->slot = moduleSlot::hyperdrive;

	if (moduleSlot == L"system" || moduleSlot == L"System")
		p->slot = moduleSlot::system;

	if (moduleSlot == L"primaryWeapon" || moduleSlot == L"PrimaryWeapon")
		p->slot = moduleSlot::primaryWeapon;

	if (moduleSlot == L"secondaryWeapon" || moduleSlot == L"SecondaryWeapon")
		p->slot = moduleSlot::secondaryWeapon;

	if (moduleSlot == L"universal" || moduleSlot == L"Universal")
		p->slot = moduleSlot::universal;

}

void ScriptSystem::p_processEditItemConstructableProperties(EditItemConstructablePropertiesScript * command)
{

	auto src = command->src;
	BaseObject * objSrc = NULL;

	auto code = getMemoryCell(src, &objSrc, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (objSrc->objectType != objectType::item)
	{
		// failed
		return;
	}

	Item * obj = static_cast<Item*>(objSrc);

	// not a item constructable
	if (obj->itemType != itemType::module && obj->itemType != itemType::equipment)
	{
		// failed
		return;
	}

	ItemConstructable * p = static_cast<ItemConstructable*>(obj);

	bool error = false;

	int quality = scriptUtil::getArgumentIntValue(command->quality, p_d, error);
	int key = scriptUtil::getArgumentIntValue(command->key, p_d, error);
	std::wstring modifier = scriptUtil::getArgumentStringValue(command->modifier, p_d, error);

	if (error)
	{
		// failed
		return;
	}

	p->key = key;
	p->quality = quality;

	if (modifier == L"broken" || modifier == L"Broken")
		p->modifier = itemModifier::broken;

	if (modifier == L"bad" || modifier == L"Bad")
		p->modifier = itemModifier::bad;

	if (modifier == L"normal" || modifier == L"Normal")
		p->modifier = itemModifier::normal;

	if (modifier == L"upgrade1" || modifier == L"Upgrade1")
		p->modifier = itemModifier::upgrade1;

	if (modifier == L"upgrade2" || modifier == L"Upgrade2")
		p->modifier = itemModifier::upgrade2;

	if (modifier == L"legendary" || modifier == L"Legendary")
		p->modifier = itemModifier::legendary;

}

void ScriptSystem::p_processCreateResourceItem(CreateResourceItemScript * command)
{
	auto dst = command->dst;

	// create item
	// need to store in global item db

	int id = gEnv->objects.nextItemId++;
	ItemResource * obj = new ItemResource;
	gEnv->objects.items[id] = obj;

	bool error = false;
	
	obj->name = scriptUtil::getArgumentStringValue(command->name, p_d, error);
	obj->count = scriptUtil::getArgumentIntValue(command->count, p_d, error);
	obj->maxCount = scriptUtil::getArgumentIntValue(command->maxCount, p_d, error);

	auto code = putMemoryCell(dst, obj, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}
}

void ScriptSystem::p_processEditEquipmentProperties(EditEquipmentPropertiesScript * command)
{

	auto src = command->src;
	BaseObject * objSrc = NULL;

	auto code = getMemoryCell(src, &objSrc, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (objSrc->objectType != objectType::item)
	{
		// failed
		return;
	}

	Item * obj = static_cast<Item*>(objSrc);


	if ( obj->itemType != itemType::equipment)
	{
		// failed
		return;
	}

	Equipment * p = static_cast<Equipment*>(obj);

	bool error = false;

	std::wstring name = scriptUtil::getArgumentStringValue(command->name, p_d, error);
	std::wstring slot = scriptUtil::getArgumentStringValue(command->slot, p_d, error);

	if (error)
	{
		// failed
		return;
	}

	p->name = name;

	// slot
	if (slot == L"head" || slot == L"Head" || slot == L"4Head")
		p->equipmentSlotType = equipmentSlot::head;

	if (slot == L"body" || slot == L"Body")
		p->equipmentSlotType = equipmentSlot::body;

	if (slot == L"arms" || slot == L"Arms")
		p->equipmentSlotType = equipmentSlot::arms;

	if (slot == L"legs" || slot == L"Legs")
		p->equipmentSlotType = equipmentSlot::legs;

	if (slot == L"universal" || slot == L"Universal")
		p->equipmentSlotType = equipmentSlot::universal;

}

void ScriptSystem::p_processCreateEquipmentItem(CreateEquipmentItemScript * command)
{
	auto dst = command->dst;

	// create item
	// need to store in global item db

	int id = gEnv->objects.nextItemId++;
	Equipment * obj = new Equipment;
	gEnv->objects.items[id] = obj;
	obj->name = command->name;

	auto code = putMemoryCell(dst, obj, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

}

void ScriptSystem::p_processApplyEffectEquipment(ApplyEffectScript * command)
{
	auto src = command->src;
	auto dst = command->dst;

	BaseObject * objSrc = NULL;

	auto code = getMemoryCell(src, &objSrc, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	BaseObject * objDst = NULL;
	code = getMemoryCell(dst, &objDst, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (objSrc->objectType != objectType::effect)
	{
		// failed
		return;
	}

	if (objDst->objectType != objectType::item)
	{
		// failed
		return;
	}
	else
	{
		if (static_cast<Item*>(objDst)->itemType != itemType::equipment)
		{
			// failed
			return;
		}
	}

	Equipment * trg = static_cast<Equipment*>(objDst);

	trg->effects.push_back(static_cast<EffectObject*>(objSrc));
}

void ScriptSystem::p_processCreatePool(CreatePoolScript * command)
{
	auto dst = command->dst;

	// create item
	// need to store in global item db

	int id = gEnv->objects.nextPoolId;
	PoolObject * obj = new PoolObject;
	gEnv->objects.pools[id] = obj;

	bool error = false;
	auto argCount = scriptUtil::getArgumentIntValue(command->count, p_d, error);
	
	obj->argCount = argCount;
	

	auto code = putMemoryCell(dst, obj, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}
}

void ScriptSystem::p_processAddToPool(AddToPoolScript * command)
{
	auto dst = command->dst;

	BaseObject * objDst = NULL;

	auto code = getMemoryCell(dst, &objDst, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (objDst->objectType != objectType::pool)
	{
		// failed
		return;
	}

	PoolObject * obj = static_cast<PoolObject*>(objDst);
	PoolDataCell * p = new PoolDataCell();
	p->a = new BaseObject*[obj->argCount];
	bool error = false;

	int weight = scriptUtil::getArgumentIntValue(command->weight, p_d, error);
	
	if (command->args.size() != obj->argCount)
	{
		// failed
		return;
	}

	for (int i(0); i < command->args.size(); i++)
	{
		//p->a command->args[i];
		auto s = command->args[i];
		BaseObject * q = NULL;
		bool error = false;
		q = scriptUtil::replicateStandart(s, p_d, error);
		if (error)
		{
			// failed
			return;
		}
		p->a[i] = q;

	}

	obj->AddObject(p, weight);

}

void ScriptSystem::p_processGetFromPool(GetFromPoolScript * command)
{

	auto src = command->src;

	BaseObject * objSrc = NULL;

	auto code = getMemoryCell(src, &objSrc, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (objSrc->objectType != objectType::pool)
	{
		// failed
		return;
	}

	PoolObject * obj = static_cast<PoolObject*>(objSrc);

	bool error = false;

	int key = scriptUtil::getArgumentIntValue(command->key, p_d, error);

	if (command->args.size() != obj->argCount)
	{
		// failed
		return;
	}

	auto q = obj->GetRandomObject(key);

	for (int i(0); i < command->args.size(); i++)
	{
		//p->a command->args[i];
		auto s = command->args[i];
		BaseObject * w = q->a[i];

		if (w->objectType == objectType::integer)
		{
			IntObject * p = new IntObject(static_cast<IntObject*>(w)->value);
			if (w->singleUse())
				delete(w);
			code = putMemoryCell(s, p, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
			continue;
		}

		if (w->objectType == objectType::real)
		{
			FloatObject * p = new FloatObject(static_cast<FloatObject*>(w)->value);
			if (w->singleUse())
				delete(w);
			code = putMemoryCell(s, p, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
			continue;
		}
	
		if (w->objectType == objectType::string)
		{
			StringObject * p = new StringObject(static_cast<StringObject*>(w)->value);
			if (w->singleUse())
				delete(w);
			code = putMemoryCell(s, p, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
			continue;
		}

		code = putMemoryCell(s, w, &p_d->localMemory);
		if (code != memoryUtil::ok)
		{
			// failed
			return;
		}

	}


}

void ScriptSystem::p_processStringConcat(StringConcatScript * command)
{

	RETURN_CODE code;
	bool error = false;

	std::wstring srcA = scriptUtil::getArgumentStringValue(command->a, p_d, error);
	std::wstring srcB = scriptUtil::getArgumentStringValue(command->b, p_d, error);

	if (error)
	{
		// failed
		return;
	}

	StringObject * res = new StringObject(srcA + srcB);
	res->memoryControl = memoryControl::singleUse;

	code = putMemoryCell(command->dest, res, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}


}

void ScriptSystem::p_processCreateExternalTable(CreateExternalTableScript * command)
{

	auto p = createExternalTable();

	StringObject * res = new StringObject(p);
	res->memoryControl = memoryControl::singleUse;
	
	auto code = putMemoryCell(command->dest, res, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

}

void ScriptSystem::p_processPutToExternalTable(PutToExternalTableScript * command)
{
	
	bool error = false;
	auto t = scriptUtil::getArgumentStringValue(command->table, p_d, error);
	if (error)
	{
		// failed
		return;
	}

	std::wstring dst = command->dst;

	dst = L"$EXT:" + t + L":" + dst;

	std::wstring src = command->src;

	BaseObject * obj = NULL;

	// check if src is const
	if (src.size() >= 1)
	{
		if (src[0] != '$')
		{
			// value is const
			auto code = convertConstToObject(src, &obj);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
		else
		{
			// get src object if not a const
			auto code = getMemoryCell(src, &obj, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
	}
	else
	{
		// failed
		// no source provided
		return;
	}

	auto code = putMemoryCell(dst, obj, &p_d->localMemory);

	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

}

void ScriptSystem::p_processPutFromExternalTable(PutFromExternalTableScript * command)
{

	bool error = false;
	auto t = scriptUtil::getArgumentStringValue(command->table, p_d, error);
	if (error)
	{
		// failed
		return;
	}

	std::wstring src = command->src;

	src = L"$EXT:" + t + L":" + src;

	std::wstring dst = command->dst;

	BaseObject * obj = NULL;

	// check if src is const
	if (src.size() >= 1)
	{
		if (src[0] != '$')
		{
			// value is const
			auto code = convertConstToObject(src, &obj);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
		else
		{
			// get src object if not a const
			auto code = getMemoryCell(src, &obj, &p_d->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}
	}
	else
	{
		// failed
		// no source provided
		return;
	}

	auto code = putMemoryCell(dst, obj, &p_d->localMemory);

	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

}

void ScriptSystem::p_processCreateMarker(CreateMarkerScript * command)
{

	MapMarker * obj = new MapMarker();

	auto dst = command->dst;

	auto code = putMemoryCell(dst, obj, &p_d->localMemory);

	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

}

void ScriptSystem::p_processAddMarkerToSector(AddMarkerToSectorScript * command)
{

	RETURN_CODE code;

	auto objSrc = scriptUtil::getArgumentObject(command->src, p_d, code);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	auto objDest = scriptUtil::getArgumentObject(command->dst, p_d, code);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (objSrc->objectType != objectType::mapMarker || objDest->objectType != objectType::mapSector)
	{
		// failed
		return;
	}

	MapSector * p = static_cast<MapSector*>(objDest);
	MapMarker * m = static_cast<MapMarker*>(objSrc);

	p->markers.push_back(m);

}

void ScriptSystem::p_processEditMarkerProperties(EditMarkerPropertiesScript * command)
{

	RETURN_CODE code;

	auto obj = scriptUtil::getArgumentObject(command->src, p_d, code);

	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (obj->objectType != objectType::mapMarker)
	{
		// failed
		return;
	}

	MapMarker * p = static_cast<MapMarker*>(obj);

//	p->danger = command->danger;
//	p->level = command->level;
//	p->name = command->label;
//	p->description = command->desc;
//	p->pos.x = command->posX;
//	p->pos.y = command->posY;

	bool error = false;

	int danger = scriptUtil::getArgumentIntValue(command->danger, p_d, error);
	int level = scriptUtil::getArgumentIntValue(command->level, p_d, error);
	float posX = scriptUtil::getArgumentFloatValue(command->posX, p_d, error);
	float posY = scriptUtil::getArgumentFloatValue(command->posY, p_d, error);
	
	std::wstring label = scriptUtil::getArgumentStringValue(command->label, p_d, error);
	std::wstring desc = scriptUtil::getArgumentStringValue(command->desc, p_d, error);

	// error check
	//if ()

	p->danger = danger;
	p->level = level;
	p->pos.x = posX;
	p->pos.y = posY;
	p->name = label;
	p->description = desc;

}

void ScriptSystem::p_processCallCustom(CallCustomScript * command)
{

	if (command->categoryId == L"SectorTemplate")
	{
		// compiling and calling script

		ScriptCompiler * c;
		ScriptDescriptor * q;
		std::string filename;

		filename = gEnv->game.workDir;

		for (int i(0); i<command->scriptId.size(); i++)
		filename += command->scriptId[i];
		c = new ScriptCompiler();

		// I cannod define family id for sector template
		// We probably need to sync groups somewhere esle

		q = c->compileFile(filename, L"Undefined");
		delete(c);

		if (q == NULL)
		{
			// failed
			return;
		}

		// Call code (Copied from Call)

		BaseObject * destObject = q;

		auto tp = destObject->objectType;

		if (tp != objectType::scriptDescriptor)
		{
			if (debugMode)
			{
				wprintf(L"Error! Failed to call [%s] function. Invalid descriptor or adress not correct\n", command->scriptId.c_str());
			}
			// failed
			return;
		}

		ScriptDescriptor * target = static_cast<ScriptDescriptor*>(destObject);
		StackElement * t = new StackElement();
		t->localMemory.clear();
		RetContext * retContext = new RetContext();
		auto extTable = createExternalTable();
		//t->rContext = retContext;

		retContext->linkTable = extTable;

		for (int i(0); i < command->arg.size(); i++)
		{

			std::wstring eDest = L"$EXT:" + extTable + L":" + std::to_wstring(i);

			if (command->arg[i].size() > 0)
			{
				if (command->arg[i][0] == '$')
				{
					retContext->srcVarLink.push_back(command->arg[i]);
					BaseObject * qsrc = NULL;
					auto code = getMemoryCell(command->arg[i], &qsrc, &p_d->localMemory);
					if (code != memoryUtil::ok)
					{
						// Operation can be failed because we want to share a pointer to memory
						// but not actual object. Thats mean that we cannot use actual object here

						// So there shouldn't be return function

						// failed
						return;
					}
					code = putMemoryCell(eDest, qsrc, &p_d->localMemory);
					if (code != memoryUtil::ok)
					{
						// failed
						return;
					}

				}
				else
					retContext->srcVarLink.push_back(L"");
			}
			else
				retContext->srcVarLink.push_back(L"");

			StringObject * obj = new StringObject();
			obj->memoryControl = memoryControl::free;
			if (command->arg[i].size() > 0)
			{
				if (command->arg[i][0] == '$')
				{
					obj->value = eDest;
				}
				else
					obj->value = command->arg[i];
			}
			else
				obj->value = command->arg[i];
			std::wstring ndst = L"$_arg" + std::to_wstring(i);
			auto code = putMemoryCell(ndst, obj, &t->localMemory);
			if (code != memoryUtil::ok)
			{
				// failed
				return;
			}
		}

		//target->localMemory;

		if (debugMode)
		{
			wprintf(L"Calling a function [%s].\n", command->scriptId.c_str());
		}

		t->scriptId = target;

		_CallFunction(t, target->entryPoint, retContext);

	}

}

void ScriptSystem::p_processLinkScriptToMarker(LinkScriptToMarkerScript * command)
{

	BaseObject * src = NULL;
	BaseObject * dst = NULL;

	RETURN_CODE code;

	src = scriptUtil::getArgumentObject(command->script, p_d, code);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}
	dst = scriptUtil::getArgumentObject(command->marker, p_d, code);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (src->objectType != objectType::scriptDescriptor)
	{
		// failed
		return;
	}

	if (dst->objectType != objectType::mapMarker)
	{
		// failed
		return;
	}

	ScriptDescriptor * sd = static_cast<ScriptDescriptor *>(src);
	MapMarker * mm = static_cast<MapMarker * >(dst);

	mm->sd = sd;

}

void ScriptSystem::p_processSetMarkerPosition(SetMarkerPositionScript * command)
{

	RETURN_CODE code;

	auto obj = scriptUtil::getArgumentObject(command->src, p_d, code);

	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (obj->objectType != objectType::mapMarker)
	{
		// failed
		return;
	}

	MapMarker * p = static_cast<MapMarker*>(obj);

	bool error = false;


	float posX = scriptUtil::getArgumentFloatValue(command->x, p_d, error);
	float posY = scriptUtil::getArgumentFloatValue(command->y, p_d, error);


	// error check
	//if ()


	p->pos.x = posX;
	p->pos.y = posY;


}

void ScriptSystem::p_processCreateDecoration(CreateDecorationScript * command)
{

	auto dst = command->dest;

	// create item
	// need to store in global item db

	int id = gEnv->objects.nextDecor;
	MapDecoration * obj = new MapDecoration;
	gEnv->objects.decor[id] = obj;




	bool error = false;
	auto model = scriptUtil::getArgumentStringValue(command->model, p_d, error);
	float sx = scriptUtil::getArgumentFloatValue(command->scaleX, p_d, error);
	float sy = scriptUtil::getArgumentFloatValue(command->scaleY, p_d, error);
	float r = scriptUtil::getArgumentFloatValue(command->rotation, p_d, error);
	float x = scriptUtil::getArgumentFloatValue(command->posX, p_d, error);
	float y = scriptUtil::getArgumentFloatValue(command->posY, p_d, error);

	//std::wstring model;
	//std::wstring scaleX;
	//std::wstring scaleY;
	//std::wstring rotation;
	//std::wstring posX;
	//std::wstring posY;

	obj->model = model;
	obj->scale.x = sx;
	obj->scale.y = sy;
	obj->rotation = r;
	obj->pos.x = x;
	obj->pos.y = y;

	auto code = putMemoryCell(dst, obj, &p_d->localMemory);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}


}

void ScriptSystem::p_processAddDecorationToSector(AddDecorationToSectorScript * command)
{

	RETURN_CODE code;

	auto objSrc = scriptUtil::getArgumentObject(command->src, p_d, code);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	auto objDest = scriptUtil::getArgumentObject(command->dst, p_d, code);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (objSrc->objectType != objectType::mapDecoration || objDest->objectType != objectType::mapSector)
	{
		// failed
		return;
	}

	MapSector * p = static_cast<MapSector*>(objDest);
	MapDecoration * m = static_cast<MapDecoration*>(objSrc);

	p->objects.push_back(m);


}

void ScriptSystem::p_processAddBackgroundToSector(AddBackgroundToSectorScript * command)
{

	RETURN_CODE code;
	bool error = false;

	auto objSrc = scriptUtil::getArgumentStringValue(command->src, p_d, error);

	auto objDest = scriptUtil::getArgumentObject(command->dst, p_d, code);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	if (objDest->objectType != objectType::mapSector)
	{
		// failed
		return;
	}

	MapSector * p = static_cast<MapSector*>(objDest);

	p->backgroundImage = objSrc;

}

void ScriptSystem::p_processEquipModule(EquipModuleScript * command)
{

	RETURN_CODE code;

	auto objSrc = scriptUtil::getArgumentObject(command->src, p_d, code);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}

	auto objDest = scriptUtil::getArgumentObject(command->dst, p_d, code);
	if (code != memoryUtil::ok)
	{
		// failed
		return;
	}
	bool error = false;
	int slotId = scriptUtil::getArgumentIntValue(command->slotId, p_d, error);
	if (error)
	{
		// failed
		return;
	}

	if (objSrc->objectType != objectType::item || objDest->objectType != objectType::ship)
	{
		// failed
		return;
	}

	Item * objSrcItem = static_cast<Item*> (objSrc);

	if (objSrcItem->itemType != itemType::module)
	{
		// failed
		return;
	}


	Module * objSrcModule = static_cast<Module*> (objSrc);

	Ship * s = static_cast<Ship*> (objDest);

	if (slotId >= s->modules.size())
	{
		// failed
		return;
	}
	
	s->modules[slotId] = objSrcModule;

	updateShipSchemeUI();

}

extern ScriptSystem * scriptSystem = NULL;