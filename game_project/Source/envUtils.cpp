#include "envUtils.h"

bool createModelDescriptor(std::wstring name)
{
	// cant create models with same names
	if (gEnv->modelDB.find(name) != gEnv->modelDB.end())
		return false;

	ModelDescriptor * p = new ModelDescriptor();

	p->name = name;
	p->status = modelStatus::notAssigned;
	p->objectType = objectType::modelDescriptor;
	p->tableId = 0;

	gEnv->modelDB[name] = p;

	return true;
}

bool createModelDescriptor(std::wstring name, std::string pathToFile, bool highPriority)
{

	if (!createModelDescriptor(name))
		return false;

	gEnv->modelDB[name]->pathToFile = gEnv->game.workDir + pathToFile;
	gEnv->modelDB[name]->priorityLoad = highPriority;
	gEnv->modelDB[name]->status = modelStatus::notLoaded;

	return true;
}

ModelDescriptor * getModelDescriptor(std::wstring name)
{

	if (gEnv->modelDB.find(name) == gEnv->modelDB.end())
		return nullptr;

	return gEnv->modelDB[name];

}

bool deleteModelDescriptor(std::wstring name)
{

	if (gEnv->modelDB.find(name) != gEnv->modelDB.end())
		return false;

	//gEnv->modelDB[name]->tex.~Texture();

	delete gEnv->modelDB[name];

	return true;
}

bool loadTextureToModelDescriptor(std::wstring name)
{
	auto p = gEnv->modelDB[name];
	if (p->status == modelStatus::notLoaded)
	{
		try
		{
			p->tex.loadFromFile(p->pathToFile);
			if (p->tex.getNativeHandle() == 0)
			{
				// Loading failed
				p->status = modelStatus::error;
				if (debugMode)
					printf("Debug: Error! Failed to load texture -> %s \n", p->pathToFile.c_str());
				return false;
			}
			else
			{
				// Loading successfull
				p->status = modelStatus::loaded;
				if (debugMode)
					printf("Debug: Loaded texture -> %ws \n", p->name.c_str());
				return true;
			}
		}
		catch (const std::exception&)
		{
			// Loading failed
			p->status = modelStatus::error;
			if (debugMode)
				printf("Debug: Error! Failed to load texture -> %s \n", p->pathToFile.c_str());
			return false;
		}

	}

	return false;

}

ScriptDescriptor * createScriptDescriptor()
{

	ScriptDescriptor * ptr;

	try
	{
		ptr = new ScriptDescriptor();
		ptr->tableId = gEnv->scripts.nextScriptID;
		gEnv->scripts.scriptDB[gEnv->scripts.nextScriptID++] = ptr;
	}
	catch (const std::exception&)
	{
		return NULL;
	}

	return ptr;
}

ScriptDescriptor * getScriptDescriptor(int id)
{

	if (gEnv->scripts.scriptDB.find(id) == gEnv->scripts.scriptDB.end())
		return NULL;

	return gEnv->scripts.scriptDB[id];
}

BaseScript * createScriptCommand(scriptType::ScriptType type)
{

	switch (type)
	{
	case scriptType::null:
		return nullptr;
		break;
	case scriptType::text:
		return new TextScript();
		break;
	case scriptType::put:
		return new PutScript();
		break;
	case scriptType::choose:
		return new ChooseScript();
		break;
	case scriptType::terminate:
		return new TerminateScript();
		break;
	case scriptType::ariphmetic:
		return new AriphmeticScript();
		break;
	case scriptType::jump:
		return new JumpScript();
		break;
	case scriptType::ifDoJump:
		return new IfDoJumpScript();
		break;
	case scriptType::changeScriptEntryPoint:
		return new ChangeScriptEntryPointScript();
		break;
	case scriptType::spendTime:
		return new SpendTimeScript();
		break;
	case scriptType::initRewardBuffer:
		return new InitRewardBufferScript();
		break;
	default:
		printf("Error! Script command creation failed. Invalid type\n");
		break;
	}

	return nullptr;
}

bool addScriptToQueue(ScriptDescriptor * sd)
{
	auto * p = new StackElement();
	p->scriptId = sd;
	p->returnPoint = sd->entryPoint;
	// new memory
	p->localMemory.clear();
	gEnv->scripts.queue.push_back(p);
	return true;
}

std::wstring createExternalTable()
{

	std::wstring internalId = std::to_wstring(gEnv->game.nextExternalTableId);

	gEnv->game.nextExternalTableId++;

	gEnv->extTables[internalId] = new ExternalTable();

	return internalId;
}

void deleteExternalTable(std::wstring id)
{
	auto t = gEnv->extTables[id];

	for (auto q = t->p_memory.begin(); q != t->p_memory.end(); q++)
	{
		auto mt = q->second->memoryControl;
		if (mt == memoryControl::free)
		{
			auto obj = q->second;
			delete obj;
		}
	}

	delete (t);

	gEnv->extTables.erase(id);
}
