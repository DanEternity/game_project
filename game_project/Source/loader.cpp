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

		loadTextureToModelDescriptor(gEnv->game.loader.pointer->second->name);

		// Move to next

		gEnv->game.loader.pointer++;

	}

	if (gEnv->game.loader.task == "loadingCompleted")
	{
		
		// Post load section

		// Texture binding goes here

		// Change active gamemode and variables

		gEnv->game.activeGameMode = gameMode::mainMenuMode;

	}
}
