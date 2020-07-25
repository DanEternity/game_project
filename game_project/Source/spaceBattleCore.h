#pragma once

#include "enviroment.h"
#include "spaceBattleTgui.h"
#include "spaceBattleMechanics.h"

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




}