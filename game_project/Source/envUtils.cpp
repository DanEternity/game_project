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

	gEnv->modelDB[name] = p;

	return true;
}

bool createModelDescriptor(std::string name, std::string pathToFile, bool highPriority)
{

	if (!createModelDescriptor(name))
		return false;

	gEnv->modelDB[name]->pathToFile = gEnv->game.workDir + pathToFile;
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

bool loadTextureToModelDescriptor(std::string name)
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
					printf("Debug: Loaded texture -> %s \n", p->name.c_str());
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


}
