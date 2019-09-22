#include "game.h"
#include "enviroment.h"
#include "scriptSystem.h"
#include "menuOverlay.h"

void updateGameCycle(double deltaTime)
{

	/* Initiating cycle update */

	/* Calling gamemodes for draw */
	
	if (gEnv->game.gameModesRequiredDraw)
	{

	}

	/* Calling gamemodes for update */
	
	if (gEnv->game.gameModesRequiredUpdate)
	{

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
