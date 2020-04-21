#include "map.h"


void BuildMapUI()
{
	tgui::Panel::Ptr panel = tgui::Panel::create();
	panel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
	panel->setPosition("(&.width - width) / 2", "(&.height - height) / 2");
	panel->setSize("90%", "90%");
	gEnv->game.adventureGUI.add(panel);
	
	for (auto sector : gEnv->game.adventureData.sectors)
	{
		tgui::Button::Ptr but = tgui::Button::create();
		but->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		but->setSize(20, 20);
		panel->add(but);
		but->setPosition(sector.second->x / 10 + (but->getParent()->getSize().x / 2), sector.second->y / 15 + (but->getParent()->getSize().y / 2));
	}
}
