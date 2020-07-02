#pragma once

#include "enviroment.h"
#include "item.h"
#include "tableInventory.h"
#include "itemUtils.h"
#include "UIExtensions.h"

void handleShipModulesPanelEvent(const int id, tgui::Widget::Ptr widget, const std::string& signalName);
void rmPanelClickedShip(const int id, tgui::Widget::Ptr widget, const std::string& signalName);
void rmPanelChoosenAdded(const int id, const int module_id, tgui::Widget::Ptr widget, const std::string& signalName);