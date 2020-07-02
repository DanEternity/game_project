#include "InventoryHandlers.h"

void InventoryResponseSignal(int cellId, std::string inventoryId, tgui::Widget::Ptr widget, const std::string & signalName)
{
	if (signalName == "MouseReleased")
	{
		if (gEnv->game.player.pickedItem != NULL)
		{
			swapElements(TargetInventory::tableInventory, cellId);
		}
		else
		{
			if (gEnv->game.player.inventory[cellId] != NULL)
			{
				gEnv->game.adventureGUI.add(createWidget(WidgetType::BitmapButton, "Button", std::to_string(45), std::to_string(45), std::to_string(sf::Mouse::getPosition(gEnv->globalWindow).x), std::to_string(sf::Mouse().getPosition(gEnv->globalWindow).y - 5)), "pickedItemMouse");
				gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse")->setImage(*gEnv->game.player.inventory[cellId]->icon);
				gEnv->game.player.pickedItem = gEnv->game.player.inventory[cellId];
				gEnv->game.player.pickedItemInvId = cellId;
				gEnv->game.player.inventory[cellId] = NULL;
				rebuildAll();
			}
		}
	}
	else if (signalName == "RightMouseReleased" && !gEnv->game.ui.rmWasClicked)
	{
		tgui::Panel::Ptr temp = tgui::Panel::create();
		temp->setSize(100, 90);
		int x = sf::Mouse::getPosition(gEnv->globalWindow).x;
		int y = sf::Mouse::getPosition(gEnv->globalWindow).y - 5;
		temp->setPosition(x, y);
		temp->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
		gEnv->game.adventureGUI.add(temp, "tempRightPanel");
		gEnv->game.ui.rmWasClicked = true;

		const int id = cellId;

		tgui::Button::Ptr btn = tgui::Button::create();

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 0);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Install into");
		btn->connect("MouseReleased", rmPanelClickedInventory, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 30);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Delete");
		btn->connect("MouseReleased", rmPanelClickedInventory, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 60);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Cancel");
		btn->connect("MouseReleased", rmPanelClickedInventory, id);
	}
}

void rmPanelClickedInventory(const int id, tgui::Widget::Ptr widget, const std::string& signalName)
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

	}
	else if (widget->cast<tgui::Button>()->getText() == L"Install into")
	{
		if (gEnv->game.player.inventory[id]->itemType == itemType::module)
		{
			gEnv->game.ui.tempAddPanelClicked = true;
			int goodItemsCount = 0;
			tgui::Button::Ptr btn;
			tgui::Panel::Ptr panel = tgui::Panel::create();
			for (int i(0); i < gEnv->game.player.ship->slots.size(); i++)
			{
				if (static_cast<Module*>(gEnv->game.player.inventory[id])->slot == gEnv->game.player.ship->slots[i].type)
				{
					btn = tgui::Button::create();
					btn->setSize(187, 31);
					btn->setPosition(0, 30 * goodItemsCount);
					btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
					btn->setText(L"Insert instead: " + gEnv->game.player.ship->modules[i]->name);
					const int num = i;
					btn->connect("MouseReleased", rmPanelChoosenInsert, id, num, 0);
					panel->add(btn);
					goodItemsCount++;
				}
			}
			if (goodItemsCount != 0)
			{
				panel->setSize(180, 30 * goodItemsCount);
				auto pos = gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->getPosition();
				pos.x += 100;
				panel->setPosition(pos);
				panel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
				gEnv->game.adventureGUI.add(panel, "tempAddPanel");
			}
			else
				gEnv->game.ui.tempAddPanelClicked = false;
		}
		else if (gEnv->game.player.inventory[id]->itemType == itemType::equipment)
		{
			gEnv->game.ui.tempAddPanelClicked = true;
			int goodItemsCount = 0;
			tgui::Button::Ptr btn;
			tgui::Panel::Ptr panel = tgui::Panel::create();
			for (int i(0); i < gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->slot.size(); i++)
			{
				if (static_cast<Equipment*>(gEnv->game.player.inventory[id])->equipmentSlotType == gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->slot[i])
				{
					btn = tgui::Button::create();
					btn->setSize(187, 31);
					btn->setPosition(0, 30 * goodItemsCount);
					btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
					if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[i] != NULL)
						btn->setText(L"Insert instead: " + gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[i]->name);
					else btn->setText(L"Insert instead: Empty");
					const int num = i;
					btn->connect("MouseReleased", rmPanelChoosenInsert, id, num, 1);
					panel->add(btn);
					goodItemsCount++;
				}
			}
			if (goodItemsCount != 0)
			{
				panel->setSize(180, 30 * goodItemsCount);
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

void rmPanelChoosenInsert(const int id, const int item_id, int inventory, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (inventory == 0)
	{
		gEnv->game.ui.tempAddPanelClicked = true;
		Module* temp = static_cast<Module*>(gEnv->game.player.inventory[id]);

		gEnv->game.player.inventory[id] = gEnv->game.player.ship->modules[item_id];
		gEnv->game.player.ship->modules[item_id] = temp;

		updateShipSchemeUI();
		BuildInventoryUI(9);
		deleteAllInventoryTooltips();

		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
		gEnv->game.ui.rmWasClicked = false;
		gEnv->game.ui.tempAddPanelClicked = false;
	}
	else if (inventory == 1)
	{
		gEnv->game.ui.tempAddPanelClicked = true;
		Equipment* temp = static_cast<Equipment*>(gEnv->game.player.inventory[id]);

		gEnv->game.player.inventory[id] = gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[item_id];
		gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[item_id] = temp;

		tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel");
		tgui::Panel::Ptr panel2 = gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel");

		if (gEnv->game.player.inventory[id] != NULL)
			panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(gEnv->game.player.inventory[id]->name);
		else
			panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(L"");

		if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[item_id] != NULL)
			panel2->get<tgui::Button>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(item_id))->setText(gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[item_id]->name);
		else
			panel2->get<tgui::Button>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(item_id))->setText(L"");

		BuildInventoryUI(9);
		deleteAllInventoryTooltips();

		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
		gEnv->game.ui.rmWasClicked = false;
		gEnv->game.ui.tempAddPanelClicked = false;
	}
}


void InventoryGridPanelEventHandler(const int id, tgui::Widget::Ptr widget, const std::string & signalName)
{
	if (signalName == "MouseReleased")
	{
		// handle left click
		if (gEnv->game.player.pickedItem == NULL)
		{
			if (id < gEnv->game.player.localInventory.size() && gEnv->game.player.localInventory[id] != -1)
				if (gEnv->game.player.inventory[gEnv->game.player.localInventory[id]] != NULL)
				{
					gEnv->game.adventureGUI.add(createWidget(WidgetType::BitmapButton, "Button", std::to_string(45), std::to_string(45), std::to_string(sf::Mouse::getPosition(gEnv->globalWindow).x), std::to_string(sf::Mouse::getPosition(gEnv->globalWindow).y - 5)), "pickedItemMouse");
					gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse")->setImage(*gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->icon);
					gEnv->game.player.pickedItem = gEnv->game.player.inventory[gEnv->game.player.localInventory[id]];
					gEnv->game.player.pickedLocalInventory = id;
					gEnv->game.player.pickedItemInvId = gEnv->game.player.localInventory[id];
					gEnv->game.player.inventory[gEnv->game.player.localInventory[id]] = NULL;
					rebuildAll();
				}
		}
		else
		{
			if (id < gEnv->game.player.localInventory.size() && gEnv->game.player.localInventory[id] != -1)
				if (gEnv->game.player.inventory[gEnv->game.player.localInventory[id]] != NULL)
				{
					swapElements(TargetInventory::gridPanel, id);
					return;
				}
		}
	}
	if (signalName == "RightMouseReleased")
	{

	}

}