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
		gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel")->add(but, "fighterButton" + std::to_string(i));
		but->connect("MouseReleased", buildFigtherModules, i);

		float posY2 = i % 2 == 0 ? gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel")->getSize().y * 0.42 : gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel")->getSize().y * 0.51;
		tgui::BitmapButton::Ptr but2 = createWidget(WidgetType::BitmapButton, "Button", "175/2", "7%", std::to_string(25 + 200 * (int)(i / 2) + (int)(175 / 4)), std::to_string(posY2))->cast<tgui::BitmapButton>();
		gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel")->add(but2, "pilotFighterButton" + std::to_string(i));
		but2->connect("MouseReleased", placePilotToFighterPanel, i);
		but2->connect("RightMouseReleased", placePilotToFighterPanel, i);
	}
}

void addShipToHangar(Ship *s)
{
	if (gEnv->game.player.fighterPlanes.size() < gEnv->game.player.hangarSize)
	{
		s->characterPosition.resize(1);
		s->characterRoleSlots.resize(1);
		s->characterRoleSlots[0] = characterRole::pilot;
		gEnv->game.player.fighterPlanes.push_back(s);
		BuildHangar();
	}
}

void placePilotToFighterPanel(int id)
{
	if (gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel") != nullptr)
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->removeAllWidgets();
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
	}

	int x = sf::Mouse::getPosition(gEnv->globalWindow).x;
	int y = sf::Mouse::getPosition(gEnv->globalWindow).y - 5;
	gEnv->game.adventureGUI.add(createWidget(WidgetType::Panel, "Panel", "0", "0", std::to_string(x), std::to_string(y)), "tempRightPanel");

	int count = 0;
	for (int i = 0; i < gEnv->game.player.crew.characters.size(); i++)
	{
		if (!gEnv->game.player.crew.characters[i]->haveRole)
		{
			tgui::BitmapButton::Ptr but = createWidget(WidgetType::BitmapButton, "Button", "120", "30", "-10", std::to_string(30 * count))->cast<tgui::BitmapButton>();
			count++;
			but->setText(gEnv->game.player.crew.characters[i]->name);
			gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->add(but);
			const int constButtonId = id;
			but->connect("MouseReleased", placePilotToFighter, &(*gEnv->game.player.crew.characters[i]), constButtonId, false);
		}
	}
	

	if (gEnv->game.player.fighterPlanes[id]->characterPosition[0] != NULL)
	{
		tgui::BitmapButton::Ptr but = createWidget(WidgetType::BitmapButton, "Button", "120", "30", "-10", std::to_string(30 * count))->cast<tgui::BitmapButton>();
		count++;
		but->setText("Unassign pilot");
		gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->add(but);
		const int constButtonId = id;
		but->connect("MouseReleased", placePilotToFighter, nullptr, constButtonId, true);
	}
	gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->setSize(100, 30 * (count + 1));

	if (count == 0) {
		gEnv->game.ui.rmWasClicked = false;
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
	}
	else
	{
		tgui::BitmapButton::Ptr but = createWidget(WidgetType::BitmapButton, "Button", "120", "30", "-10", std::to_string(30 * count))->cast<tgui::BitmapButton>();
		but->setText("Cancel");
		gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->add(but);
		const int constButtonId = id;
		but->connect("MouseReleased", placePilotToFighter, nullptr, constButtonId, false);
	}
}

void placePilotToFighter(Character *c, int id, bool isUnassigned)
{
	gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->removeAllWidgets();
	gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
	if (isUnassigned)
	{
		gEnv->game.player.fighterPlanes[id]->characterPosition[0]->haveRole = false;
		gEnv->game.player.fighterPlanes[id]->characterPosition[0]->role = characterRole::noneRole;
		gEnv->game.player.fighterPlanes[id]->characterPosition[0] = NULL; 
		gEnv->game.adventureGUI.get<tgui::BitmapButton>("pilotFighterButton" + std::to_string(id))->setText("");
	}
	if (c == nullptr)
	{
		return;
	}
	if (gEnv->game.player.fighterPlanes[id]->characterPosition[0] == NULL)
	{
		c->haveRole = true;
		c->role = gEnv->game.player.fighterPlanes[id]->characterRoleSlots[0];
		gEnv->game.player.fighterPlanes[id]->characterPosition[0] = c;
		updateShipValues(gEnv->game.player.fighterPlanes[id]);
		gEnv->game.adventureGUI.get<tgui::BitmapButton>("pilotFighterButton" + std::to_string(id))->setText(c->name);
	}
	else
	{
		gEnv->game.player.fighterPlanes[id]->characterPosition[0]->haveRole = false;
		gEnv->game.player.fighterPlanes[id]->characterPosition[0]->role = characterRole::noneRole;

		c->haveRole = true;
		c->role = gEnv->game.player.fighterPlanes[id]->characterRoleSlots[0];
		gEnv->game.player.fighterPlanes[id]->characterPosition[0] = c;
		updateShipValues(gEnv->game.player.fighterPlanes[id]);
		gEnv->game.adventureGUI.get<tgui::BitmapButton>("pilotFighterButton" + std::to_string(id))->setText(c->name);
	}
}

void buildFigtherModules(int id)
{
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel"), false);

	if (gEnv->game.adventureGUI.get<tgui::Panel>("fighterModules") != nullptr)
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("fighterModules")->removeAllWidgets();
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->remove(gEnv->game.adventureGUI.get<tgui::Panel>("fighterModules"));
	}

	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::Panel, "Panel3", "51%", "60%", "1%", "2%"), "fighterModules");

	if (gEnv->game.adventureGUI.get<tgui::Panel>("fighterStats") != nullptr)
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("fighterStats")->removeAllWidgets();
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->remove(gEnv->game.adventureGUI.get<tgui::Panel>("fighterStats"));
	}

	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::Panel, "Panel3", "43%", "96.5%", "55%", "2%"), "fighterStats");
	tgui::Panel::Ptr pan = gEnv->game.adventureGUI.get<tgui::Panel>("fighterStats");

	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel"), true);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel"), true);

	for (int i = 0; i < gEnv->game.player.fighterPlanes[id]->modules.size(); i++)
	{
		tgui::BitmapButton::Ptr btn = createWidget(WidgetType::BitmapButton, "Button", "50", "50", std::to_string(25 + (i % 5) * 90), std::to_string(50 + (i / 5) * 80))->cast<tgui::BitmapButton>();
		if (gEnv->game.player.fighterPlanes[id]->modules[i] != NULL)
		{
			if (gEnv->game.player.fighterPlanes[id]->modules[i]->icon == NULL)
				giveIconToItem(gEnv->game.player.fighterPlanes[id]->modules[i]);
			btn->setImage(*gEnv->game.player.fighterPlanes[id]->modules[i]->icon);
		}
		gEnv->game.adventureGUI.get<tgui::Panel>("fighterModules")->add(btn);

		const int moduleId = i; const int fighterId = id;
		btn->setToolTip(gEnv->game.ui.tooltipDescription);
		btn->connect("MouseEntered", applyFighterTooltipUI, fighterId, moduleId);
		btn->connect("MouseReleased", handleFighterModulesPanelEvent, fighterId, moduleId);
	}

	updateShipValues(gEnv->game.player.fighterPlanes[id]);
	std::string render = "Label";
	int y = 5;
	int yDif = 23;
	//Hull
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Hull") + L": " + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->hull.current) + L"/" + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->hull.total) + L" (+" + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->hullReg.total) + L" / round; NONE / day)")), "shipStatHull");
	tgui::Label::Ptr lab = tgui::Label::create();
	lab->setTextSize(18);
	lab->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	lab->setText("The strength of the ship's hull plating.\nIf the durability drops to 0, the core will be destroyed and the ship will explode.");
	gEnv->game.adventureGUI.get<tgui::Label>("shipStatHull")->setToolTip(lab);
	y += yDif;
	//Shield
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Shield") + L": " + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->shield.current) + L"/" + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->shield.total) + L" (+" + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->shieldReg.total) + L" / round; NONE / day)")), "shipStatShield");
	y += yDif;
	//Power Supply
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Energy used") + L": " + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->powerSupply.current) + L"/" + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->powerSupply.total))), "shipStatPowerSupply");
	y += yDif;
	//High Power Supply
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("High energy limit used") + L": " + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->highPowerSupply.current) + L"/" + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->highPowerSupply.total))), "shipStatHighPowerSupply");
	y += yDif;
	//Battle Action Points
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Action points in battle") + L": " + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->actionPoints.total))), "shipStatActionPoints");
	y += yDif;
	//Hull resist to damgage
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Hull resistance") + L": "
		+ std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->hullResistPhysical.total)
		+ L"/" + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->hullResistEnergy.total)
		+ L"/" + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->hullStructureStability.total)
		+ L" (Physical: "
		+ std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->hullResistPhysical.total != 0 ? (int)((gEnv->game.player.fighterPlanes[id]->hullResistPhysical.total / (gEnv->game.player.fighterPlanes[id]->hullResistPhysical.total + 100)) * 100) : 0)
		+ L"%; Energy: "
		+ std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->hullResistEnergy.total != 0 ? (int)((gEnv->game.player.fighterPlanes[id]->hullResistEnergy.total / (gEnv->game.player.fighterPlanes[id]->hullResistEnergy.total + 100)) * 100) : 0)
		+ L"%; Crit: "
		+ std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->hullStructureStability.total != 0 ? (int)((gEnv->game.player.fighterPlanes[id]->hullStructureStability.total / (gEnv->game.player.fighterPlanes[id]->hullStructureStability.total + 100)) * 100) : 0)
		+ L"%)")), "shipStatHullResist");
	y += yDif;
	//Shield resist to damage
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Shield resistance") + L": "
		+ std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->shieldResistPhysical.total)
		+ L"/" + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->shieldResistEnergy.total)
		+ L"/" + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->shieldStructureStability.total)
		+ L" (Physical: "
		+ std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->shieldResistPhysical.total != 0 ? (int)((gEnv->game.player.fighterPlanes[id]->shieldResistPhysical.total / (gEnv->game.player.fighterPlanes[id]->shieldResistPhysical.total + 100)) * 100) : 0)
		+ L"%; Energy: "
		+ std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->shieldResistEnergy.total != 0 ? (int)((gEnv->game.player.fighterPlanes[id]->shieldResistEnergy.total / (gEnv->game.player.fighterPlanes[id]->shieldResistEnergy.total + 100)) * 100) : 0)
		+ L"%; Crit: "
		+ std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->shieldStructureStability.total != 0 ? (int)((gEnv->game.player.fighterPlanes[id]->shieldStructureStability.total / (gEnv->game.player.fighterPlanes[id]->shieldStructureStability.total + 100)) * 100) : 0)
		+ L"%)")), "shipStatShieldResistPhysical");
	y += yDif;
	//Stealth, evasion, sensors and missileDefence
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, GetString("Sensor power: ") + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->sensorPower.total) + L";"), "shipStatSensors");
	pan->add(createWidgetLabel(render, "250", std::to_string(y), 18, GetString("Sensor tier: ") + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->sensorTier.total), "shipStatSensorsTier"));
	y += yDif;
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, GetString("Stealth power: ") + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->stealth.total) + L";"));
	pan->add(createWidgetLabel(render, "250", std::to_string(y), 18, GetString("Stealth tier: ") + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->stealthTier.total), "shipStatStealthTier"));
	y += yDif;
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, GetString("Evasion: ") + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->evasion.total) + L";"), "shipStatEvasion");
	pan->add(createWidgetLabel(render, "250", std::to_string(y), 18, GetString("Mobility: ") + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->mobility.total), "shipStatMobility"));
	y += yDif;
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, GetString("Missile defence power: ") + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->missileDefense.total) + L";"), "shipStatMissileDefence");
	pan->add(createWidgetLabel(render, "250", std::to_string(y), 18, GetString("Missile defence tier: ") + std::to_wstring((int)gEnv->game.player.fighterPlanes[id]->missileDefenseTier.total), "shipStatMissileDefenceTier"));

}

void applyFighterTooltipUI(int fighterId, int moduleId)
{
	if (gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId] != NULL)
	{
		switch (gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId]->moduleType)
		{
		case moduleType::system:
			createModuleTooltip(static_cast<Module*>(gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId]));
			break;
		case moduleType::weapon:
			createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId]));
			break;
		}
		gEnv->game.ui.tooltipDescription->setVisible(true);
	}
	else gEnv->game.ui.tooltipDescription->setVisible(false);
}