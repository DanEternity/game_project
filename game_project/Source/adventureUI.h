#pragma once

#include <TGUI/Gui.hpp>
#include "envUtils.h"
#include "personEquipmentUI.h"
#include "shipModulesUI.h"
#include "tableInventory.h"
#include "storageStuff.h"

void updateAdventureUI();
void disableAllAdventureUIWidgets();
void createAdventureUIButtons();

// ui event handlers
void adventureUIChangeState(AdventureUIInventoryStateNamespace::AdventureUIInventoryState state);
void adventureUIInventorySpecialButtons(AdventureUIInventoryStateNamespace::AdventureUIInventoryState newState);

//
void createPauseMenu();