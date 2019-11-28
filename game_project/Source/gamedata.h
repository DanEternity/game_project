#pragma once

#include <map>
#include <TGUI\TGUI.hpp>
#include <vector>
#include "adventureData.h"
#include "accountData.h"
#include "playerData.h"
#include "uiData.h"

namespace menuState
{
	enum MenuState{
		mainMenu,
		exitActive,
		optionsActive,
	};
}

class MainMenu
{
public:
	bool menuUpdateRequired;
	bool menuDrawRequired;
	bool widgetDisable;
	bool sureExit = false;

	std::vector<tgui::Widget::Ptr> mainMenuWidgets;

	menuState::MenuState active = menuState::mainMenu;
};

// Loader variables
class ResourseLoader
{
public:

	std::map<std::wstring, ModelDescriptor *>::iterator pointer;

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

	// envUtil.h section

	int nextExternalTableId = 0;

	// game.h section

	// Does game should check gamemode for draw
	bool gameModesRequiredDraw = false;
	// Does game should update gamemodes
	bool gameModesRequiredUpdate = false;
	// Does game should run script system
	bool scriptSystemRequiresUpdate = false;
	// Does game should update menu (menu will be disabled if FALSE)
	bool menuOverlayRequiresUpdate = false;
	// Does world generator active
	bool worldGeneratorRequiresUpdate = false;
	// Does game should handle globalGui events
	bool globalGUIeventsRequiresUpdate = false;
	// Does game should display adventure
	bool gameAdventureGUIRequiresUpdate = false;
	

	// Active game mode
	gameMode::GameMode activeGameMode = gameMode::blankMode;

	// Can be used to locate return point if needed
	gameMode::GameMode lastActiveGameMode = gameMode::blankMode;

	// gameloader.h section

	ResourseLoader loader;

	//mainmenu section
	MainMenu mainMenu;

	//adventure section
	AdnvetureData adventureData;

	//account data / statistics
	AccountData account;

	//player data / inventory / common player data
	PlayerData player;

	// ui status / variables
	UIData ui;

	// adventureUI
	tgui::Gui adventureGUI;



};

