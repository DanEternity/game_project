#include "game.h"
#include "enviroment.h"
#include "scriptSystem.h"
#include "menuOverlay.h"
#include "loader.h"
#include "mainMenu.h"
#include "adventureModeCore.h"
#include "adventureUI.h"
#include "worldGenerator.h"
#include "spaceBattleCore.h"
#include "gameOverGamemode.h"

void updateGameCycle(double deltaTime)
{

	/* Initiating cycle update */

	/* Calling gamemodes for draw */
	
	if (gEnv->game.gameModesRequiredDraw)
	{
		switch (gEnv->game.activeGameMode)
		{
		case gameMode::loadingMode:
			// drawLoadingMode();
			break;
		case gameMode::mainMenuMode:
			updateMainMenu();
			break;
		case gameMode::adventureMode:
			//updateAdventureGameMode(deltaTime);
			//updateAdventureUI();
			
			drawAdventureGameMode(deltaTime);
			DrawAdventureUI();
			break;
		case gameMode::spaceBattleMode:

			break;
		default:
			// invalid game mode
			// Probably critical error
			break;
		}
	}

	/* Calling gamemodes for update */
	
	if (gEnv->game.gameModesRequiredUpdate)
	{
		switch (gEnv->game.activeGameMode)
		{
		case gameMode::loadingMode:
			updateLoadingMode();
			break;
		case gameMode::adventureMode:
			updateAdventureGameMode(deltaTime);
			updateAdventureUI();
			break;
		case gameMode::spaceBattleMode:
			// Due to manual map segments calculation its not possible to draw it separately
			// But it's possible to disable controls and freeze animations
			updateSpaceBattle(deltaTime);
			break;
		case gameMode::gameover:
			updateGameOverGamemode(deltaTime);
			drawGameOverGamemode(deltaTime);
			break;
		default:
			// invalid game mode
			// Probably critical error
			break;
		}
	}

	/* Calling script system */

	if (gEnv->game.scriptSystemRequiresUpdate)
	{
		gEnv->scripts.scriptGui.draw();
		scriptSystem->updateScriptEngine();
	}

	/* Calling menu overlay */

	if (gEnv->game.menuOverlayRequiresUpdate)
	{
		updateMenuOverlay(deltaTime);
	}

	/* World generator utility goes here */

	if (gEnv->game.worldGeneratorRequiresUpdate)
	{
		worldGeneratorUpdate(deltaTime);
	}

	/* End of cycle update */
}
