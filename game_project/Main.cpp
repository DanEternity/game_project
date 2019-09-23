//#include <SFML/Graphics.hpp>
//#include <TGUI/tGui.hpp>

#include "Source\enviroment.h"
#include "Source\game.h"
#include "Source\preload.h"

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

	// Clock to calculate time from previous frame
	sf::Clock deltaClock;

	while (gEnv->globalWindow.isOpen())
	{
		// Handle system events
		sf::Event event;
		while (gEnv->globalWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				gEnv->globalWindow.close();
			gEnv->globalGui.handleEvent(event);
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
	}

	return 0;
}