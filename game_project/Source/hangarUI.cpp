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
		updateShipValues(gEnv->game.player.fighterPlanes[id]);
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
		gEnv->game.adventureGUI.get<tgui::BitmapButton>("pilotFighterButton" + std::to_string(id))->setText(c->name);
		updateShipValues(gEnv->game.player.fighterPlanes[id]);
	}
	else
	{
		gEnv->game.player.fighterPlanes[id]->characterPosition[0]->haveRole = false;
		gEnv->game.player.fighterPlanes[id]->characterPosition[0]->role = characterRole::noneRole;

		c->haveRole = true;
		c->role = gEnv->game.player.fighterPlanes[id]->characterRoleSlots[0];
		gEnv->game.player.fighterPlanes[id]->characterPosition[0] = c;
		gEnv->game.adventureGUI.get<tgui::BitmapButton>("pilotFighterButton" + std::to_string(id))->setText(c->name);
		updateShipValues(gEnv->game.player.fighterPlanes[id]);
	}
}

void buildFigtherModules(int id)
{
	gEnv->game.ui.activeOpenFighterWindow = id;
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("hangarMainPanel"), false);

	if (gEnv->game.adventureGUI.get<tgui::Panel>("fighterModules") != nullptr)
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("fighterModules")->removeAllWidgets();
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->remove(gEnv->game.adventureGUI.get<tgui::Panel>("fighterModules"));
	}

	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::Panel, "Panel3", "43%", "60%", "5%", "2%"), "fighterModules");
	gEnv->game.adventureGUI.get<tgui::Panel>("fighterModules")->add(createWidget(WidgetType::BitmapButton, "Button", "130", "30", "70%", "2%"), "fighterPriority");
	gEnv->game.adventureGUI.get<tgui::BitmapButton>("fighterPriority")->setText("Modules priority");
	gEnv->game.adventureGUI.get<tgui::BitmapButton>("fighterPriority")->connect("MouseReleased", createShipModulePriorityPanel, &(*gEnv->game.player.fighterPlanes[id]));

	if (gEnv->game.adventureGUI.get<tgui::BitmapButton>("swipeFighterLeft") != nullptr)
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->remove(gEnv->game.adventureGUI.get<tgui::BitmapButton>("swipeFighterLeft"));
	}
	if (gEnv->game.adventureGUI.get<tgui::BitmapButton>("swipeFighterRight") != nullptr)
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->remove(gEnv->game.adventureGUI.get<tgui::BitmapButton>("swipeFighterRight"));
	}

	if (id != 0)
	{
		tgui::BitmapButton::Ptr left = createWidget(WidgetType::BitmapButton, "Button", "3%", "12%", "1%", "24%")->cast<tgui::BitmapButton>();
		left->setText("<");
		left->setTextSize(36);
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(left, "swipeFighterLeft");
		const int newid = id - 1;
		left->connect("MouseReleased", buildFigtherModules, newid);
	}
	if (id != gEnv->game.player.fighterPlanes.size() - 1)
	{
		tgui::BitmapButton::Ptr right = createWidget(WidgetType::BitmapButton, "Button", "3%", "12%", "50%", "24%")->cast<tgui::BitmapButton>();
		right->setText(">");
		right->setTextSize(36);
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(right, "swipeFighterRight");
		const int newid = id + 1;
		right->connect("MouseReleased", buildFigtherModules, newid);
	}
	

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
	createShipStatPanel(gEnv->game.player.fighterPlanes[id], pan);
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