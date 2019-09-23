#pragma once

#include <map>

// Loader variables
class ResourseLoader
{
public:
	std::map<std::string, ModelDescriptor *>::iterator pointer;

};

namespace gameMode 
{

	enum GameMode
	{
		blankMode,
		loadingMode,
		gameGenerationMode,
		adventureMode,
		groundMode,
		spaceBattleMode,
		groundBattleMode,
	};

} // namespace gameMode

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

	// Active game mode
	gameMode::GameMode activeGameMode = gameMode::blankMode;

	// Can be used to locate return point if needed
	gameMode::GameMode lastActiveGameMode = gameMode::blankMode;

	// gameloader.h section

	ResourseLoader loader;

};

