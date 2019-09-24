#include "game.h"
#include "enviroment.h"
#include "scriptSystem.h"
#include "menuOverlay.h"
#include "loader.h"

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
		default:
			// invalid game mode
			// Probably critical error
			break;
		}
	}

	/* Calling script system */

	if (gEnv->game.scriptSystemRequiresUpdate)
	{

	}

	/* Calling menu overlay */

	if (gEnv->game.menuOverlayRequiresUpdate)
	{
		updateMenuOverlay(deltaTime);
	}

	/* World generator utility goes here */

	if (gEnv->game.worldGeneratorRequiresUpdate)
	{

	}

	/* End of cycle update */
}
