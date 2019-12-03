#pragma once

#include <TGUI/Gui.hpp>
#include "ShipModulesUI.h"
#include "tableInventory.h"
#include "personEquipmentUI.h"
#include "envUtils.h"
#include "scriptCompiler.h"
#include "worldGenerator.h"
#include <fstream>
#include <sstream>
#include <codecvt>

//This file contains logic for main menu

void updateMainMenu();
void createMenuButtons();
void disableAllMainMenuWidgets();
void mainMenuChangeState();

void startClick();
void exitClick();
void exitButtonsYes();

void testFunctionCreateScript();
void testFunctionExecScript();
void btnNextPressed();