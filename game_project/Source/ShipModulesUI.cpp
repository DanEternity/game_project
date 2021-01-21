#include "shipModulesUI.h"
#include "enviroment.h"
#include "LocaleLoader.h"

void BuildShipSchemeUI(int moduleSizeUI)
{
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::Panel, "Panel3", "52%", "60%", "1%", "2%", false), "ShipSchemeModulesPanel");

	tgui::Button::Ptr priorityButton = createWidget(WidgetType::Button, "Button", "130", "30", "76%", "2%")->cast<tgui::Button>();
	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->add(priorityButton, "priorityButton");
	priorityButton->setText(L"Modules priority");
	priorityButton->connect("MouseReleased", createShipModulePriorityPanel, &(*gEnv->game.player.ship));
	
	for (int i(0); i < gEnv->game.player.ship->modules.size(); i++)
	{
		tgui::BitmapButton::Ptr btn = createWidget(WidgetType::BitmapButton, "Button", std::to_string(moduleSizeUI), std::to_string(moduleSizeUI), std::to_string(25 + (i % 5) * 90), std::to_string(50 + (i / 5) * 80))->cast<tgui::BitmapButton>();
		if (gEnv->game.player.ship->modules[i] != NULL)
		{
			if (gEnv->game.player.ship->modules[i]->icon != nullptr)
				btn->setImage(*gEnv->game.player.ship->modules[i]->icon);
			else
				btn->setImage(gEnv->modelDB[L"itemDefault"]->tex);
		}
		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->add(btn, "ShipSchemeModule" + std::to_string(i));
		const int id = i;

		btn->connect("MouseReleased", handleShipModulesPanelEvent, id);
		btn->connect("RightMouseReleased", handleShipModulesPanelEvent, id);
		btn->connect("MouseEntered", applyModuleTooltipShipUI, id);
		btn->setToolTip(gEnv->game.ui.tooltipDescription);
	}
}

void buildShipStats()
{
	createShipStatPanel(gEnv->game.player.ship, gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel"));
		
	for (int i(0); i < gEnv->game.player.ship->modules.size(); i++)
	{
		if (gEnv->game.player.ship->modules[i] != NULL) {
			if (gEnv->game.player.ship->modules[i]->online)
				gEnv->game.adventureGUI.get<tgui::BitmapButton>("ShipSchemeModule" + std::to_string(i))->setImage(*gEnv->game.player.ship->modules[i]->icon);
			else
				gEnv->game.adventureGUI.get<tgui::BitmapButton>("ShipSchemeModule" + std::to_string(i))->setImage(gEnv->modelDB[L"noEnergy"]->tex);
		}
		else
			gEnv->game.adventureGUI.get<tgui::BitmapButton>("ShipSchemeModule" + std::to_string(i))->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	}
}

void updateShipSchemeUI()
{
	for (int i(0); i < gEnv->game.player.ship->modules.size(); i++)
	{
		tgui::BitmapButton::Ptr btn = gEnv->game.adventureGUI.get<tgui::BitmapButton>("ShipSchemeModule" + std::to_string(i));
		if (gEnv->game.player.ship->modules[i] != NULL)
		{
			if (gEnv->game.player.ship->modules[i]->icon != nullptr)
				btn->setImage(*gEnv->game.player.ship->modules[i]->icon);
			else
			{
				giveIconToItem(gEnv->game.player.ship->modules[i]);
				btn->setImage(*gEnv->game.player.ship->modules[i]->icon);
				//btn->setImage(gEnv->modelDB[L"itemDefault"]->tex);
			}
		}
		else btn->setImage(gEnv->modelDB[L"itemEmpty"]->tex);
	}
}

void createShipModulePriorityPanel(Ship *s)
{
	if (gEnv->game.adventureGUI.get<tgui::Panel>("priorityPanel") != nullptr)
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("priorityPanel")->removeAllWidgets();
	}
	else 
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::ScrollablePanel, "Panel", "300", "500", "60%", "5%", false), "priorityPanel");

	if (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("priorityPanel")->isVisible())
	{
		enableWidget(gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("priorityPanel"), false);
	}
	else {
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("priorityPanel")->moveToFront();
		enableWidget(gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("priorityPanel"), true);
		for (int i = 0; i < s->modules.size(); i++)
		{
			tgui::Label::Ptr label;
			if (s->modules[i] != NULL)
			{
				label = createWidgetLabel("Label", "(&.width - width) / 2", std::to_string(20 + i * 60), 20,s->modules[i]->name + L" [" + std::to_wstring(s->modules[i]->powerPriority) + L"]");
				gEnv->game.adventureGUI.get<tgui::Panel>("priorityPanel")->add(label, "labelModulePriority" + std::to_string(i));
			}
			if (i != 0 && s->modules[i] != NULL)
			{
				tgui::Button::Ptr button1 = createWidget(WidgetType::Button, "Button", "30", "30", "5%", std::to_string(20 + i * 60))->cast<tgui::Button>();
				button1->setText("<");
				gEnv->game.adventureGUI.get<tgui::Panel>("priorityPanel")->add(button1);
				button1->connect("MouseReleased", changeShipModulePriority, i, false, &(*s));

				tgui::Button::Ptr button2 = createWidget(WidgetType::Button, "Button", "30", "30", "90%", std::to_string(20 + i * 60))->cast<tgui::Button>();
				button2->setText(">");
				gEnv->game.adventureGUI.get<tgui::Panel>("priorityPanel")->add(button2);
				button2->connect("MouseReleased", changeShipModulePriority, i, true, &(*s));
			}
		}
	}
}

void changeShipModulePriority(int id, bool isUp, Ship *s)
{
	if (isUp)
	{
		if (s->modules[id]->powerPriority < 99)
			s->modules[id]->powerPriority++;
	}
	else
	{
		if (s->modules[id]->powerPriority > 1)
			s->modules[id]->powerPriority--;
	}
	gEnv->game.adventureGUI.get<tgui::Label>("labelModulePriority" + std::to_string(id))
				->setText(s->modules[id]->name + L" [" + std::to_wstring(s->modules[id]->powerPriority) + L"]");

	updateShipValues(s);
	buildShipStats();
}