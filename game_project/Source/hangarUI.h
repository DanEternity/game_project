#pragma once

#include "enviroment.h"
#include "UIExtensions.h"
#include "HangarHandlers.h"
#include "UITooltipsApply.h"
#include "UITooltipsCreate.h"

void BuildHangar();
void addShipToHangar(Ship *s);

void placePilotToFighterPanel(int id);
void placePilotToFighter(Character *c, int id, bool isUnassigned);

void buildFigtherModules(int id);