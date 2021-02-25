#pragma once


#include "ShipHandlers.h"
#include "UITooltipsApply.h"
#include "UITooltipsCreate.h"

void BuildShipSchemeUI(int moduleSizeUI = 45);


// handlers


//stats field
void buildShipStats();
void updateShipSchemeUI();

void createShipModulePriorityPanel(Ship *s);
void changeShipModulePriority(int id, bool isUp, Ship *s);