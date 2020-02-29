#pragma once

#include <TGUI/Gui.hpp>
#include "envUtils.h"

void updateAdventureUI();
void disableAllAdventureUIWidgets();
void createAdventureUIButtons();
void adventureUIChangeState(adventureUIState::AdventureUIInventoryState state);

void createPauseMenu();