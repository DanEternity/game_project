#pragma once

/* This file contain all game enviroment variables and table */
/* It's possible to access structures only through this file */

/* HINT: Includes only data/util headers. Any game logic processing */
/* structures can break system hierarhy, make it impossible to      */
/* compile.                                                         */

/* Non-game includes */
#include <SFML/Graphics.hpp>
#include <TGUI/tGui.hpp>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

/* Game data includes */
// #include "character.h"
// #include "ship.h"
#include "scriptDescriptor.h"
#include "graphicsModel.h"
#include "gamedata.h"
#include "graphics.h"
#include "menuData.h"
#include "valueObjects.h"
#include "scriptSystemData.h"

// Short name for global enviroment 
#define gEnv globalEnviroment

// Debug variable short name
#define debugMode globalEnviroment->game.debug

//
// Game enviroment table. Contains all possible game variables. All non-temp variables should be stored here.
//
class GlobalEnviroment
{

// all non-memory management values should be public

public:

	// SFML window descriptor. Used to manipulate window params and draw objects
	sf::RenderWindow globalWindow;

	// TGUI descriptor
	tgui::Gui globalGui;

	// TGUI theme 
	tgui::Theme globalTheme;

	// Graphical settings and values
	Graphics graphics;

	// Contain info about states of game engine
	GameData game;

	// Contains menu data and menu related states
	MenuData menuData;

	// Contains graphical models (2d textures)
	std::map<std::string, ModelDescriptor *> modelDB;

	// Contains external tables
	std::map<std::string, ExternalTable*> extTables;

	// Script system data
	ScriptSystemData scripts;
};

extern GlobalEnviroment * globalEnviroment;

void initEnviroment();