#pragma once

#include "enviroment.h"
#include "Item.h"
#include "shipManagement.h"
#include "shipModulesUI.h"
#include "LocaleLoader.h"

void RewardResponseSignal(int cellId, tgui::Widget::Ptr widget, const std::string & signalName);
void RewardNewItemsResponseSignal(int cellId, Item* item, tgui::Widget::Ptr widget, const std::string & signalName);