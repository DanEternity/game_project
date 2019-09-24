#include "mainMenu.h"
#include "enviroment.h"

void updateMainMenu()
{
	if (gEnv->game.mainMenu.menuDrawRequired)
	{
		gEnv->globalGui.draw();
	}

	if (gEnv->game.mainMenu.widgetDisable)
	{
		for (const auto& widget : gEnv->game.mainMenu.mainMenuWidgets)
		{
			widget->setVisible(false);
			widget->setEnabled(false);
		}
		gEnv->game.mainMenu.widgetDisable = false;
	}
}
