#include "personEquipmentUI.h"

void BuildPersonSchemeUI(int equipSizeUI, int crewPersonNumber)
{
	tgui::Panel::Ptr mainPersonPanel = tgui::Panel::create();
	mainPersonPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
	mainPersonPanel->setSize(350, 550);
	mainPersonPanel->setPosition("67%", "5%");
	gEnv->game.adventureGUI.get<tgui::Panel>("adventuryUIInventoryMainPanel")->add(mainPersonPanel, "PersonSchemeEquipPanel");

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
				tgui::Panel::Ptr panel2 = gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel");

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
	}
	else if (signalName == "RightMouseReleased" && !gEnv->game.ui.rmWasClicked)
	{
		//ui->activermModule = widget->cast<tgui::Button>()->getText();
		tgui::Panel::Ptr temp = tgui::Panel::create();
		temp->setSize(100, 90);
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
		btn->setText(L"Delete");
		btn->connect("MouseReleased", rmPanelClickedPerson, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 60);
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

		tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel");
		panel->get<tgui::Button>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(id))->setText("");
		gEnv->game.ui.rmWasClicked = false;
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
	tgui::Panel::Ptr panel2 = gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel");

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