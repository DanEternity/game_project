#pragma once

#include "enviroment.h"
#include "UIExtensions.h"
#include "adventureUI.h"
#include "shopClass.h"

void createShopPanel();
void buildShop(Shop* p);

void ChangeToResources();
void ChangeToModules();
void ChangeToShips();
void ChangeToCrew();

void tradeItems(int id, Item* product, Item* price);
void applyShopTooltip(Item* i, tgui::Widget::Ptr widget, const std::string& signalName);

void removeShop();