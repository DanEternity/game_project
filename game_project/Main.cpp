//#include <SFML/Graphics.hpp>
//#include <TGUI/tGui.hpp>

#include "Source\enviroment.h"
#include "Source\game.h"
#include "Source\preload.h"
#include "Source\uiEventHandlers.h"
#include "Source\postUpdate.h"

int main()
{
	// Create game enviroment
	initEnviroment();

	// Preloading and constructing game resources
	preloadResources();

	// Create window to display game
	gEnv->globalWindow.create(
		sf::VideoMode(gEnv->graphics.windowSizeX, gEnv->graphics.windowSizeY), 
		"Eternity (development)", 
		gEnv->graphics.fullscreen ? sf::Style::Fullscreen : sf::Style::Default
	);

	// Bind gui descriptor to main window
	gEnv->globalGui.setTarget(gEnv->globalWindow);
	gEnv->scripts.scriptGui.setTarget(gEnv->globalWindow);
	gEnv->game.adventureGUI.setTarget(gEnv->globalWindow);
	gEnv->game.spaceBattle.GUI.setTarget(gEnv->globalWindow);
	tgui::Font fontArial(gEnv->game.workDir + "\\resources\\Fonts\\ARIALUNI.TTF");
	gEnv->globalGui.setFont(fontArial);
	gEnv->scripts.scriptGui.setFont(fontArial);
	gEnv->game.adventureGUI.setFont(fontArial);
	gEnv->game.spaceBattle.GUI.setFont(fontArial);

	// Clock to calculate time from previous frame
	sf::Clock deltaClock;

	gEnv->globalWindow.setFramerateLimit(120);

	while (gEnv->globalWindow.isOpen())
	{
		// Handle system events
		sf::Event event;
		while (gEnv->globalWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				gEnv->globalWindow.close();
			handleUIEvents(event);
		}

		gEnv->globalWindow.clear();

		// Delta time calculation
		sf::Time dt = deltaClock.restart();

		// Start game update
		updateGameCycle(dt.asSeconds());
		
		// DEBUG
		std::wstring debugTitle = L"Eternity(development); FPS: " + std::to_wstring(int(1.0 / dt.asSeconds())) + L"; Latency: " + std::to_wstring(dt.asMilliseconds()) + L" ms";
		gEnv->globalWindow.setTitle(debugTitle);
		// DEBUG END

		// Display frame
		gEnv->globalWindow.display();

		// Post update
		postUpdate();

		if (gEnv->game.endGameFlag)
			break;

	}

	return 0;
}