#include "shipModulesUI.h"
#include "enviroment.h"
#include "LocaleLoader.h"

void BuildShipSchemeUI(int moduleSizeUI)
{
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::Panel, "Panel3", "600", "300", "1%", "2%", false), "ShipSchemeModulesPanel");

	tgui::Button::Ptr priorityButton = createWidget(WidgetType::Button, "Button", "130", "30", "76%", "2%")->cast<tgui::Button>();
	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->add(priorityButton, "priorityButton");
	priorityButton->setText(L"Modules priority");
	priorityButton->connect("MouseReleased", createShipModulePriorityPanel);
	
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
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->removeAllWidgets();
	std::string render = "Label";
	int y = 5;
	//Hull
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Hull") + L": " + std::to_wstring((int)gEnv->game.player.ship->hull.current) + L"/" + std::to_wstring((int)gEnv->game.player.ship->hull.total) + L" (+" + std::to_wstring((int)gEnv->game.player.ship->hullReg.total) + L" / round; NONE / day)")), "shipStatHull");
	y += 20;
	//Shield
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Shield") + L": " + std::to_wstring((int)gEnv->game.player.ship->shield.current) + L"/" + std::to_wstring((int)gEnv->game.player.ship->shield.total) + L" (+" + std::to_wstring((int)gEnv->game.player.ship->shieldReg.total) + L" / round; NONE / day)")), "shipStatShield");
	y += 20;
	//Power Supply
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Energy used") + L": "+ std::to_wstring((int)gEnv->game.player.ship->powerSupply.current)+ L"/"+ std::to_wstring((int)gEnv->game.player.ship->powerSupply.total))), "shipStatPowerSupply");
	y += 20;
	//High Power Supply
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("High energy limit used") + L": "+ std::to_wstring((int)gEnv->game.player.ship->highPowerSupply.current)+ L"/"+ std::to_wstring((int)gEnv->game.player.ship->highPowerSupply.total))), "shipStatHighPowerSupply");
	y += 20;
	//Battle Action Points
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Action points in battle") + L": " +  std::to_wstring((int)gEnv->game.player.ship->actionPoints.total))), "shipStatActionPoints");
	y += 20;
	//Hull resist to damgage
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Hull resistance") + L": "
		+ std::to_wstring((int)gEnv->game.player.ship->hullResistPhysical.total)
		+ L"/" + std::to_wstring((int)gEnv->game.player.ship->hullResistEnergy.total)
		+ L"/" + std::to_wstring((int)gEnv->game.player.ship->hullStructureStability.total)
		+ L" (Physical: "
		+ std::to_wstring((int)gEnv->game.player.ship->hullResistPhysical.total != 0 ? (int)((gEnv->game.player.ship->hullResistPhysical.total / (gEnv->game.player.ship->hullResistPhysical.total + 100)) * 100) : 0)
		+ L"%; Energy: " 
		+ std::to_wstring((int)gEnv->game.player.ship->hullResistEnergy.total != 0 ? (int)((gEnv->game.player.ship->hullResistEnergy.total / (gEnv->game.player.ship->hullResistEnergy.total + 100)) * 100) : 0)
		+ L"%; Crit: " 
		+ std::to_wstring((int)gEnv->game.player.ship->hullStructureStability.total != 0 ? (int)((gEnv->game.player.ship->hullStructureStability.total / (gEnv->game.player.ship->hullStructureStability.total + 100)) * 100) : 0)
		+ L"%)")), "shipStatHullResist");
	y += 20;
	//Shield resist to damage
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Shield resistance") + L": "
		+ std::to_wstring((int)gEnv->game.player.ship->shieldResistPhysical.total)
		+ L"/" + std::to_wstring((int)gEnv->game.player.ship->shieldResistEnergy.total)
		+ L"/" + std::to_wstring((int)gEnv->game.player.ship->shieldStructureStability.total)
		+ L" (Physical: "
		+ std::to_wstring((int)gEnv->game.player.ship->shieldResistPhysical.total != 0 ? (int)((gEnv->game.player.ship->shieldResistPhysical.total / (gEnv->game.player.ship->shieldResistPhysical.total + 100)) * 100) : 0)
		+ L"%; Energy: "
		+ std::to_wstring((int)gEnv->game.player.ship->shieldResistEnergy.total != 0 ? (int)((gEnv->game.player.ship->shieldResistEnergy.total / (gEnv->game.player.ship->shieldResistEnergy.total + 100)) * 100) : 0)
		+ L"%; Crit: "
		+ std::to_wstring((int)gEnv->game.player.ship->shieldStructureStability.total != 0 ? (int)((gEnv->game.player.ship->shieldStructureStability.total / (gEnv->game.player.ship->shieldStructureStability.total + 100)) * 100) : 0)
		+ L"%)")), "shipStatShieldResistPhysical");
	y += 20;

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

void createShipModulePriorityPanel()
{
	if (gEnv->game.adventureGUI.get<tgui::Panel>("priorityPanel") != nullptr)
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("priorityPanel")->removeAllWidgets();
	}
	else 
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::ScrollablePanel, "Panel", "300", "500", "60%", "5%", true), "priorityPanel");

	if (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("priorityPanel")->isVisible())
	{
		enableWidget(gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("priorityPanel"), false);
	}
	else {
		enableWidget(gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("priorityPanel"), true);
		for (int i = 0; i < gEnv->game.player.ship->modules.size(); i++)
		{
			tgui::Label::Ptr label;
			if (gEnv->game.player.ship->modules[i] != NULL)
			{
				label = createWidgetLabel("Label", "(&.width - width) / 2", std::to_string(20 + i * 60), 20, gEnv->game.player.ship->modules[i]->name + L" [" + std::to_wstring(gEnv->game.player.ship->modules[i]->powerPriority) + L"]");
				gEnv->game.adventureGUI.get<tgui::Panel>("priorityPanel")->add(label, "labelModulePriority" + std::to_string(i));
			}
			if (i != 0 && gEnv->game.player.ship->modules[i] != NULL)
			{
				tgui::Button::Ptr button1 = createWidget(WidgetType::Button, "Button", "30", "30", "5%", std::to_string(20 + i * 60))->cast<tgui::Button>();
				button1->setText("<");
				gEnv->game.adventureGUI.get<tgui::Panel>("priorityPanel")->add(button1);
				button1->connect("MouseReleased", changeShipModulePriority, i, false);

				tgui::Button::Ptr button2 = createWidget(WidgetType::Button, "Button", "30", "30", "90%", std::to_string(20 + i * 60))->cast<tgui::Button>();
				button2->setText(">");
				gEnv->game.adventureGUI.get<tgui::Panel>("priorityPanel")->add(button2);
				button2->connect("MouseReleased", changeShipModulePriority, i, true);
			}
		}
	}
}

void changeShipModulePriority(int id, bool isUp)
{
	if (isUp)
	{
		if (gEnv->game.player.ship->modules[id]->powerPriority < 99)
			gEnv->game.player.ship->modules[id]->powerPriority++;
	}
	else
	{
		if (gEnv->game.player.ship->modules[id]->powerPriority > 1)
			gEnv->game.player.ship->modules[id]->powerPriority--;
	}
	gEnv->game.adventureGUI.get<tgui::Label>("labelModulePriority" + std::to_string(id))
				->setText(gEnv->game.player.ship->modules[id]->name + L" [" + std::to_wstring(gEnv->game.player.ship->modules[id]->powerPriority) + L"]");

	updateShipValues(gEnv->game.player.ship);
	buildShipStats();
}

void applyModuleTooltipShipUI(int id)
{
	if (gEnv->game.player.ship->modules[id] != NULL)
	{
		switch (gEnv->game.player.ship->modules[id]->moduleType)
		{
		case moduleType::system:
			createModuleTooltip(static_cast<Module*>(gEnv->game.player.ship->modules[id]));
			break;
		case moduleType::weapon:
			createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.ship->modules[id]));
			break;
		}
		gEnv->game.ui.tooltipDescription->setVisible(true);
	}
	else gEnv->game.ui.tooltipDescription->setVisible(false);
}