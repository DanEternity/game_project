#include "map.h"


void BuildMapUI()
{
	tgui::Panel::Ptr panel = tgui::Panel::create();
	panel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
	panel->setPosition("(&.width - width) / 2", "(&.height - height) / 2");
	panel->setSize("90%", "90%");
	gEnv->game.adventureGUI.add(panel, "globalMapPanel");
	panel->setVisible(false);
	panel->setEnabled(false);
	
	int i = 0;
	for (auto sector : gEnv->game.adventureData.sectors)
	{
		tgui::Button::Ptr but = tgui::Button::create();
		but->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		but->setSize(20, 20);
		panel->add(but, "globalMapSectorButton" + std::to_string(i));
		but->setPosition(sector.second->x / 8 + (but->getParent()->getSize().x / 2), sector.second->y / 8 + (but->getParent()->getSize().y / 2));
		but->connect("MouseReleased", clickSector, sector.first);
		i++;
	}
}

void clickSector(const std::string str, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (!gEnv->game.ui.rmWasClicked)
	{
		tgui::Panel::Ptr panel = tgui::Panel::create();
		panel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
		gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->add(panel, "tempRightPanel");
		panel->setPosition(widget->getPosition().x + 20, widget->getPosition().y + 20);
		panel->setSize(120, 30);

		tgui::Button::Ptr but = tgui::Button::create();
		but->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		but->setSize(120, 30);
		panel->add(but);
		but->setPosition(0, 0);
		but->setText("Jump");
		but->connect("MouseReleased", jumpSector, str);
		gEnv->game.ui.rmWasClicked = true;
	}
	else
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));

		tgui::Panel::Ptr panel = tgui::Panel::create();
		panel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
		gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->add(panel, "tempRightPanel");
		panel->setPosition(widget->getPosition().x + 20, widget->getPosition().y + 20);
		panel->setSize(120, 30);

		tgui::Button::Ptr but = tgui::Button::create();
		but->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		but->setSize(120, 30);
		panel->add(but);
		but->setPosition(0, 0);
		but->setText("Jump");
		but->connect("MouseReleased", jumpSector, str);
	}
}

void jumpSector(const std::string str, tgui::Widget::Ptr widget, const std::string& signalName)
{
	
	gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
	gEnv->game.ui.rmWasClicked = false;

	//Dan write code here
	//
	//
}

void UpdateMapUI()
{
	if (gEnv->game.ui.mapUpdateRequired)
	{
		int i = 0;
		for (auto sector : gEnv->game.adventureData.sectors)
		{
			tgui::Button::Ptr but = gEnv->game.adventureGUI.get<tgui::Button>("globalMapSectorButton" + std::to_string(i));
			but->setPosition(sector.second->x / gEnv->game.ui.mapScale + (but->getParent()->getSize().x / 2) + gEnv->game.ui.mapBiasX, sector.second->y / gEnv->game.ui.mapScale + (but->getParent()->getSize().y / 2) + gEnv->game.ui.mapBiasY);
			i++;
		}
		if (gEnv->game.ui.rmWasClicked)
		{
			tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel");
			panel->setPosition(panel->getPosition().x + gEnv->game.ui.mapBiasX, panel->getPosition().y + gEnv->game.ui.mapBiasY);
		}
		gEnv->game.ui.mapUpdateRequired = false;
	}
}