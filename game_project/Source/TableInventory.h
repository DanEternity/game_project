#pragma once

#include "InventoryHandlers.h"
#include <string>
#include "UITooltipsApply.h"
#include "UITooltipsCreate.h"

void BuildInventoryUI(int cellSize);
void updateInventoryCell(int id);

// filtered inventory grid

void CreateInventoryGridPanel(int length);
void RebuildInventoryGridPanel();

// applies filter default for current inventory window or gamemode
void ApplyDefaultFilterToInventoryPanel();


void filterSearchFieldChanged(tgui::Widget::Ptr widget, const std::string& signalName);
void filterCategoryFieldChanged(tgui::Widget::Ptr widget, const std::string& signalName);
