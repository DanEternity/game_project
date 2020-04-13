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

		//	gEnv->game.loader.task = "loadingCompleted";
			gEnv->game.loader.task = "loadingScripts";
			gEnv->game.loader.scriptFilenameId = 0;
			return;
		}

		// Load current texture

		loadTextureToModelDescriptor(gEnv->game.loader.pointer->second->name);

		// Move to next

		gEnv->game.loader.pointer++;

	}

	if (gEnv->game.loader.task == "loadingScripts")
	{
		std::string filename;
		ScriptCompiler * c;
		ScriptDescriptor * q;

		filename = gEnv->game.workDir;
		filename += gEnv->game.loader.scriptFilenames[gEnv->game.loader.scriptFilenameId].filename;

		if (debugMode)
			printf("Loading script: %s \n", filename.c_str());

		c = new ScriptCompiler();
		q = c->compileFile(filename, gEnv->game.loader.scriptFilenames[gEnv->game.loader.scriptFilenameId].familyId);
		delete(c);

		gEnv->game.loader.scriptFilenameId++;

		if (gEnv->game.loader.scriptFilenameId >= gEnv->game.loader.scriptFilenames.size())
		{
			gEnv->game.loader.task = "loadingCompleted";
			return;
		}
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
