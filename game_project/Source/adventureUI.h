#pragma once

#include <TGUI/Gui.hpp>
#include "envUtils.h"
#include "personEquipmentUI.h"
#include "shipModulesUI.h"
#include "tableInventory.h"
#include "storageStuff.h"
#include "LocaleLoader.h"
#include "CraftUI.h"

void updateAdventureUI();
void DrawAdventureUI();
void disableAllAdventureUIWidgets();
void createAdventureUIButtons();

void updateShipMenuUIState(shipMenu::ShipMenu state, int whereCalled);
void updateCategoryFilters();

void disableAllAdventureUI();

void showItemsReward(std::vector<Item*> items);
void applyRewardTooltip(Item *item);
void closeRewardWindow();

// ui event handlers

//
void createPauseMenu();
