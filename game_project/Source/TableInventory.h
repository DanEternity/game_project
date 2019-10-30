#pragma once

#include "enviroment.h"

class InventoryItem;
class TableInventory;


class TableInventory
{
public:
	tgui::ScrollablePanel::Ptr scrollablePanel;
	std::vector<InventoryItem*> item;
	bool itemTransfering = false;
	std::string itemWhichTransfer;

	void addItem(std::string obj);
	TableInventory();
};

class InventoryItem
{
public:
	std::string* content;
	tgui::Button::Ptr panelButton;
	int positionX, positionY;
	int cellsize = 10;
	int number;
	InventoryItem(int position, TableInventory* inv, std::string content);
};

void InventoryItemClicked(TableInventory* inv, InventoryItem *item, tgui::Widget::Ptr widget, const std::string& signalName);