#include "scriptSystem.h"

#include "enviroment.h"
#include "envUtils.h"
#include "scriptMemoryUtils.h"

void ScriptSystem::updateScriptEngine()
{

	if (gEnv->game.scriptSystemRequiresUpdate)
	{
		if (gEnv->scripts.task == "notInitialized")
		{

			// init

			gEnv->scripts.task = "ready";

		}

		if (gEnv->scripts.task == "ready")
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

		break;
	default:
		printf("Debug: Error! Script commands has unknown type -> %i", sType);
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
}

std::string ScriptSystem::p_convertText(std::string src)
{

	std::string res = "";

	for (int i(0); i < src.size(); i++)
	{

		if (src[i] != '$')
		{
			res += src[i];
			continue;
		}

		// looking for first space

		int right = src.find_first_of(" ", i);
		if (right <= 0)
			right = src.size();

		std::string fragment = p_convertValueToString(src.substr(i, right - i));

		i = right;

		res += fragment;

	}

	p_s = p_sysStatus::scriptWaitForReaction;

	return res;
}

std::string ScriptSystem::p_convertValueToString(std::string src)
{

	// $value

	std::string result = "";

	if (src.size() <= 1) // nothing to convert
		return "";

	// start from digit or _ means local memory
	if ((src[2] >= '0' && src[2] <= '9') || src[2] == '_')
	{

		// attempting to extract memory data

		BaseObject * target;
		auto code = getMemoryCellFromLocalMemory(&p_d->localMemory, src.substr(2, src.size() - 2), &target);
		
		if (code != memoryUtil::ok)
			return "NULL";

		code = convertToString(target, result);

		if (code != memoryUtil::ok)
			return "NULL";

		return result;

	}

	if (src.find("$EXT:") != std::string::npos)
	{

		// external table

		BaseObject * target;
		auto code = getMemoryCellFromExternalTable(src.substr(5, 4), src.substr(10, src.size() - 11), &target);

		if (code != memoryUtil::ok)
			return "NULL";

		code = convertToString(target, result);

		if (code != memoryUtil::ok)
			return "NULL";

		return result;


	}

	// Game value or incorrect query

	BaseObject * target;
	auto code = getMemoryCellFromGameEnviroment(src.substr(1, src.size() - 2), &target);

	if (code != memoryUtil::ok)
		return "NULL";

	code = convertToString(target, result);

	if (code != memoryUtil::ok)
		return "NULL";

	return result;
}

std::string ScriptSystem::p_getLocalMemoryCellAsString(std::string idx)
{

	if (p_d->localMemory.find(idx) == p_d->localMemory.end())
		return "NULL";

	auto obj = p_d->localMemory[idx];

	std::string res = "";

	switch (obj->objectType)
	{
	case objectType::integer:
		res = std::to_string(static_cast<IntObject*>(obj)->value);
		break;
	case objectType::real:
		res = std::to_string(static_cast<FloatObject*>(obj)->value);
		break;
	case objectType::string:
		res = static_cast<StringObject*>(obj)->value;
		break;
	default:
		break;
	}

	return res;
}

std::string ScriptSystem::p_getExternalTableValueAsString(std::string tableId, std::string idx)
{
	return std::string();
}

std::string ScriptSystem::p_getGlobalValueAsString(std::string ValueName)
{
	return std::string();
}

void ScriptSystem::p_processText(TextScript * command)
{

	// Need to block/pause game

	p_blockGame_WaitForReaction();

	// Draw text OwO
	
	//gEnv->scripts.huieviiButton.setText(p_convertText(command->text));
	std::string text = p_convertText(command->text);
	gEnv->scripts.scriptGui.get<tgui::TextBox>("scriptTextMessage")->setText(text);

	if (true)
		printf("TEST: %s\n", text.c_str());

	// Check buttons

	if (gEnv->scripts.buttonPressed)
	{

		p_blockGame_WaitForReaction(false);

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

extern ScriptSystem * scriptSystem = NULL;