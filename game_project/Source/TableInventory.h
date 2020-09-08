#pragma once

#include "enviroment.h"
#include "Item.h"
#include "shipManagement.h"
#include "shipModulesUI.h"
#include "LocaleLoader.h"
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
void rmPanelChoosenInsert(const int id, const int item_id, int inventory, tgui::Widget::Ptr widget, const std::string& signalName);


// filtered inventory grid

void CreateInventoryGridPanel(int length);
void RebuildInventoryGridPanel();

// applies filter default for current inventory window or gamemode
void ApplyDefaultFilterToInventoryPanel();


void filterSearchFieldChanged(tgui::Widget::Ptr widget, const std::string& signalName);
void filterCategoryFieldChanged(tgui::Widget::Ptr widget, const std::string& signalName);

void InventoryGridPanelEventHandler(const int id, tgui::Widget::Ptr widget, const std::string& signalName);

void applyTooltip(int id);
void createTooltip(Item * m);
void disableTooltips();