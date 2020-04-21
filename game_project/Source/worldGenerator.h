#pragma once

//
// this file contain world generation setup
//
//
//

#include "generationUtility.h"
#include "enviroment.h"
#include "scriptCompiler.h"
#include "map.h"

void startWorldGeneration();

void loadSectorPropertiesDB();

void loadSectorTemplatesDB();

void worldGeneratorUpdate(double deltatime);

void worldGeneratorProcessSector();