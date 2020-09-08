#pragma once

#include "ship.h"
#include "enviroment.h"

// this function cacalculates all ship values based on ship components, crew, states etc

void updateShipValues(Ship * p);

void clearStats(Ship * p);
void calcModuleStats(Ship * p);
void collectModules(Ship * p);

void applySysModuleEffects(Ship * p, Module * m);
void applyStatEffect(Ship * p, StatModEffect * e);
bool checkRequirements(Ship * p, Module * m);
