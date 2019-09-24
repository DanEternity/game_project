#pragma once

#include <map>
#include <TGUI\TGUI.hpp>
#include <vector>

class MainMenu
{
public:
	bool menuUpdateRequired;
	bool menuDrawRequired;
	bool widgetDisable;

	std::vector<tgui::Widget::Ptr> mainMenuWidgets;
};

// Loader variables
class ResourseLoader
{
public:

	std::map<std::string, ModelDescriptor *>::iterator pointer;

	std::string task = "null";

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
		mainMenuMode,
		menuOverlay,
	};

} // namespace gameMode

//
// Class contain info about states of game engine
//
class GameData
{
public:

	// system section

	// executable directory
	std::string execDir = "";

	// work directory
	std::string workDir = "";

	bool debug = true;

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

	//mainmenu section
	MainMenu mainMenu;
};

