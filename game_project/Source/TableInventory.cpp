#include "tableInventory.h"
/*
void TableInventory::addItem(Item* obj)
{
	int findNext;
	for (findNext = 0; findNext < vecInventoryItem.size(); findNext++)
	{
		if (vecInventoryItem[findNext]->cellItem == nullptr)
		{
			break;
		}
	}
	vecInventoryItem[findNext]->cellItem = obj;
	tgui::Button::Ptr wid;
	wid = vecInventoryItem[findNext]->panelButton;
	wid->setText(obj->name);
}

TableInventory::TableInventory()
{
	scrollablePanel = tgui::ScrollablePanel::create();
	gEnv->game.adventureGUI.add(scrollablePanel, "inventoryPanel");
	scrollablePanel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
	scrollablePanel->setPosition("10%", "60%");
	scrollablePanel->setSize(515, 155);
	for (int i = 0; i < 30; i++)
	{
		InventoryItem * invitem = new InventoryItem(i, this);
		vecInventoryItem.push_back(invitem);
	}
}

InventoryItem::InventoryItem(int position, TableInventory* inv)
{
	positionX = position % cellsize;
	positionY = position / cellsize;
	number = position;
	panelButton = tgui::Button::create();
	inv->scrollablePanel->add(panelButton);
	panelButton->setSize(45, 40);
	panelButton->setPosition(5 + positionX * 50, 10 + positionY * 50);
	panelButton->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	panelButton->setText(L"");
	panelButton->connect("MouseReleased", InventoryItemClicked, &(*inv), &(*this));
}

void InventoryItemClicked(TableInventory * inv, InventoryItem *item, tgui::Widget::Ptr widget, const std::string & signalName)
{
	if (!inv->itemTransfering)
	{
		if (item->cellItem != nullptr)
		{
			inv->itemWhichTransfer = item->cellItem;
			widget->cast<tgui::Button>()->setText(L"");
			item->cellItem = nullptr;
			inv->itemTransfering = true;
		}
	}
	else
	{
		if (item->cellItem == nullptr)
		{
			widget->cast<tgui::Button>()->setText(inv->itemWhichTransfer->name);
			item->cellItem = inv->itemWhichTransfer;
			inv->itemWhichTransfer = nullptr;
			inv->itemTransfering = false;
		}
	}
}*/

void BuildInventoryUI(int cellSize)
{

	tgui::ScrollablePanel::Ptr scrollablePanel = tgui::ScrollablePanel::create();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(scrollablePanel, "inventoryPanel");
	scrollablePanel->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));
	scrollablePanel->setPosition("5%", "15%");
	scrollablePanel->setSize(520, 200);
	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{

		int positionX = i % cellSize;
		int positionY = i / cellSize;
		const int number = i;
		tgui::Button::Ptr button = tgui::Button::create();

		scrollablePanel->add(button, "InventoryCell"+ std::to_string(i));

		button->setSize(45, 40);
		button->setPosition(5 + positionX * 50, 10 + positionY * 50);
		button->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		
		if (gEnv->game.player.inventory[i] != NULL)
			button->setText(gEnv->game.player.inventory[i]->name);
		else
			button->setText(L"");

		button->connect("MouseReleased", IntentoryResponseSignal, number, std::string("ShipInventory"));
		button->connect("RightMouseReleased", IntentoryResponseSignal, number, std::string("ShipInventory"));

		//auto tooltop = tgui::Panel::create();
		//tooltop->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
		//tooltop->setSize(500, 100);
		//tgui::Button::Ptr but = tgui::Button::create();
		//but->setSize(9, 50);
		//but->setPosition(50, 50);
		//but->setText("O");
		//but->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		//tooltop->add(but);
		//button->setToolTip(tooltop);
	}
	scrollablePanel->setEnabled(false);
	scrollablePanel->setVisible(false);
}

void DeleteInventoryUI()
{
}

void IntentoryResponseSignal( int cellId, std::string inventoryId, tgui::Widget::Ptr widget, const std::string & signalName)
{
	if (signalName == "MouseReleased")
	{
		if (gEnv->game.ui.selected != -1)
		{
			// swap

			std::swap(gEnv->game.player.inventory[cellId], gEnv->game.player.inventory[gEnv->game.ui.selected]);


			// update cell images
			tgui::ScrollablePanel::Ptr panel = gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("inventoryPanel");

			if (gEnv->game.player.inventory[cellId] != NULL)
				panel->get<tgui::Button>("InventoryCell" + std::to_string(cellId))->setText(gEnv->game.player.inventory[cellId]->name);
			else
				panel->get<tgui::Button>("InventoryCell" + std::to_string(cellId))->setText(L"");

			if (gEnv->game.player.inventory[gEnv->game.ui.selected] != NULL)
				panel->get<tgui::Button>("InventoryCell" + std::to_string(gEnv->game.ui.selected))->setText(gEnv->game.player.inventory[gEnv->game.ui.selected]->name);
			else
				panel->get<tgui::Button>("InventoryCell" + std::to_string(gEnv->game.ui.selected))->setText(L"");

			gEnv->game.ui.selected = -1;
		}
		else
		{

			if (gEnv->game.player.inventory[cellId] != NULL)
			{
				gEnv->game.ui.selected = cellId;
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

		tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel");
		tgui::Panel::Ptr panel2 = gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel");

		if (gEnv->game.player.inventory[id] != NULL)
			panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(gEnv->game.player.inventory[id]->name);
		else
			panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(L"");

		if (gEnv->game.player.ship->modules[item_id] != NULL)
			panel2->get<tgui::Button>("ShipSchemeModule" + std::to_string(item_id))->setText(gEnv->game.player.ship->modules[item_id]->name);
		else
			panel2->get<tgui::Button>("ShipSchemeModule" + std::to_string(item_id))->setText(L"");

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

		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
		gEnv->game.ui.rmWasClicked = false;
		gEnv->game.ui.tempAddPanelClicked = false;
	}
}

void CreateInventoryGridPanel(int length)
{

	tgui::ScrollablePanel::Ptr scrollablePanel = tgui::ScrollablePanel::create();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->add(scrollablePanel, "inventoryGridPanel");
	scrollablePanel->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));
	scrollablePanel->setPosition("3%", "25%");
	scrollablePanel->setSize(520, 140);


	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{

		int positionX = i % length;
		int positionY = i / length;
		const int number = i;
		tgui::Button::Ptr button = tgui::Button::create();

		scrollablePanel->add(button, "InventoryItem" + std::to_string(i));

		button->setSize(45, 40);
		button->setPosition(5 + positionX * 50, 10 + positionY * 50);
		button->setRenderer(gEnv->globalTheme.getRenderer("Button"));

		button->setText(L"");

		button->connect("MouseReleased", InventoryGridPanelEventHandler, number);
		button->connect("RightMouseReleased", InventoryGridPanelEventHandler, number);

	}

}

void RebuildInventoryGridPanel()
{

	gEnv->game.player.localInventory.clear();

	// apply category filter
	//gEnv->game.player.inventoryFilter.searchString = L"Ebalo";
	//
	for (int id(0); id < gEnv->game.player.inventory.size(); id++)
	{
		if (gEnv->game.player.inventory[id] != NULL)
		{

			// compare to filter
			//

			auto p = gEnv->game.player.inventory[id];

			//if (p->itemType in filter.itemTypes && p->name in filter.nameSeacrh)

			bool filter_ok = true;
			IntventoryFilter* filter = &gEnv->game.player.inventoryFilter;
			
			if (filter->searchString != L"")
			{
				if (p->name.find(filter->searchString) == std::wstring::npos)
				{
					filter_ok = false;
				}
			}

			if (filter->itemType.size() > 0)
			{
				if (filter->itemType.find(p->itemType) == filter->itemType.end())
				{
					filter_ok = false;
				}
			}

			if (p->itemType == itemType::module)
			{
				if (filter->moduleSlotType.size() > 0)
				{
					if (filter->moduleSlotType.find(static_cast<Module*>(p)->slot) == filter->moduleSlotType.end())
					{
						filter_ok = false;
					}
				}
			}

			if (p->itemType == itemType::equipment)
			{
				if (filter->equipmentType.size() > 0)
				{
					if (filter->equipmentType.find(static_cast<Equipment*>(p)->equipmentType) == filter->equipmentType.end())
					{
						filter_ok = false;
					}
				}
			}

			if (!filter_ok)
				continue;
			gEnv->game.player.localInventory.push_back(id);

		}
	}

	for (int id(0); id < gEnv->game.player.inventory.size(); id++)
	{	
		if (id < gEnv->game.player.localInventory.size() && gEnv->game.player.localInventory[id] != -1)
			gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(id))->
			setText(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->name);
		else
			gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(id))->
			setText(L"");
	}


}

void ApplyDefaultFilterToInventoryPanel()
{

	// current menu
	auto q = gEnv->game.player.shipMenu;
	
	if (q == shipMenu::ship)
	{
		gEnv->game.player.inventoryFilter.itemType.insert(itemType::module);
	}

	if (q == shipMenu::crew)
	{
		gEnv->game.player.inventoryFilter.itemType.insert(itemType::equipment);
	}

}

void filterSearchFieldChanged(tgui::Widget::Ptr widget, const std::string & signalName)
{

	gEnv->game.player.inventoryFilter.searchString = widget->cast<tgui::EditBox>()->getText();

	RebuildInventoryGridPanel();

}

void filterCategoryFieldChanged(tgui::Widget::Ptr widget, const std::string & signalName)
{

	auto p = widget->cast<tgui::ComboBox>();
	std::wstring s = p->getSelectedItem();
	wprintf(L"Filter set: %s \n", s.c_str());

	gEnv->game.player.inventoryFilter.itemType.clear();
	gEnv->game.player.inventoryFilter.equipmentType.clear();
	gEnv->game.player.inventoryFilter.moduleSlotType.clear();

	//if (s == L"Equipment")
	//{
	//	gEnv->game.player.inventoryFilter.itemType.insert(itemType::equipment);
	//}

	//if (s == L"Modules")
	//{
	//	gEnv->game.player.inventoryFilter.itemType.insert(itemType::module);
	//}

	if (s == L"Engine")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::engine);
	}

	if (s == L"Hyperdrive")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::hyperdrive);
	}

	if (s == L"No filter")
	{
		// no filter
	}

	// currently do nothing because not all windows are completed
	ApplyDefaultFilterToInventoryPanel();

	RebuildInventoryGridPanel();

}

void InventoryGridPanelEventHandler(const int id, tgui::Widget::Ptr widget, const std::string & signalName)
{
	if (signalName == "MouseReleased")
	{
		// handle left click
		if (gEnv->game.player.pickedItem == NULL)
		{
			if ( id < gEnv->game.player.localInventory.size() && gEnv->game.player.localInventory[id] != -1)
				if (gEnv->game.player.inventory[gEnv->game.player.localInventory[id]] != NULL)
				{
					gEnv->game.player.pickedItem = gEnv->game.player.inventory[gEnv->game.player.localInventory[id]];
					gEnv->game.player.pickedLocalInventory = id;
					gEnv->game.player.pickedItemInvId = gEnv->game.player.localInventory[id];
					return;
				}
		}
		else
		{
			// swap items if can
			if (id < gEnv->game.player.localInventory.size() && gEnv->game.player.localInventory[id] != -1)
				if (gEnv->game.player.inventory[gEnv->game.player.localInventory[id]] != NULL)
				{

					std::swap(
						gEnv->game.player.inventory[gEnv->game.player.localInventory[id]], 
						gEnv->game.player.inventory[gEnv->game.player.localInventory[gEnv->game.player.pickedLocalInventory]]);

					gEnv->game.player.pickedLocalInventory = -1;
					gEnv->game.player.pickedItem = NULL;
					RebuildInventoryGridPanel();
					return;

				}
		}
	}

	if (signalName == "RightMouseReleased")
	{
		// handle right click
		
	}

}
