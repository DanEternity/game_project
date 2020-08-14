#include "RewardsHandlers.h"

void RewardResponseSignal(int cellId, tgui::Widget::Ptr widget, const std::string & signalName)
{
	if (signalName == "MouseReleased")
	{
		if (gEnv->game.player.pickedItem != NULL)
		{
			if (gEnv->game.player.inventory[cellId] != NULL && gEnv->game.player.pickedItem->itemType == itemType::resource
				&& static_cast<ItemResource*>(gEnv->game.player.pickedItem)->count + static_cast<ItemResource*>(gEnv->game.player.inventory[cellId])->count <=
				static_cast<ItemResource*>(gEnv->game.player.pickedItem)->maxCount)
			{
				static_cast<ItemResource*>(gEnv->game.player.inventory[cellId])->count += static_cast<ItemResource*>(gEnv->game.player.pickedItem)->count;
				gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse"));
				gEnv->game.player.pickedItem = NULL;
			}
			else if (gEnv->game.player.inventory[cellId] == NULL)
			{
				gEnv->game.player.inventory[cellId] = gEnv->game.player.pickedItem;
				gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse"));
				widget->cast<tgui::BitmapButton>()->setImage(*gEnv->game.player.inventory[cellId]->icon);
				gEnv->game.player.pickedItem = NULL;
			}
		}
		else
		{
			if (gEnv->game.player.inventory[cellId] != NULL)
			{
				gEnv->game.adventureGUI.add(createWidget(WidgetType::BitmapButton, "Button", std::to_string(45), std::to_string(45), std::to_string(sf::Mouse::getPosition(gEnv->globalWindow).x), std::to_string(sf::Mouse().getPosition(gEnv->globalWindow).y - 5)), "pickedItemMouse");
				gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse")->setImage(*gEnv->game.player.inventory[cellId]->icon);
				gEnv->game.player.pickedItem = gEnv->game.player.inventory[cellId];
				gEnv->game.player.inventory[cellId] = NULL;
				widget->cast<tgui::BitmapButton>()->setImage(NULL);
			}
		}
	}
}

void RewardNewItemsResponseSignal(int cellId, Item* item, tgui::Widget::Ptr widget, const std::string & signalName)
{
	if (gEnv->game.player.pickedItem == NULL && gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("addRewardPanel") != nullptr)
	{
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("rewardPanel")->remove(gEnv->game.adventureGUI.get<tgui::BitmapButton>("rewardItem" + std::to_string(cellId)));
		gEnv->game.adventureGUI.add(createWidget(WidgetType::BitmapButton, "Button", std::to_string(45), std::to_string(45), std::to_string(sf::Mouse::getPosition(gEnv->globalWindow).x), std::to_string(sf::Mouse().getPosition(gEnv->globalWindow).y - 5)), "pickedItemMouse");
		gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse")->setImage(*item->icon);
		gEnv->game.player.pickedItem = item;
	}
}