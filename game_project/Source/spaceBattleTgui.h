#pragma once

#include "enviroment.h"
#include "UIExtensions.h"

void buildMiniWindowShipStats(int x, int y, Ship * s);
void hideMiniWindowShipStats();

void buildMiniWindowHex(std::wstring name, bool full, float distance, float moveCost, std::wstring text, int x, int y);
void hideMiniWindowHex();