#include "loader.h"
#include "enviroment.h"

void updateLoadingMode()
{

	//
	// Performs resource loading
	//

	if (gEnv->game.loader.task == "null")
	{

		// Setup variables

		gEnv->game.loader.pointer = gEnv->modelDB.begin();

		// Start loading

		gEnv->game.loader.task = "loadingModels";

	}

	if (gEnv->game.loader.task == "loadingModels")
	{

		if (gEnv->game.loader.pointer == gEnv->modelDB.end())
		{

			// Loading completed

			gEnv->game.loader.task = "loadingCompleted";

			return;
		}

		// Load current texture

		if (gEnv->game.loader.pointer->second->status == modelStatus::notLoaded)
		{
			try
			{
				gEnv->game.loader.pointer->second->tex.loadFromFile(gEnv->game.loader.pointer->second->pathToFile);
				if (gEnv->game.loader.pointer->second->tex.getNativeHandle() == 0)
				{
					// Loading failed
					gEnv->game.loader.pointer->second->status = modelStatus::error;
					if (debugMode)
						printf("Debug: Error! Failed to load texture -> %s \n", gEnv->game.loader.pointer->second->pathToFile.c_str());
				}
				else
				{
					// Loading successfull
					gEnv->game.loader.pointer->second->status = modelStatus::loaded;
					if (debugMode)
						printf("Debug: Loaded texture -> %s \n", gEnv->game.loader.pointer->second->name.c_str());
				}
			}
			catch (const std::exception&)
			{
				// Loading failed
				gEnv->game.loader.pointer->second->status = modelStatus::error;
				if (debugMode)
					printf("Debug: Error! Failed to load texture -> %s \n", gEnv->game.loader.pointer->second->pathToFile.c_str());
			}

		}

		// Move to next

		gEnv->game.loader.pointer++;

	}

	if (gEnv->game.loader.task == "loadingCompleted")
	{

		// Change active gamemode and variables

		gEnv->game.activeGameMode = gameMode::mainMenuMode;

	}
}
