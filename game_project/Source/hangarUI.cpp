#include "hangarUI.h"

void BuildHangar()
{
	if (gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel") != nullptr)
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel")->removeAllWidgets();
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel"));
	}
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::ScrollablePanel, "Panel3", "98%", "98%", "1%", "1%", false), "hangarMainPanel");

	for (int i = 0; i < gEnv->game.player.fighterPlanes.size(); i++)
	{
		float posY = i % 2 == 0 ? gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel")->getSize().y * 0.01 : gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel")->getSize().y * 0.59;
		tgui::BitmapButton::Ptr but = createWidget(WidgetType::BitmapButton, "Button", "175", "40%", std::to_string(25 + 200 * (int)(i / 2)), std::to_string(posY))->cast<tgui::BitmapButton>();
		gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel")->add(but);

		float posY2 = i % 2 == 0 ? gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel")->getSize().y * 0.42 : gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel")->getSize().y * 0.51;
		tgui::BitmapButton::Ptr but2 = createWidget(WidgetType::BitmapButton, "Button", "175/2", "7%", std::to_string(25 + 200 * (int)(i / 2) + (int)(175 / 4)), std::to_string(posY2))->cast<tgui::BitmapButton>();
		gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel")->add(but2);
	}
}

void addShipToHangar(Ship *s)
{
	if (gEnv->game.player.fighterPlanes.size() < gEnv->game.player.hangarSize)
	{
		gEnv->game.player.fighterPlanes.push_back(s);
		BuildHangar();
	}
}