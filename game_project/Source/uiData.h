#pragma once

//
// This file contain ui variables
//

#include <string>

namespace PUIState{
	enum personUIstate
	{
		defaultState,
		inventoryState,
		skillTreeState,
		battleAbilitiesState,
	};
}

class UIData
{
public:

	// selected cell id
	int selected = -1;
	bool rmWasClicked = false, tempAddPanelClicked = false;
	bool markerDraw = false;
	int activeOpenPersonWindow = 0;
	int activeOpenFighterWindow = -1;
	bool shiftedItem = false, shiftedItemTakedAll = false;
	int shiftedItemStartId = -1;
	bool adventureMenuActive = false;
	PUIState::personUIstate puistate = PUIState::personUIstate::defaultState;

	float mapBiasX = 0, mapBiasY = 0;
	float mapScale = 8;
	bool mapUpdateRequired = false;

	int sectorNumberRightPanel;

	int characterPlayerCount = 0;

	Character* choosenShopCharacter;
	int choosenShopCharacterPrice;

	tgui::Panel::Ptr tooltipDescription = tgui::Panel::create();

	int spaceBattleHexMiniWindowCount = 0;
	int spaceBattleShipMiniWindowCount = 0;
	int activeWeaponModulesCount = 0;

	std::wstring spaceBattleLogs = L"";
};