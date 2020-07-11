#include "personEquipmentUI.h"

void BuildSchemeChooseCharacter()
{
	tgui::Panel::Ptr pan = gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel");
	if (pan != nullptr)
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->remove(gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel"));
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::Panel, "Panel3", "300", "580", "73%", "1%", false), "choosePersonPanel");
	if (gEnv->game.player.shipMenu == shipMenu::crew) enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel"), true);
	

	for (int i = 0; i < gEnv->game.player.crew.characters.size(); i++)
	{
		tgui::Button::Ptr button = createWidget(WidgetType::Button, "Button", "200", "90", "0", std::to_string(i*90))->cast<tgui::Button>();
		button->setText(gEnv->game.player.crew.characters[i]->name);
		gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel")->add(button, "ChoosePerson" + std::to_string(i));
		button->connect("MouseReleased", ChangeActiveCharacter, i);

		if (i != 0)
		{
			tgui::Button::Ptr but = createWidget(WidgetType::Button, "Button", "100", "90", "200", std::to_string(i * 90))->cast<tgui::Button>();
			but->setText("Remove");
			gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel")->add(but);
			but->connect("MouseReleased", unregisterPlayerCharacter, i);
		}
	}
}

void BuildSchemeRoles()
{
	if (gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles") != NULL)
		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles")->removeAllWidgets();
	else gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::Panel, "Panel3", "840", "580", "1%", "1%", false), "ShipSchemePersonRoles");

	tgui::Button::Ptr showBonusesButton = createWidget(WidgetType::Button, "Button", "200", "50", "5%", "90%")->cast<tgui::Button>();
	showBonusesButton->setText("Show Bonuses");
	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles")->add(showBonusesButton, "CrewBonusesShow");

	for (int i = 0; i < gEnv->game.player.ship->characterRoleSlots.size(); i++)
	{
		const int id = i;
		tgui::Button::Ptr but = createWidget(WidgetType::Button, "Button", "100", "100", std::to_string(100 + i * 120), "50%")->cast<tgui::Button>();
		if (gEnv->game.player.ship->characterPosition[i] != NULL) but->setText(gEnv->game.player.ship->characterPosition[i]->name);
		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles")->add(but, "buttonChangeRole" + std::to_string(i));
		but->connect("RightMouseReleased", giveRoleFind, id, id);
	}
}

void BuildPersonSchemeUI(int equipSizeUI, int crewPersonNumber)
{
	if (gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(crewPersonNumber)) != NULL)
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(crewPersonNumber))->removeAllWidgets();
	else gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::Panel, "Panel3", "600", "370", "1%", "1%", false), "PersonSchemeEquipPanel" + std::to_string(crewPersonNumber));

	tgui::Label::Ptr characterName = createWidget(WidgetType::Label, "Label", "0", "0", "(&.size - size)/2", "2%")->cast<tgui::Label>();
	characterName->setText(gEnv->game.player.crew.characters[crewPersonNumber]->name);
	characterName->setTextSize(18);
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(crewPersonNumber))->add(characterName, "PersonSchemeName");

	for (int i(0); i < gEnv->game.player.crew.characters[crewPersonNumber]->equipment.size(); i++)
	{
		tgui::BitmapButton::Ptr btn = createWidget(WidgetType::BitmapButton, "Button", std::to_string(equipSizeUI), std::to_string(equipSizeUI), std::to_string(i <= 3 ? 30 : 600 - 30 - equipSizeUI), std::to_string(i <= 3 ? 40 + 75 * i : 40 + 75 * (i - 4)))->cast<tgui::BitmapButton>();
		if (gEnv->game.player.crew.characters[crewPersonNumber]->equipment[i] != NULL)
		{
			if (gEnv->game.player.crew.characters[crewPersonNumber]->equipment[i]->icon != nullptr)
				btn->setImage(*gEnv->game.player.crew.characters[crewPersonNumber]->equipment[i]->icon);
			else btn->setImage(gEnv->modelDB[L"itemDefault"]->tex);
		}
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(crewPersonNumber))->add(btn, "Person" + std::to_string(crewPersonNumber) + "Equip" + std::to_string(i));
		const int id = i;
		btn->connect("RightMouseReleased", personUIElementWasClicked, id);
		btn->connect("MouseReleased", personUIElementWasClicked, id);
		btn->connect("MouseEntered", applyEquipmentTooltipPersonUI, id);
	}
}

void BuildStatPersonScreen(int crewPersonNumber)
{
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::Panel, "Panel3", "400", "580", "1% + 610", "1%", false), "PersonStatScreen" + std::to_string(crewPersonNumber));
}

void BuildPersonSkillTree(int crewPersonNumber)
{
	tgui::Panel::Ptr mainPersonPanel = createWidget(WidgetType::Panel, "Panel3", "100%", "10%", "0", "0", false)->cast<tgui::Panel>();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(mainPersonPanel, "NamePointsPanel" + std::to_string(crewPersonNumber));

	tgui::Panel::Ptr mainPersonPanel2 = createWidget(WidgetType::Panel, "Panel3", "25%", "90%", "0", "10%", false)->cast<tgui::Panel>();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(mainPersonPanel, "PersonFirstSkillTree" + std::to_string(crewPersonNumber));

	tgui::Label::Ptr lab = createWidget(WidgetType::Label, "Label", "0", "0", "(&.width - width) / 2", "10")->cast<tgui::Label>();
	lab->setText(gEnv->game.player.crew.characters[crewPersonNumber]->name);
	lab->setTextSize(20);
	mainPersonPanel->add(lab);

	lab = createWidget(WidgetType::Label, "Label", "0", "0", "(&.width - width) / 4 - 20", "30")->cast<tgui::Label>();
	lab->setText("Level: " + std::to_string(gEnv->game.player.crew.characters[crewPersonNumber]->level));
	lab->setTextSize(20);
	mainPersonPanel->add(lab, "labSkillTreeLevel" + std::to_string(crewPersonNumber));

	lab = createWidget(WidgetType::Label, "Label", "0", "0", "(&.width - width) / 4 * 3 + 20", "30")->cast<tgui::Label>();
	lab->setText("Skill points: " + std::to_string(gEnv->game.player.crew.characters[crewPersonNumber]->skillPoints));
	lab->setTextSize(20);
	mainPersonPanel->add(lab,  "labSkillTreePoints" + std::to_string(crewPersonNumber));

	Character *c = gEnv->game.player.crew.characters[crewPersonNumber];

	for (int i = 1; i <= 5; i++)
	{
		tgui::Label::Ptr label = tgui::Label::create();
		label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
		label->setText("Level: " + std::to_string(i));
		label->setPosition(5, 70 + 60 * (i - 1));
		label->setTextSize(20);
		mainPersonPanel2->add(label);
		int rep = 0;
		for (auto j : c->skillTrees[0])
		{
			if (i == j->level)
				rep++;
		}
		int rep2 = 1;
		for (auto j : c->skillTrees[0])
		{
			if (i == j->level)
			{
				tgui::Button::Ptr button = tgui::Button::create();
				j->active ? button->setRenderer(gEnv->globalTheme.getRenderer("Button2")) : button->setRenderer(gEnv->globalTheme.getRenderer("Button"));
				button->setSize(50, 50);
				switch (rep)
				{
				case 1:
					button->setPosition("(&.width - width) / 2 + 25", 70 + 60 * (i - 1));
					break;
				case 2:
					switch (rep2)
					{
					case 1:
						button->setPosition("(&.width - width) / 3 + 25", 70 + 60 * (i - 1));
						rep2++;
						break;
					case 2:
						button->setPosition("(&.width - width) / 3 * 2 + 25", 70 + 60 * (i - 1));
						break;
					}
					break;
				case 3:
					switch (rep2)
					{
					case 1:
						button->setPosition("(&.width - width) / 4 + 25", 70 + 60 * (i - 1));
						rep2++;
						break;
					case 2:
						button->setPosition("(&.width - width) / 4 * 2 + 25", 70 + 60 * (i - 1));
						rep2++;
						break;
					case 3:
						button->setPosition("(&.width - width) / 4 * 3 + 25", 70 + 60 * (i - 1));
						break;
					}
					break;
				}
				mainPersonPanel2->add(button);
				button->setText(j->name);

				button->connect("MouseReleased", skillUp, &(*c), &(*j), 0);
			}
		}
	}
}

void UpdatePersonSkillTree()
{
	for (int i = 0; i < gEnv->game.player.crew.characters.size(); i++)
	{
		gEnv->game.adventureGUI.get<tgui::Label>("labSkillTreeLevel" + std::to_string(i))->setText("Level: " + std::to_string(gEnv->game.player.crew.characters[i]->level));
		gEnv->game.adventureGUI.get<tgui::Label>("labSkillTreePoints" + std::to_string(i))->setText("Skill points: " + std::to_string(gEnv->game.player.crew.characters[i]->skillPoints));
	}
}

void UpdateStatPersonScreen()
{
	updateCharacterStats(gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]);
	
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))->removeAllWidgets();

	#pragma region Person Stats Labels



	tgui::Label::Ptr label = tgui::Label::create();
	label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label->setPosition("(&.width - width) / 2", 10);
	label->setText(gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->name);
	label->setTextSize(24);
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))->add(label);

	tgui::Label::Ptr label2 = tgui::Label::create();
	label2->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label2->setPosition("(&.width - width) / 4", 40);
	label2->setText(L"Class: " + gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->characterClass);
	label2->setTextSize(20);
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))->add(label2);

	tgui::Label::Ptr label3 = tgui::Label::create();
	label3->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label3->setPosition("(&.width - width) / 4 * 3", 40);
	label3->setText(L"Race: " + gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->characterRace);
	label3->setTextSize(20);
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))->add(label3);

	tgui::Label::Ptr label4 = tgui::Label::create();
	label4->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label4->setPosition("(&.width - width) / 4", 70);
	switch (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->role){
	case characterRole::noneRole:
		label4->setText(L"Role: none");
		break;
	}
	label4->setTextSize(20);
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))->add(label4);

	tgui::Label::Ptr label5 = tgui::Label::create();
	label5->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label5->setPosition("(&.width - width) / 4 * 3", 70);
	switch (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->role) {
	case characterAspect::noneAspect:
		label5->setText(L"Aspect: none");
		break;
	}
	label5->setTextSize(20);
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))->add(label5);

	tgui::Label::Ptr label6 = tgui::Label::create();
	label6->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label6->setPosition("(&.width - width) / 2", 100);
	label6->setText(L"Health: " + std::to_wstring((int)(gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->health.total)));
	label6->setTextSize(20);
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))->add(label6);
	#pragma endregion
}

void BuildPanelChangePersonState()
{

	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::Panel, "Panel", "150", "580", "1% + 1010", "1%", false), "PanelChangePersonState");

	tgui::Button::Ptr button = createWidget(WidgetType::Button, "Button", "180", "200", "-15", "0")->cast<tgui::Button>();
	button->setText("Inventory");
	gEnv->game.adventureGUI.get<tgui::Panel>("PanelChangePersonState")->add(button, "ChoosePersonInventory");
	button->connect("MouseReleased", ChangePersonPanelsState, PUIState::inventoryState);

	tgui::Button::Ptr button2 = createWidget(WidgetType::Button, "Button", "180", "200", "-15", "33%")->cast<tgui::Button>();
	button2->setText("Skill Tree");
	gEnv->game.adventureGUI.get<tgui::Panel>("PanelChangePersonState")->add(button2, "ChoosePersonInventory");
	button2->connect("MouseReleased", ChangePersonPanelsState, PUIState::skillTreeState);

	tgui::Button::Ptr button3 = createWidget(WidgetType::Button, "Button", "180", "200", "-15", "66%")->cast<tgui::Button>();
	button3->setText("Battle Abilities");
	gEnv->game.adventureGUI.get<tgui::Panel>("PanelChangePersonState")->add(button3, "ChoosePersonInventory");
	button3->connect("MouseReleased", ChangePersonPanelsState, PUIState::battleAbilitiesState);

}

void ChangeActiveCharacter(int id)
{
	gEnv->game.ui.activeOpenPersonWindow = id;
	ChangePersonPanelsState(PUIState::inventoryState);
}

void ChangePersonPanelsState(PUIState::personUIstate state)
{
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel"), false);
	for (int i = 0; i < gEnv->game.player.crew.characters.size(); i++)
	{
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(i)), false);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(i)), false);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("PersonFirstSkillTree" + std::to_string(i)), false);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("NamePointsPanel" + std::to_string(i)), false);
	}
	switch (state)
	{
	case PUIState::defaultState:
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel"), true);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles"), true);
		break;
	case PUIState::inventoryState:
		UpdateStatPersonScreen();
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel"), true);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel"), true);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel"
			+ std::to_string(gEnv->game.ui.activeOpenPersonWindow)), true);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen"
			+ std::to_string(gEnv->game.ui.activeOpenPersonWindow)), true);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("PanelChangePersonState"), true);
		break;
	case PUIState::skillTreeState:
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("PanelChangePersonState"), true);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("PersonFirstSkillTree" + std::to_string(gEnv->game.ui.activeOpenPersonWindow)), true);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("NamePointsPanel" + std::to_string(gEnv->game.ui.activeOpenPersonWindow)), true);
		break;
	case PUIState::battleAbilitiesState:
		break;
	}
}

void skillUp(Character *c, PassiveSkill *p, int treeNumber, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (c->level < p->level || c->skillPoints == 0) return;

	bool ok = true;
	for (auto pp : c->skillTrees[treeNumber])
	{
		if ((pp->level == p->level) && (pp->active == true))
			ok = false;
	}

	bool ok2 = false;
	if (p->level == 1) ok2 = true;
	else for (auto pp : c->skillTrees[treeNumber])
	{
		if (pp->level + 1 == p->level && pp != p)
		{
			if (pp->active)
				ok2 = true;
		}
	}

	if (!ok || !ok2) return;

	p->active = true;
	if (p->effect->targetType == targetType::ship)
	{
		c->effectsForShip.push_back(p->effect);
		updateShipValues(gEnv->game.player.ship);
		buildShipStats();
	}
	
	widget->setRenderer(gEnv->globalTheme.getRenderer("Button2"));
	c->skillPoints--;

	UpdatePersonSkillTree();
}

void giveRoleFind(int id, int buttonId, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (!gEnv->game.ui.rmWasClicked)
	{
		int x = sf::Mouse::getPosition(gEnv->globalWindow).x;
		int y = sf::Mouse::getPosition(gEnv->globalWindow).y - 5;
		gEnv->game.adventureGUI.add(createWidget(WidgetType::Panel, "Panel", "0", "0", std::to_string(x), std::to_string(y)), "tempRightPanel");
		gEnv->game.ui.rmWasClicked = true;

		int count = 0;
		for (int i = 0; i < gEnv->game.player.crew.characters.size(); i++)
		{
			if (!gEnv->game.player.crew.characters[i]->haveRole)
			{
				tgui::Button::Ptr but = createWidget(WidgetType::Button, "Button", "120", "30", "-10", std::to_string(30*count))->cast<tgui::Button>();
				count++;
				but->setText(gEnv->game.player.crew.characters[i]->name);
				gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->add(but);
				const int constButtonId = buttonId;
				but->connect("MouseReleased", giveRole, &(*gEnv->game.player.crew.characters[i]), constButtonId);
			}
		}
		gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->setSize(100, 30 * (count + 1));

		if (count == 0) {
			gEnv->game.ui.rmWasClicked = false;
			gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
		}
		else
		{
			tgui::Button::Ptr but = createWidget(WidgetType::Button, "Button", "120", "30", "-10", std::to_string(30*count))->cast<tgui::Button>();
			but->setText("Cancel");
			gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->add(but);
			const int constButtonId = buttonId;
			but->connect("MouseReleased", giveRole, nullptr, constButtonId);
		}
	}
}

void giveRole(Character *c, int buttonId, tgui::Widget::Ptr widget, const std::string& signalName)
{
	std::string str = widget->cast<tgui::Button>()->getText();
	if (str == "Cancel")
	{
		gEnv->game.ui.rmWasClicked = false;
		gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->removeAllWidgets();
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
	}
	else
	{
		gEnv->game.ui.rmWasClicked = false;
		gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->removeAllWidgets();
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));

		gEnv->game.adventureGUI.get<tgui::Button>("buttonChangeRole" + std::to_string(buttonId))->setText(c->name);
		c->haveRole = true;
		c->role = gEnv->game.player.ship->characterRoleSlots[buttonId];
		gEnv->game.player.ship->characterPosition[buttonId] = c;

		updateShipValues(gEnv->game.player.ship);
		buildShipStats();
	}
}

void giveRoleCaptain(Character *c, int buttonId = 0)
{
	gEnv->game.adventureGUI.get<tgui::Button>("buttonChangeRole" + std::to_string(buttonId))->setText(c->name);
	c->haveRole = true;
	c->role = gEnv->game.player.ship->characterRoleSlots[buttonId];
	gEnv->game.player.ship->characterPosition[buttonId] = c;

	updateShipValues(gEnv->game.player.ship);
	buildShipStats();
}

void registerPlayerCharacter(Character *c)
{
	int id = gEnv->game.ui.characterPlayerCount++;
	gEnv->game.player.crew.characters.push_back(c);
	BuildPersonSchemeUI(50, id);
	BuildStatPersonScreen(id);
	BuildPersonSkillTree(id);
	BuildSchemeChooseCharacter();
}

void unregisterPlayerCharacter(int id)
{
	if (id != 0)
	{
		for (int i = 0; i < gEnv->game.ui.characterPlayerCount; i++)
		{
			gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(i))->removeAllWidgets();
			gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->remove(gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(i)));

			gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(i))->removeAllWidgets();
			gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->remove(gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(i)));

			gEnv->game.adventureGUI.get<tgui::Panel>("NamePointsPanel" + std::to_string(i))->removeAllWidgets();
			gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->remove(gEnv->game.adventureGUI.get<tgui::Panel>("PersonFirstSkillTree" + std::to_string(i)));
			gEnv->game.adventureGUI.get<tgui::Panel>("PersonFirstSkillTree" + std::to_string(i))->removeAllWidgets();
			gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->remove(gEnv->game.adventureGUI.get<tgui::Panel>("PersonFirstSkillTree" + std::to_string(i)));
		}

		gEnv->game.ui.characterPlayerCount = 0;
		std::vector<Character*> temp;
		for (int i = 0; i < gEnv->game.player.crew.characters.size(); i++)
		{
			if (i != id)
				temp.push_back(gEnv->game.player.crew.characters[i]);
		}
		if (gEnv->game.player.crew.characters[id]->haveRole)
		{
			for (int i = 0; i < gEnv->game.player.ship->characterPosition.size(); i++)
			{
				if (gEnv->game.player.crew.characters[id] == gEnv->game.player.ship->characterPosition[i]) {
					gEnv->game.player.ship->characterPosition[i] = NULL;
					break;
				}
			}
		}
		gEnv->game.player.crew.characters.clear();
		for (int i = 0; i < temp.size(); i++)
			registerPlayerCharacter(temp[i]);

		gEnv->game.ui.activeOpenPersonWindow = 0;
		BuildSchemeRoles();
		BuildSchemeChooseCharacter();
	}
}

void applyEquipmentTooltipPersonUI(int id)
{
	if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id] != NULL)
	{
		if (!gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id]->tooltipWasCreated)
		{
			createEquipmentTooltip(gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id]);
			gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id]->tooltipWasCreated = true;
		}
		gEnv->game.adventureGUI.get<tgui::BitmapButton>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(id))
			->setToolTip(gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id]->tooltipDescription);
	}
}

void deleteAllTooltipsPersonUI()
{
	for (int i = 0; i < gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment.size(); i++)
	{
		gEnv->game.adventureGUI.get<tgui::BitmapButton>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(i))->setToolTip(NULL);
	}
}