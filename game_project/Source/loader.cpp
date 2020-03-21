#include "loader.h"
#include "enviroment.h"
#include "mainMenu.h"
#include "adventureUI.h"

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
		//dfgdfgdfg
		// Texture binding goes here

		// Change active gamemode and variables

		createMenuButtons();
		createAdventureUIButtons();

		InitGameLogic();

		LoadEnglishLocale();
		LoadRussianLocale(); // only for testing

		gEnv->game.activeGameMode = gameMode::mainMenuMode;
		gEnv->game.mainMenu.menuDrawRequired = true;
		gEnv->game.mainMenu.menuUpdateRequired = true;
		gEnv->game.gameModesRequiredDraw = true;
		gEnv->game.gameModesRequiredUpdate = true;
		//gEnv->game.mainMenu.widgetDisable = true;

		//gEnv->game.activeGameMode = gameMode::adventureMode;

	}
}
