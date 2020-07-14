#pragma once

#include "enviroment.h"
#include "Item.h"
#include "shipManagement.h"
#include "shipModulesUI.h"
#include "LocaleLoader.h"

void InventoryResponseSignal(int cellId, std::string inventoryId, tgui::Widget::Ptr widget, const std::string & signalName);
void rmPanelClickedInventory(const int id, tgui::Widget::Ptr widget, const std::string& signalName);
void rmPanelChoosenInsert(const int id, const int item_id, int inventory, tgui::Widget::Ptr widget, const std::string& signalName);

void InventoryGridPanelEventHandler(const int id, tgui::Widget::Ptr widget, const std::string& signalName);