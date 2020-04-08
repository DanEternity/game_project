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
	mainPersonPanel->setSize(400, 550);
	mainPersonPanel->setPosition("60%", "5%");
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
		btn->setPosition(30,40+75*i);
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

void personUIElementWasClicked(const int id, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (signalName == "MouseReleased")
	{
		if (gEnv->game.ui.selected != -1)
		{
			if (static_cast<Equipment*>(gEnv->game.player.inventory[gEnv->game.ui.selected])->equipmentSlotType == gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->slot[id])
			{
				Equipment* temp = static_cast<Equipment*>(gEnv->game.player.inventory[gEnv->game.ui.selected]);

				gEnv->game.player.inventory[gEnv->game.ui.selected] = gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id];
				gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id] = temp;

				tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel");
				tgui::Panel::Ptr panel2 = gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(gEnv->game.ui.activeOpenPersonWindow));

				if (gEnv->game.player.inventory[gEnv->game.ui.selected] != NULL)
					panel->get<tgui::Button>("InventoryCell" + std::to_string(gEnv->game.ui.selected))->setText(gEnv->game.player.inventory[gEnv->game.ui.selected]->name);
				else
					panel->get<tgui::Button>("InventoryCell" + std::to_string(gEnv->game.ui.selected))->setText(L"");

				if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id] != NULL)
					panel2->get<tgui::Button>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(id))->setText(gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id]->name);
				else
					panel2->get<tgui::Button>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(id))->setText(L"");
				gEnv->game.ui.selected = -1;
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
}

void ChangeActiveCharacter(int id)
{
	gEnv->game.ui.puistate = PUIState::inventoryState;
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))->setVisible(false);
	gEnv->game.ui.activeOpenPersonWindow = id;
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))->setEnabled(true);
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))->setVisible(true);

	gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel")->setVisible(false);

	gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setEnabled(true);
	gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setVisible(true);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setEnabled(true);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setVisible(true);

	
	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles")->setVisible(false);
}