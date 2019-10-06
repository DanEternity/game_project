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

}
