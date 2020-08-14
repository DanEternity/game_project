#include "rewardPanelUI.h"

void showItemsReward(std::vector<Item*> items)
{
	gEnv->game.adventureGUI.add(createWidget(WidgetType::ScrollablePanel, "Panel", "45%", "30%", "(&.width - width) / 2", "15%"), "rewardPanel");

	int i = 0;
	for (auto item : items)
	{
		tgui::BitmapButton::Ptr button = createWidget(WidgetType::BitmapButton, "Button", "50", "50", std::to_string(10 + i % 10 * 60), std::to_string(10 + i / 10 * 60))->cast<tgui::BitmapButton>();
		button->setImage(*item->icon);
		gEnv->game.adventureGUI.get<tgui::Panel>("rewardPanel")->add(button, "rewardItem" + std::to_string(i));
		button->setToolTip(gEnv->game.ui.tooltipDescription);
		const int id = i;
		button->connect("MouseReleased", RewardNewItemsResponseSignal, id, &(*item));
		button->connect("MouseEntered", applyRewardTooltip, &(*item));
		i++;
	}

	tgui::BitmapButton::Ptr exit = createWidget(WidgetType::BitmapButton, "Button", "200", "50", "70%", "80%")->cast<tgui::BitmapButton>();
	exit->connect("MouseReleased", closeRewardWindow, items);
	exit->setText("Take reward");
	gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("rewardPanel")->add(exit, "exitRewardWindow");
}

void closeRewardWindow(std::vector<Item*> items)
{
	gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("rewardPanel")->remove(gEnv->game.adventureGUI.get<tgui::BitmapButton>("exitRewardWindow"));
	int emptyCount = 0;
	std::vector<int> indexes;
	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{
		if (gEnv->game.player.inventory[i] == NULL)
		{
			emptyCount++;
			indexes.push_back(i);
		}
	}
	if (emptyCount > items.size())
	{
		for (int i = 0; i < items.size(); i++)
		{
			gEnv->game.player.inventory[indexes[i]] = items[i];
		}

		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("rewardPanel")->removeAllWidgets();
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("rewardPanel"));
	}
	else
	{
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::BitmapButton>("exitRewardWindow"));
		gEnv->game.adventureGUI.add(createWidget(WidgetType::ScrollablePanel, "Panel", "45%", "32%", "(&.width - width) / 2", "50%"), "addRewardPanel");

		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("addRewardPanel")->add(createWidgetLabel("Label", "10", "10", 18, L"There is not enough space in your inventory. Transfer the items you want to keep."));

		for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
		{
			tgui::BitmapButton::Ptr button = createWidget(WidgetType::BitmapButton, "Button", "50", "50", std::to_string(10 + i % 14 * 60), std::to_string(40 + i / 14 * 60))->cast<tgui::BitmapButton>();
			gEnv->game.adventureGUI.get<tgui::Panel>("addRewardPanel")->add(button, "inventoryItemReward" + std::to_string(i));

			if (gEnv->game.player.inventory[i] != NULL)
			{
				if (gEnv->game.player.inventory[i]->icon != nullptr)
					button->setImage(*gEnv->game.player.inventory[i]->icon);
				else button->setImage(gEnv->modelDB[L"itemDefault"]->tex);
			}
			else button->setImage(gEnv->modelDB[L"itemEmpty"]->tex);

			button->setToolTip(gEnv->game.ui.tooltipDescription);

			const int id = i;
			button->connect("MouseEntered", applyStorageTooltip, id);
			button->connect("MouseReleased", RewardResponseSignal, id);
		}

		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("addRewardPanel")->add(createWidget(WidgetType::BitmapButton, "Button", "50", "50", "10", "100% - height - 10"), "deleteRewardItem");
		gEnv->game.adventureGUI.get<tgui::BitmapButton>("deleteRewardItem")->connect("MouseReleased", deleteRewardItem);
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("addRewardPanel")->add(createWidgetLabel("Label", "75", "88%", 18, L"Place the items here that you want to delete."));
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("addRewardPanel")->add(createWidget(WidgetType::BitmapButton, "Button", "200", "50", "75%", "100% - height - 20"), "finishReward");
		gEnv->game.adventureGUI.get<tgui::BitmapButton>("finishReward")->setText("Finish");
		gEnv->game.adventureGUI.get<tgui::BitmapButton>("finishReward")->connect("MouseReleased", finishItemChange);
	}
}

void finishItemChange()
{
	gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("rewardPanel")->removeAllWidgets();
	gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("rewardPanel"));

	gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("addRewardPanel")->removeAllWidgets();
	gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("addRewardPanel"));
}

void applyRewardTooltip(Item *item)
{
	if (item != NULL)
	{
		switch (item->itemType)
		{
		case itemType::module:
			createModuleTooltip(static_cast<Module*>(item));
		case itemType::resource:
			createResourseTooltip(static_cast<ItemResource*>(item));
		}
		gEnv->game.ui.tooltipDescription->setVisible(true);
	}
	else gEnv->game.ui.tooltipDescription->setVisible(false);
	tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
}

void deleteRewardItem()
{
	if (gEnv->game.player.pickedItem != NULL)
	{
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse"));
		gEnv->game.player.pickedItem = NULL;
	}
}