#pragma once

#include "enviroment.h"
#include "UIExtensions.h"
#include "adventureUI.h"
#include "shopClass.h"

void createShopPanel();
void createShop();
void buildShop(Shop* p, bool rebuild = false);

void ChangeToResources();
void ChangeToModules();
void ChangeToShips();
void ChangeToCrew();

void tradeItems(Goods g, Shop *p);
void buyItem(Goods g, Shop *p);
void sellItem(tgui::Widget::Ptr widget, const std::string& signalName);

void crewClick(int id, Character *c, int price);
void buyCrew();

void applyShopTooltip(Item* i, tgui::Widget::Ptr widget, const std::string& signalName);

void removeShop();