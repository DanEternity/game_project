#pragma once

#include <map>

// Loader variables
class ResourseLoader
{
public:
	std::map<std::string, ModelDescriptor *>::iterator pointer;

};

//
// Class contain info about states of game engine
//
class GameData
{
public:

	// system section

	std::string execDir = "";

	// game.h section

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

	// gameloader.h section

	ResourseLoader loader;

};

