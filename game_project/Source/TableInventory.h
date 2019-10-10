#pragma once

#include "enviroment.h"

class InventoryItem;
class TableInventory;


class TableInventory
{
public:
	tgui::ScrollablePanel::Ptr scrollablePanel;
	std::vector<InventoryItem*> item;

	TableInventory();
};

class InventoryItem
{
public:
	std::string content;
	tgui::Button::Ptr panel;
	int positionX, positionY;
	int cellsize = 10;

	InventoryItem(int position, TableInventory* inv, std::string content);
};