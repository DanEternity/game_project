#include "gameOverGamemode.h"

void updateGameOverGamemode(double deltiTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		gEnv->game.endGameFlag = true;
	}
}

void drawGameOverGamemode(double deltaTime)
{
	if (gEnv->game.adventureData.sysImage == NULL)
	{
		gEnv->game.adventureData.sysImage = new sf::Sprite(gEnv->modelDB[L"systemGameOverTest"]->tex);

		gEnv->game.adventureData.sysImage->setOrigin(400, 300);

	}

	gEnv->game.adventureData.sysImage->setPosition(gEnv->graphics.windowSizeX / 2, gEnv->graphics.windowSizeY / 2);

	gEnv->globalWindow.draw(*gEnv->game.adventureData.sysImage);

}
