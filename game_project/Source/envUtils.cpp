#include "envUtils.h"

bool createModelDescriptor(std::string name)
{
	// cant create models with same names
	if (gEnv->modelDB.find(name) != gEnv->modelDB.end())
		return false;

	ModelDescriptor * p = new ModelDescriptor();

	p->name = name;
	p->status = modelStatus::notAssigned;
	p->objectType = objectType::modelDescriptor;
	p->tableId = 0;

	return true;
}

bool createModelDescriptor(std::string name, std::string pathToFile, bool highPriority)
{

	if (!createModelDescriptor(name))
		return false;

	gEnv->modelDB[name]->pathToFile = pathToFile;
	gEnv->modelDB[name]->priorityLoad = highPriority;
	gEnv->modelDB[name]->status = modelStatus::notLoaded;

	return true;
}

ModelDescriptor * getModelDescriptor(std::string name)
{

	if (gEnv->modelDB.find(name) == gEnv->modelDB.end())
		return nullptr;

	return gEnv->modelDB[name];

}

bool deleteModelDescriptor(std::string name)
{

	if (gEnv->modelDB.find(name) != gEnv->modelDB.end())
		return false;

	//gEnv->modelDB[name]->tex.~Texture();

	delete gEnv->modelDB[name];

	return true;
}
