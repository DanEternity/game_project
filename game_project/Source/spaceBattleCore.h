#pragma once

#include "enviroment.h"
#include "spaceBattleTgui.h"
#include "spaceBattleMechanics.h"
#include "shipManagement.h"
#include "spaceBattleUI.h"

#include <stack>

// Space battle core file

void updateSpaceBattle(double deltaTime);

void drawSpaceBattle(double deltaTime);





// Mechanics and support functions

namespace spaceBattle
{
	std::vector < std::pair<int, int> > getPath(int si, int sj, int fi, int fj);

	void teleportShip(int si, int sj, int fi, int fj, int shipId);

	int dist2(int x1, int y1, int x2, int y2);

	// this func will return NULL if such module does not exist
	WeaponModule * getShipWeaponModule(Ship * s, int id);

	void initBattle();

	void initAllShips();

	void initShip(Ship * s);

	// Turn starts only for specific faction (example: Player)
	// At the start of the turn all ships of this faction restore shields, energy, weapons etc
	// This command should be executed for all factions in battle in specific order (how they enter battle probably).
	void startTurnUpdate(int factionId);

	void updateShip(Ship * s);

	bool canUseWeapon(Ship * s, WeaponModule * m);

}