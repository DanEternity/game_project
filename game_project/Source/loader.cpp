#include "loader.h"
#include "enviroment.h"


void signalHandler(tgui::Widget::Ptr widget, const std::string& signalName)
{

}

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

		tgui::Button::Ptr testButton = tgui::Button::create("testButton");
		tgui::Button::Ptr test2 = tgui::Button::create();
		gEnv->globalGui.add(testButton);
		gEnv->globalGui.add(test2);
		gEnv->game.mainMenu.mainMenuWidgets.push_back(testButton);
		gEnv->game.mainMenu.mainMenuWidgets.push_back(test2);
		int i = 0;
		for (const auto& widget : gEnv->game.mainMenu.mainMenuWidgets)
		{
			widget->setSize(200, 200);
			widget->setPosition(100*i + (i*200), 100);
			widget->setRenderer(gEnv->globalTheme.getRenderer("Button"));
			i++;
		}

		gEnv->game.mainMenu.mainMenuWidgets[0]->connect("MouseReleased", signalHandler);
		

		gEnv->game.activeGameMode = gameMode::mainMenuMode;
		gEnv->game.mainMenu.menuDrawRequired = true;
		gEnv->game.mainMenu.menuUpdateRequired = true;
		gEnv->game.gameModesRequiredDraw = true;
		gEnv->game.gameModesRequiredUpdate = true;
		//gEnv->game.mainMenu.widgetDisable = true;

	}
}
