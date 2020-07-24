#pragma once

#include "enviroment.h"
#include "spaceBattleTgui.h"

#include <stack>

// Space battle core file

void updateSpaceBattle(double deltaTime);

void drawSpaceBattle(double deltaTime);



// Mechanics and support functions

namespace spaceBattle
{
	std::vector < std::pair<int, int> > getPath(int si, int sj, int fi, int fj);

}