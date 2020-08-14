#pragma once

#include "enviroment.h"
#include "UIExtensions.h"
#include "tableInventory.h"
#include "RewardsHandlers.h"


void showItemsReward(std::vector<Item*> items);
void applyRewardTooltip(Item *item);
void closeRewardWindow(std::vector<Item*> items);
void finishItemChange();
void deleteRewardItem();