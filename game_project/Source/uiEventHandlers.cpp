#include "uiEventHandlers.h"

void handleUIEvents(sf::Event & event)
{

	if (gEnv->game.globalGUIeventsRequiresUpdate)
	{
		gEnv->globalGui.handleEvent(event);
	}

	if (gEnv->scripts.scriptGuiEventsRequiresUpdate)
	{
		gEnv->scripts.scriptGui.handleEvent(event);
	}

	if (gEnv->game.gameAdventureGUIRequiresUpdate)
	{
		gEnv->game.adventureGUI.handleEvent(event);
	}

	if (event.type == sf::Event::MouseWheelMoved)
	{
		gEnv->game.player.mouseWheelDelta = event.mouseWheel.delta;
	}

}
