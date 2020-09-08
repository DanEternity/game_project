#pragma once

#include "InventoryHandlers.h"
#include <string>
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
void updateInventoryCell(int id);

// filtered inventory grid

void CreateInventoryGridPanel(int length);
void RebuildInventoryGridPanel();

// applies filter default for current inventory window or gamemode
void ApplyDefaultFilterToInventoryPanel();


void filterSearchFieldChanged(tgui::Widget::Ptr widget, const std::string& signalName);
void filterCategoryFieldChanged(tgui::Widget::Ptr widget, const std::string& signalName);




void createModuleTooltip(Module * m);
void createResourseTooltip(ItemResource * r);
void createEquipmentTooltip(Equipment * e);
void createWeaponModuleTooltip(WeaponModule * w);

void applyStorageTooltip(int id);
void applyGridTooltip(int id);