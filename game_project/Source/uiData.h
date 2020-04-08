#pragma once

//
// This file contain ui variables
//

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
	int activeOpenPersonWindow = 0;
	bool adventureMenuActive = false;
	PUIState::personUIstate puistate = PUIState::personUIstate::defaultState;
};