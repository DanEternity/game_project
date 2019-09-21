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

// Short name for global enviroment 
#define gEnv globalEnviroment

//
// Game enviroment table. Contains all possible game variables. All non-temp variables should be stored here.
//
class GlobalEnviroment
{

// all non-memory management values should be public

public:

	/*                                  */
	/*      SFML variables section      */
	/*                                  */

	sf::RenderWindow globalWindow;
	
	int windowSizeX = 1920;
	int windowSizeY = 1080;

	/*                                  */
	/* game.h primary variables section */
	/*                                  */

	// Does game should check gamemode for draw
	bool gameModesRequiredDraw;
	// Does game should update gamemodes
	bool gameModesRequiredUpdate;
	// Does game should run script system
	bool scriptSystemRequiresUpdate;
	// Does game should update menu (menu will be disabled if FALSE)
	bool menuOverlayRequiresUpdate;
	// Does world generator active
	bool worldGeneratorRequiresUpdate;
};

extern GlobalEnviroment * globalEnviroment;

void initEnviroment();