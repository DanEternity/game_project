#include "menuOverlay.h"
#include "enviroment.h"

void updateMenuOverlay(double deltaTime)
{

	if (gEnv->menuData.drawRequired)
	{

		// draw menu based on gamemode active

	}

	if (gEnv->menuData.updateRequired)
	{

		// update menu based on current state

	}

	if (gEnv->game.debug)
	{

		sf::CircleShape f(120.f);
		gEnv->globalWindow.draw(f);

	}

}
