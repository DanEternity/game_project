#pragma once

#include <TGUI/Gui.hpp>
#include "envUtils.h"
#include "personEquipmentUI.h"
#include "shipModulesUI.h"
#include "tableInventory.h"
#include "storageStuff.h"
#include "LocaleLoader.h"
#include "CraftUI.h"
#include "map.h"
#include "UIExtensions.h"
#include "Shop.h"
#include "rewardPanelUI.h"

void updateAdventureUI();
void DrawAdventureUI();
void disableAllAdventureUIWidgets();
void createAdventureUIButtons();

void updateShipMenuUIState(shipMenu::ShipMenu state, int whereCalled, bool openShop = false);
void updateCategoryFilters();


// ui event handlers

//
void createPauseMenu();
void disableAllAdventureUI();

