#pragma once

#include <map>
#include <TGUI\TGUI.hpp>
#include <vector>
#include "adventureData.h"
#include "accountData.h"
#include "playerData.h"
#include "uiData.h"
#include "localization.h"
#include "gameLogic.h"
#include "spaceBattleData.h"

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


namespace AdventureUIInventoryStateNamespace
{
	enum AdventureUIInventoryState {
		shipInventory,
		characterInventory,
		storageInventory,
	};
}

class AdventureUIState
{
public:
	bool inventoryOpen = false;
	//AdventureUIInventoryStateNamespace::AdventureUIInventoryState advUIState = AdventureUIInventoryStateNamespace::AdventureUIInventoryState::shipInventory;
};

class AdventureUI
{
public:
	bool isInventoryOpen = false;
	bool isMapOpen = false;
	bool adventureUIUpdateRequired;
	bool adventureUIDrawRequired;
	bool widgetDisable;

	std::vector<tgui::Widget::Ptr> adventureUIWidgets;

	AdventureUIState adventureUIState;
};

struct ScriptLoaderInfo
{
	std::string filename;
	std::wstring familyId;
};

// Loader variables
class ResourseLoader
{
public:

	std::map<std::wstring, ModelDescriptor *>::iterator pointer;

	std::string task = "null";

	std::vector<ScriptLoaderInfo> scriptFilenames;
	int scriptFilenameId;

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
		gameover,
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
	// Does game should update space battle ui
	bool gameSpaceBattleGUIRequiresUpdate = false;
	// WASD controls
	bool gameCanPlayerMoveWASD = false;
	// Can trigger markers
	bool gameCanPlayerTriggerMarkers = false;
	// For space bar based actions
	bool gameSpaceBarPressed = false;

	// Active game mode
	gameMode::GameMode activeGameMode = gameMode::blankMode;

	// Can be used to locate return point if needed
	gameMode::GameMode lastActiveGameMode = gameMode::blankMode;

	// Gamemode flag
	bool endGameFlag = false;

	// gameloader.h section

	ResourseLoader loader;

	//mainmenu section
	MainMenu mainMenu;

	//adventure UI things(inventories)
	AdventureUI adventureUI;

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

	// localization
	LocaleData locale;

	// game logic data
	GameLogicData gameLogic;

	// space battle info
	SpaceBattleData spaceBattle;

	// generation utility

	uint64_t worldSeed = 0;

	uint64_t randTmp = 0;
};

