#include "PersonHandlers.h"


void personUIElementWasClicked(const int id, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (signalName == "MouseReleased")
	{
		printf("MouseReleased");
		if (gEnv->game.player.pickedItem != NULL)
		{
			swapElements(TargetInventory::personPanel, id);
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
		if (gEnv->game.ui.tempAddPanelClicked)
		{
			gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
			gEnv->game.ui.tempAddPanelClicked = false;
		}
		RebuildInventoryGridPanel();
		UpdateStatPersonScreen();
		BuildInventoryUI(9);
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


					gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(gEnv->game.ui.activeOpenPersonWindow))->get<tgui::Button>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(id))->setText("");

					gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
					gEnv->game.ui.rmWasClicked = false;
					if (gEnv->game.ui.tempAddPanelClicked)
					{
						gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
						gEnv->game.ui.tempAddPanelClicked = false;
					}


					RebuildInventoryGridPanel();
					BuildInventoryUI(9);
					UpdateStatPersonScreen();
					break;
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

	RebuildInventoryGridPanel();
	UpdateStatPersonScreen();
	BuildInventoryUI(9);
}