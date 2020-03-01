#pragma once

#include <TGUI/Gui.hpp>
#include "envUtils.h"
#include "personEquipmentUI.h"
#include "shipModulesUI.h"
#include "tableInventory.h"

void updateAdventureUI();
void disableAllAdventureUIWidgets();
void createAdventureUIButtons();
void adventureUIChangeState(AdventureUIInventoryStateNamespace::AdventureUIInventoryState state);
void adventureUIInventorySpecialButtons(AdventureUIInventoryStateNamespace::AdventureUIInventoryState newState);

void createPauseMenu();