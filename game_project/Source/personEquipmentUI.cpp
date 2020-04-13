#include "personEquipmentUI.h"

void BuildSchemeChooseCharacter()
{
	tgui::Panel::Ptr choosePersonPanel = tgui::Panel::create();
	choosePersonPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel3"));
	choosePersonPanel->setSize(300, 580);
	choosePersonPanel->setPosition("73%", "1%");
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(choosePersonPanel, "choosePersonPanel");

	for (int i = 0; i < gEnv->game.player.crew.characters.size(); i++)
	{
		tgui::Button::Ptr button = tgui::Button::create();
		button->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		button->setSize(300, 90);
		button->setText(gEnv->game.player.crew.characters[i]->name);
		button->setPosition(0, i*90);
		choosePersonPanel->add(button, "ChoosePerson" + std::to_string(i));
		button->connect("MouseReleased", ChangeActiveCharacter, i);
	}
}

void BuildSchemeRoles()
{
	tgui::Panel::Ptr ShipSchemePersonRoles = tgui::Panel::create();
	ShipSchemePersonRoles->setRenderer(gEnv->globalTheme.getRenderer("Panel3"));
	ShipSchemePersonRoles->setSize(840, 580);
	ShipSchemePersonRoles->setPosition("1%", "1%");
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(ShipSchemePersonRoles, "ShipSchemePersonRoles");
	ShipSchemePersonRoles->setEnabled(false);
	ShipSchemePersonRoles->setVisible(false);

	tgui::Button::Ptr showBonusesButton = tgui::Button::create();
	showBonusesButton->setPosition("5%", "90%");
	showBonusesButton->setSize(200, 50);
	showBonusesButton->setText("Show Bonuses");
	showBonusesButton->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	ShipSchemePersonRoles->add(showBonusesButton, "CrewBonusesShow");
}

void BuildPersonSchemeUI(int equipSizeUI, int crewPersonNumber)
{
	tgui::Panel::Ptr mainPersonPanel = tgui::Panel::create();
	mainPersonPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel3"));
	mainPersonPanel->setSize(600, 370);
	mainPersonPanel->setPosition("1%", "1%");
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(mainPersonPanel, "PersonSchemeEquipPanel" + std::to_string(crewPersonNumber));

	tgui::Label::Ptr characterName = tgui::Label::create();
	characterName->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	characterName->setText(gEnv->game.player.crew.characters[crewPersonNumber]->name);
	characterName->setPosition("(&.size - size)/2", "2%");
	characterName->setTextSize(18);
	mainPersonPanel->add(characterName, "PersonSchemeName");

	for (int i(0); i < gEnv->game.player.crew.characters[crewPersonNumber]->equipment.size(); i++)
	{
		tgui::Button::Ptr btn = tgui::Button::create();
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setSize(equipSizeUI, equipSizeUI);
		btn->setPosition(i <= 3 ? 30 : 600 - 30 - equipSizeUI, i <= 3 ? 40+75*i : 40+75*(i-4));
		if (gEnv->game.player.crew.characters[crewPersonNumber]->equipment[i] != NULL)
			btn->setText(gEnv->game.player.crew.characters[i]->equipment[i]->name);
		mainPersonPanel->add(btn, "Person" + std::to_string(crewPersonNumber) + "Equip" + std::to_string(i));
		const int id = i;
		btn->connect("RightMouseReleased", personUIElementWasClicked, id);
		btn->connect("MouseReleased", personUIElementWasClicked, id);
	}

	mainPersonPanel->setEnabled(false);
	mainPersonPanel->setVisible(false);
}

void BuildStatPersonScreen(int crewPersonNumber)
{
	tgui::Panel::Ptr mainPersonPanel = tgui::Panel::create();
	mainPersonPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel3"));
	mainPersonPanel->setSize(400, 580);
	mainPersonPanel->setPosition("1% + 610", "1%");
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(mainPersonPanel, "PersonStatScreen" + std::to_string(crewPersonNumber));
	mainPersonPanel->setVisible(false);
	mainPersonPanel->setEnabled(false);
}

void UpdateStatPersonScreen()
{
	updateCharacterStats();
	
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))->removeAllWidgets();

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

}

void BuildPanelChangePersonState()
{
	tgui::Panel::Ptr mainPersonPanel = tgui::Panel::create();
	mainPersonPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
	mainPersonPanel->setSize(150, 580);
	mainPersonPanel->setPosition("1% + 1010", "1%");
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(mainPersonPanel, "PanelChangePersonState");
	mainPersonPanel->setVisible(false);
	mainPersonPanel->setEnabled(false);

	tgui::Button::Ptr button = tgui::Button::create();
	button->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	button->setSize(180, 600 / 3);
	button->setPosition(-15, 0);
	button->setText("Inventory");
	mainPersonPanel->add(button, "ChoosePersonInventory");

	tgui::Button::Ptr button2 = tgui::Button::create();
	button2->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	button2->setSize(180, 600 / 3);
	button2->setPosition(-15, "33%");
	button2->setText("Skill Tree");
	mainPersonPanel->add(button2, "ChoosePersonInventory");

	tgui::Button::Ptr button3 = tgui::Button::create();
	button3->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	button3->setSize(180, 600 / 3);
	button3->setPosition(-15, "66%");
	button3->setText("Battle Abilities");
	mainPersonPanel->add(button3, "ChoosePersonInventory");

}

void personUIElementWasClicked(const int id, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (signalName == "MouseReleased")
	{
		if (gEnv->game.player.pickedItem != NULL)
		{
			auto p_equip = static_cast<Equipment*>(gEnv->game.player.pickedItem);
			auto type = p_equip->equipmentSlotType;

			auto s_slot = gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->slot[id];

			// compare to compability

			if (s_slot == type)
			{
				gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(gEnv->game.player.pickedLocalInventory))->setRenderer(gEnv->globalTheme.getRenderer("Button"));
				auto tmp = gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId];

				gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id];
				gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id] = static_cast<Equipment*>(tmp);

				widget->cast<tgui::Button>()->setText(gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id]->name);

				gEnv->game.player.pickedItemInvId = -1;
				gEnv->game.player.pickedItem = NULL;
				gEnv->game.player.pickedLocalInventory = -1;

				RebuildInventoryGridPanel();

				UpdateInventoryUI();
			}
		}
		//else gEnv->game.ui.selected
	}
	else if (signalName == "RightMouseReleased" && !gEnv->game.ui.rmWasClicked)
	{
		//ui->activermModule = widget->cast<tgui::Button>()->getText();
		tgui::Panel::Ptr temp = tgui::Panel::create();
		temp->setSize(100, 120);
		int x = sf::Mouse::getPosition(gEnv->globalWindow).x;
		int y = sf::Mouse::getPosition(gEnv->globalWindow).y - 5;
		temp->setPosition(x, y);
		temp->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
		gEnv->game.adventureGUI.add(temp, "tempRightPanel");
		gEnv->game.ui.rmWasClicked = true;

		tgui::Button::Ptr btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 0);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Add");
		btn->connect("MouseReleased", rmPanelClickedPerson, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 30);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Unequip");
		btn->connect("MouseReleased", rmPanelClickedPerson, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 60);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Delete");
		btn->connect("MouseReleased", rmPanelClickedPerson, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 90);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Cancel");
		btn->connect("MouseReleased", rmPanelClickedPerson, id);
	}
}

void rmPanelClickedPerson(const int id, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (widget->cast<tgui::Button>()->getText() == L"Cancel")
	{
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
		gEnv->game.ui.rmWasClicked = false;
		if (gEnv->game.ui.tempAddPanelClicked)
		{
			gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
			gEnv->game.ui.tempAddPanelClicked = false;
		}
	}
	else if (widget->cast<tgui::Button>()->getText() == L"Delete")
	{
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));

		// need to delete module correctly
		gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id] = nullptr;

		tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(gEnv->game.ui.activeOpenPersonWindow));
		panel->get<tgui::Button>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(id))->setText("");
		gEnv->game.ui.rmWasClicked = false;

		UpdateStatPersonScreen();
	}
	else if (widget->cast<tgui::Button>()->getText() == L"Unequip")
	{
		if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id] != NULL)
		{
			for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
			{
				if (gEnv->game.player.inventory[i] == NULL)
				{
					Item* temp = gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id];
					gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id] = static_cast<Equipment*>(gEnv->game.player.inventory[i]);
					gEnv->game.player.inventory[i] = temp;

					gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("inventoryPanel")
						->get<tgui::Button>("InventoryCell" + std::to_string(i))
						->setText(gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))
							->get<tgui::Button>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(id))->getText());

					gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))->get<tgui::Button>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(id))->setText("");
				
					UpdateStatPersonScreen();
				}
			}
		}
	}
	else if (widget->cast<tgui::Button>()->getText() == L"Add")
	{
		if (!gEnv->game.ui.tempAddPanelClicked)
		{
			gEnv->game.ui.tempAddPanelClicked = true;
			int goodItemsCount = 0;
			tgui::Button::Ptr btn;
			tgui::Panel::Ptr panel = tgui::Panel::create();
			for (int i(0); i < gEnv->game.player.inventory.size(); i++)
			{
				if (gEnv->game.player.inventory[i] == nullptr) continue;
				if (gEnv->game.player.inventory[i]->itemType == itemType::equipment)
				{
					if (static_cast<Equipment*>(gEnv->game.player.inventory[i])->equipmentSlotType == gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->slot[id])
					{
						btn = tgui::Button::create();
						btn->setSize(107, 31);
						btn->setPosition(0, 30 * goodItemsCount);
						btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
						btn->setText(gEnv->game.player.inventory[i]->name);
						const int num = i;
						btn->connect("MouseReleased", rmPanelChoosenAddedPerson, num, id);
						panel->add(btn);
						goodItemsCount++;
					}
				}

			}
			if (goodItemsCount != 0)
			{
				panel->setSize(100, 30 * goodItemsCount);
				auto pos = gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->getPosition();
				pos.x += 100;
				panel->setPosition(pos);
				panel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
				gEnv->game.adventureGUI.add(panel, "tempAddPanel");
			}
			else
				gEnv->game.ui.tempAddPanelClicked = false;
		}
	}
}

void rmPanelChoosenAddedPerson(const int id, const int equip_id, tgui::Widget::Ptr widget, const std::string& signalName)
{
	gEnv->game.ui.tempAddPanelClicked = true;
	Equipment* temp = static_cast<Equipment*>(gEnv->game.player.inventory[id]);

	gEnv->game.player.inventory[id] = gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[equip_id];
	gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[equip_id] = temp;

	tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel");
	tgui::Panel::Ptr panel2 = gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(gEnv->game.ui.activeOpenPersonWindow));

	if (gEnv->game.player.inventory[id] != NULL)
		panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(gEnv->game.player.inventory[id]->name);
	else
		panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(L"");

	if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[equip_id] != NULL)
		panel2->get<tgui::Button>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(equip_id))->setText(gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[equip_id]->name);
	else
		panel2->get<tgui::Button>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(equip_id))->setText(L"");

	gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
	gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
	gEnv->game.ui.rmWasClicked = false;
	gEnv->game.ui.tempAddPanelClicked = false;

	UpdateStatPersonScreen();
}

void ChangeActiveCharacter(int id)
{
	gEnv->game.ui.activeOpenPersonWindow = id;
	ChangePersonPanelsState(PUIState::inventoryState);
}

void ChangePersonPanelsState(PUIState::personUIstate state)
{
	gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setVisible(false);
	for (int i = 0; i < gEnv->game.player.crew.characters.size(); i++)
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(i))->setEnabled(false);
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(i))->setVisible(false);
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(i))->setEnabled(false);
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(i))->setVisible(false);

	}

	switch (state)
	{
	case PUIState::defaultState:
		gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel")->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles")->setVisible(true);
		break;
	case PUIState::inventoryState:
		UpdateStatPersonScreen();
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel"
			+ std::to_string(gEnv->game.ui.activeOpenPersonWindow))->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel"
			+ std::to_string(gEnv->game.ui.activeOpenPersonWindow))->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen"
			+ std::to_string(gEnv->game.ui.activeOpenPersonWindow))->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen"
			+ std::to_string(gEnv->game.ui.activeOpenPersonWindow))->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("PanelChangePersonState")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("PanelChangePersonState")->setVisible(true);
		break;
	case PUIState::skillTreeState:
		break;
	case PUIState::battleAbilitiesState:
		break;
	}
}