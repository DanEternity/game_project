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

			chooseUI = new ChooseUI(100, 300);
			chooseUI->setVisible(false);
			//gEnv->scripts.scriptGui.get<tgui::TextBox>(L"scriptTextMessage")->setVisible(false);

			gEnv->scripts.task = L"ready";

		}

		if (gEnv->scripts.task == L"ready")
		{

			p_processFrame();

		}

	}

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
	default:
		printf("Debug: Error! Script command has unknown type -> %i", sType);
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
		std::wstring l_arg = p_convertValueToString(comparator->left);
		std::wstring r_arg = p_convertValueToString(comparator->right);

		std::wstring op = comparator->operation;


		float l = _wtof(l_arg.c_str());
		float r = _wtof(r_arg.c_str());

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

extern ScriptSystem * scriptSystem = NULL;