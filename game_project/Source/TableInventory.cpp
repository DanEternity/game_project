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
	gEnv->globalGui.add(scrollablePanel, "inventoryPanel");
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
	gEnv->globalGui.add(scrollablePanel, "inventoryPanel");
	scrollablePanel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
	scrollablePanel->setPosition("10%", "70%");
	scrollablePanel->setSize(515, 155);
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

	}

}

void DeleteInventoryUI()
{
}

void IntentoryResponseSignal( int cellId, std::string inventoryId, tgui::Widget::Ptr widget, const std::string & signalName)
{
	
	if (gEnv->game.ui.selected != -1)
	{
		// swap

		std::swap(gEnv->game.player.inventory[cellId], gEnv->game.player.inventory[gEnv->game.ui.selected]);
		

		// update cell images
		tgui::ScrollablePanel::Ptr panel = gEnv->globalGui.get<tgui::ScrollablePanel>("inventoryPanel");

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
