#pragma once

#include "character.h"
#include "enviroment.h"

// this function cacalculates all ship values based on ship components, crew, states etc

void updateCharacterStats(Character * c);
void clearCharacterStats();
void collectEquipment(Character * c);
void applyCharEquipmentEffects(Character * c, Equipment * m);
void applyCharacterStatEffect(Character * c, StatModEffect * e);