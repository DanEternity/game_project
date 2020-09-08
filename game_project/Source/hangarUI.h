#pragma once

#include "enviroment.h"
#include "UIExtensions.h"
#include "HangarHandlers.h"

void BuildHangar();
void addShipToHangar(Ship *s);

void placePilotToFighterPanel(int id);
void placePilotToFighter(Character *c, int id, bool isUnassigned);

void buildFigtherModules(int id);
void applyFighterTooltipUI(int fighterId, int moduleId);