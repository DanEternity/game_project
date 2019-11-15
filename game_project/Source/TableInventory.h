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
	std::wstring itemWhichTransfer;

	void addItem(std::wstring obj);
	TableInventory();
};

class InventoryItem
{
public:
	std::wstring* content;
	tgui::Button::Ptr panelButton;
	int positionX, positionY;
	int cellsize = 10;
	int number;
	InventoryItem(int position, TableInventory* inv, std::wstring content);
};

void InventoryItemClicked(TableInventory* inv, InventoryItem *item, tgui::Widget::Ptr widget, const std::string& signalName);