#pragma once

#include <TGUI/Gui.hpp>
#include "envUtils.h"
#include "personEquipmentUI.h"
#include "shipModulesUI.h"
#include "tableInventory.h"
#include "storageStuff.h"
#include "LocaleLoader.h"

void updateAdventureUI();
void disableAllAdventureUIWidgets();
void createAdventureUIButtons();

void updateShipMenuUIState(shipMenu::ShipMenu state, int whereCalled);
void updateCategoryFilters();

void disableAllAdventureUI();

// ui event handlers
void adventureUIChangeState(AdventureUIInventoryStateNamespace::AdventureUIInventoryState state);
void adventureUIInventorySpecialButtons(AdventureUIInventoryStateNamespace::AdventureUIInventoryState newState);

//
void createPauseMenu();
