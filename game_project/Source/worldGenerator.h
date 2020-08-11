#pragma once

//
// this file contain world generation setup
//
//
//

#include "generationUtility.h"
#include "enviroment.h"
#include "scriptCompiler.h"
#include "adventureUI.h"
#include "map.h"
#include "hangarUI.h"

void startWorldGeneration();

void loadSectorPropertiesDB();

void loadSectorTemplatesDB();

void worldGeneratorUpdate(double deltatime);

void worldGeneratorProcessSector();

bool checkSectorTemplateCompability(MapSector * s, SectorTemplate * t);

void SetupAdventureStart();