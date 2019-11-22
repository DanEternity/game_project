#pragma once

#include "enviroment.h"
#include "Item.h"
/*
class InventoryItem;
class TableInventory;


class TableInventory
{
public:
	tgui::ScrollablePanel::Ptr scrollablePanel;
	std::vector<InventoryItem*> vecInventoryItem;
	bool itemTransfering = false;
	Item* itemWhichTransfer;

	void addItem(Item* obj);
	TableInventory();
};

class InventoryItem
{
public:
	Item* cellItem;
	tgui::Button::Ptr panelButton;
	int positionX, positionY;
	int cellsize = 10;
	int number;
	InventoryItem(int position, TableInventory* inv);
};

void InventoryItemClicked(TableInventory* inv, InventoryItem *item, tgui::Widget::Ptr widget, const std::string& signalName);
*/


void BuildInventoryUI(int cellSize);
void DeleteInventoryUI();
void IntentoryResponseSignal(int cellId, std::string inventoryId, tgui::Widget::Ptr widget, const std::string & signalName);
void rmPanelClickedInventory(const int id, tgui::Widget::Ptr widget, const std::string& signalName);
void rmPanelChoosenInsert(const int id, const int module_id, tgui::Widget::Ptr widget, const std::string& signalName);