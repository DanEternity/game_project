#pragma once

#include "ship.h"

// this function cacalculates all ship values based on ship components, crew, states etc

void updateShipValues(Ship * p);

void clearStats(Ship * p);
void calcModuleStats(Ship * p);
void collectModules(Ship * p);

void applyStatEffect(Ship * p, StatModEffect * e);

