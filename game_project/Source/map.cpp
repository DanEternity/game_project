#include "map.h"


void BuildMapUI()
{
	gEnv->game.adventureGUI.add(createWidget(WidgetType::Panel, "Panel", "90%", "90%", "(&.width - width) / 2", "(&.height - height) / 2", false), "globalMapPanel");
	
	int i = 0;
	for (auto sector : gEnv->game.adventureData.sectors)
	{
		const int id = i;
		tgui::Panel::Ptr pan = gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->cast<tgui::Panel>();

		pan->add(createWidget(WidgetType::Button, "Button", "20", "20",
			std::to_string(sector.second->x / 8 + (pan->getSize().x / 2)), std::to_string(sector.second->y / 8 + (pan->getSize().y / 2))), "globalMapSectorButton" + std::to_string(i));

		gEnv->game.adventureGUI.get<tgui::Button>("globalMapSectorButton" + std::to_string(i))->connect("MouseReleased", clickSector, sector.first, id);
		i++;
	}
}

void clickSector(const std::string str, const int id, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (!gEnv->game.ui.rmWasClicked)
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->add(createWidget(WidgetType::Panel, "Panel", "120", "30", std::to_string(widget->getPosition().x + 20), std::to_string(widget->getPosition().y + 20)), "tempRightPanel");


		tgui::Button::Ptr but = createWidget(WidgetType::Button, "Button", "120", "30", "0", "0")->cast<tgui::Button>();
		gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->add(but);
		but->setText("Jump");
		but->connect("MouseReleased", jumpSector, str);
		gEnv->game.ui.rmWasClicked = true;
	}
	else
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));

		gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->add(createWidget(WidgetType::Panel, "Panel", "120", "30", std::to_string(widget->getPosition().x + 20), std::to_string(widget->getPosition().y + 20)), "tempRightPanel");

		tgui::Button::Ptr but = createWidget(WidgetType::Button, "Button", "120", "30", "0", "0")->cast<tgui::Button>();
		gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->add(but);
		but->setText("Jump");
		but->connect("MouseReleased", jumpSector, str);
	}
	gEnv->game.ui.sectorNumberRightPanel = id;
}

void jumpSector(const std::string str, tgui::Widget::Ptr widget, const std::string& signalName)
{
	
	gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
	gEnv->game.ui.rmWasClicked = false;

	// Jump to sector
	gEnv->game.adventureData.currentSectorId = str;
	gEnv->game.adventureData.isSectorLoaded = false;
	gEnv->game.player.cameraPosition.x = 0;
	gEnv->game.player.cameraPosition.y = 0;
	printf("info: Jumping to sector %s\n", str.c_str());

	openMap();
}

void UpdateMapUI()
{
	if (gEnv->game.ui.mapUpdateRequired)
	{
		int i = 0;
		for (auto sector : gEnv->game.adventureData.sectors)
		{
			tgui::Button::Ptr but = gEnv->game.adventureGUI.get<tgui::Button>("globalMapSectorButton" + std::to_string(i));
			int x = sector.second->x / gEnv->game.ui.mapScale + (but->getParent()->getSize().x / 2) + gEnv->game.ui.mapBiasX;
			int y = sector.second->y / gEnv->game.ui.mapScale + (but->getParent()->getSize().y / 2) + gEnv->game.ui.mapBiasY;
			but->setPosition(x, y);
			if (i == gEnv->game.ui.sectorNumberRightPanel && gEnv->game.ui.rmWasClicked)
			{
				tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel");
				panel->setPosition(x+20,y+20);
			}
			i++;
		}
		gEnv->game.ui.mapUpdateRequired = false;
	}
}

void openMap()
{
	disableAllAdventureUI();
	gEnv->game.adventureUI.isInventoryOpen = false;
	gEnv->game.adventureUI.isMapOpen = !gEnv->game.adventureUI.isMapOpen;
	if (gEnv->game.adventureUI.isMapOpen)
	{
		gEnv->game.player.shipMenu = shipMenu::map;
		gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->setVisible(true);
	}
	else gEnv->game.player.shipMenu = shipMenu::null;

}
