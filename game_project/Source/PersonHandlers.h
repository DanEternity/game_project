#pragma once

#include "characterManagement.h"
#include "tableInventory.h"
#include "UIExtensions.h"
#include "personEquipmentUI.h"

void personUIElementWasClicked(const int id, tgui::Widget::Ptr widget, const std::string& signalName);
void rmPanelClickedPerson(const int id, tgui::Widget::Ptr widget, const std::string& signalName);
void rmPanelChoosenAddedPerson(const int id, const int module_id, tgui::Widget::Ptr widget, const std::string& signalName);