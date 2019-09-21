#include "game.h"
#include "enviroment.h"
#include "scriptSystem.h"

void updateGameCycle(double deltaTime)
{

	/* Initiating cycle update */

	/* Calling gamemodes for draw */
	
	if (gEnv->gameModesRequiredDraw)
	{

	}

	/* Calling gamemodes for update */
	
	if (gEnv->gameModesRequiredUpdate)
	{

	}

	/* Calling script system */

	if (gEnv->scriptSystemRequiresUpdate)
	{

	}

	/* Calling menu overlay */

	if (gEnv->menuOverlayRequiresUpdate)
	{

	}

	/* World generator utility goes here */

	if (gEnv->worldGeneratorRequiresUpdate)
	{

	}

	/* End of cycle update */
}
