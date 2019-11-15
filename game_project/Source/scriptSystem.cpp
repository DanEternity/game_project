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
			ScriptDescriptor * sd = gEnv->scripts.queue.front();
			this->p_l = sd->entryPoint;
			this->p_nl = sd->entryPoint;
			this->p_d = sd;
			gEnv->scripts.queue.pop_front();

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
		auto code = getMemoryCellFromExternalTable(src.substr(5, 4), src.substr(10, src.size() - 11), &target);

		if (code != memoryUtil::ok)
			return L"NULL";

		code = convertToString(target, result);

		if (code != memoryUtil::ok)
			return L"NULL";

		return result;


	}

	// Game value or incorrect query

	BaseObject * target;
	auto code = getMemoryCellFromGameEnviroment(src.substr(1, src.size() - 2), &target);

	if (code != memoryUtil::ok)
		return L"NULL";

	code = convertToString(target, result);

	if (code != memoryUtil::ok)
		return L"NULL";

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
		gEnv->scripts.scriptGui.get<tgui::TextBox>(L"scriptTextMessage")->setVisible(true);
		gEnv->scripts.scriptGui.get<tgui::TextBox>(L"scriptTextMessage")->setText(text);
		gEnv->scripts.scriptGui.get<tgui::Button>(L"ScriptButtonNext")->setVisible(true);
		gEnv->scripts.scriptGui.get<tgui::Button>(L"ScriptButtonNext")->setEnabled(true);
		//gEnv->scripts.scriptGui.get<tgui::Button>(L"ScriptButtonNext")->setText(text);
		if (true)
			printf("TEST: %s\n", text.c_str());
	}
	else
		text = p_textChache;

	



	// Check buttons

	if (gEnv->scripts.buttonPressed)
	{

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
	if (command->scriptId == L"" || command->scriptId == L"$self")
	{
		p_d->entryPoint = command->lineId;
	}
	else
	{
		// doesnt work xd
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

extern ScriptSystem * scriptSystem = NULL;