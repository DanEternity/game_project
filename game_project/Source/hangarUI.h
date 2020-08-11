#pragma once

#include "enviroment.h"
#include "UIExtensions.h"

void BuildHangar();
void addShipToHangar(Ship *s);

void placePilotToFighterPanel(int id);
void placePilotToFighter(Character *c, int id, bool isUnassigned);