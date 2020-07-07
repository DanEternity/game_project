#include "Shop.h"

void createShopPanel()
{
	tgui::Panel::Ptr shop = createWidget(WidgetType::Panel, "Panel3", "51%", "92%", "47%", "1%", false)->cast<tgui::Panel>();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(shop, "adventureShop");
}

void buildShop(Shop* p)
{
	gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop")->removeAllWidgets();
	tgui::BitmapButton::Ptr changeButton = createWidget(WidgetType::BitmapButton, "Button", "25%", "8%", "0%", "92%")->cast<tgui::BitmapButton>();
	changeButton->setText("Resources and components");
	changeButton->setTextSize(12);
	changeButton->connect("MouseReleased", ChangeToResources);
	gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop")->add(changeButton);
	changeButton = createWidget(WidgetType::BitmapButton, "Button", "25%", "8%", "25%", "92%")->cast<tgui::BitmapButton>();
	changeButton->setText("Modules and Equipment");
	changeButton->setTextSize(12);
	changeButton->connect("MouseReleased", ChangeToModules);
	gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop")->add(changeButton);
	changeButton = createWidget(WidgetType::BitmapButton, "Button", "25%", "8%", "50%", "92%")->cast<tgui::BitmapButton>();
	changeButton->setText("Ships");
	changeButton->setTextSize(12);
	changeButton->connect("MouseReleased", ChangeToShips);
	gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop")->add(changeButton);
	changeButton = createWidget(WidgetType::BitmapButton, "Button", "25%", "8%", "75%", "92%")->cast<tgui::BitmapButton>();
	changeButton->setText("Crew");
	changeButton->setTextSize(12);
	changeButton->connect("MouseReleased", ChangeToCrew);
	gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop")->add(changeButton);

	gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop")->add(createWidgetLabel("Label", "(&.width - width) / 2", "2%", 28, L"Shop"));
	gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop")->add(createWidgetLabel("Label", "80%", "3%", 18, L"Credits: " + std::to_wstring(gEnv->game.player.money)), "moneyLabel");

	gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop")->add(createWidget(WidgetType::Panel, "Panel2", "99%", "83%", "0.5%", "8%"), "iternalShopResourcesPanel");
	gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop")->add(createWidget(WidgetType::Panel, "Panel2", "99%", "83%", "0.5%", "8%", false), "iternalShopModEquipPanel");
	gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop")->add(createWidget(WidgetType::Panel, "Panel2", "99%", "83%", "0.5%", "8%", false), "iternalShopShipPanel");
	gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop")->add(createWidget(WidgetType::Panel, "Panel2", "99%", "83%", "0.5%", "8%", false), "iternalShopCrewPanel");

	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopResourcesPanel")->add(createWidgetLabel("Label", "3%", "5%", 24, L"Resources: "));
	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopResourcesPanel")->add(createWidgetLabel("Label", "3%", "55%", 24, L"Components: "));
	
	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopModEquipPanel")->add(createWidgetLabel("Label", "3%", "7%", 24, L"Modules: "));
	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopModEquipPanel")->add(createWidgetLabel("Label", "3%", "50%", 24, L"Equipment: "));

	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopResourcesPanel")->add(createWidget(WidgetType::ScrollablePanel, "Panel3", "100%", "35%", "0", "15%"), "shopResources");

	for (int i = 0; i < p->resources.size(); i++)
	{
		int posX = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.03) + (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.4) * i;
		int posY = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().y * 0.15);
		int sizeY = gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.1;
		tgui::BitmapButton::Ptr but = createWidget(WidgetType::BitmapButton, "Button", "10%", std::to_string(sizeY), std::to_string(posX), std::to_string(posY))->cast<tgui::BitmapButton>();
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->add(but, "playerItemButton" + std::to_string(i));
		but->setImage(*p->resources[i].itemPrice->icon);
		but->connect("MouseEntered", applyShopTooltip, &(*p->resources[i].itemPrice));

		int labelPosX = posX + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.12;
		int labelPosY = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().y * 0.15) + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().y * 0.1;
		tgui::BitmapButton::Ptr but2 = createWidget(WidgetType::BitmapButton, "Button", "10%", "15%", std::to_string(labelPosX), std::to_string(labelPosY))->cast<tgui::BitmapButton>();
		but2->setText("<-->");
		but2->setTextSize(18);
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->add(but2, "changeItemResourceButton" + std::to_string(i));
		const int ci = i;
		but2->connect("MouseReleased", tradeItems, ci,  &(*p->resources[i].product), &(*p->resources[i].itemPrice));

		int posX2 = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.27) + (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.4) * i;
		tgui::BitmapButton::Ptr but3 = createWidget(WidgetType::BitmapButton, "Button", "10%", std::to_string(sizeY), std::to_string(posX2), std::to_string(posY))->cast<tgui::BitmapButton>();
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->add(but3, "shopResources" + std::to_string(i));
		but3->setImage(*p->resources[i].product->icon);
		but3->connect("MouseEntered", applyShopTooltip, &(*p->resources[i].product));
		
		float orlabelPosX = posX + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.12 + gEnv->game.adventureGUI.get<tgui::BitmapButton>("changeItemResourceButton" + std::to_string(i))->getSize().x / 4.2;
		float orlabelPosY = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().y * 0.15) + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().y * 0.3;
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->add(createWidgetLabel("Label", std::to_string(orlabelPosX), std::to_string(orlabelPosY), 18, L"OR"));

		float buyButtonPosX = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.03) + (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.4) * i;
		tgui::BitmapButton::Ptr buyButton = createWidget(WidgetType::BitmapButton, "Button", "34%", "20%", std::to_string(buyButtonPosX), "60%")->cast<tgui::BitmapButton>();
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->add(buyButton);
		buyButton->setText("Buy it for " + std::to_string(p->resources[i].creditsPrice) + " credits.");
	}

	updateShipMenuUIState(shipMenu::storage, 1, true);
}

void ChangeToResources()
{
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopModEquipPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopShipPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopCrewPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopResourcesPanel"), true);
}

void ChangeToModules()
{
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopModEquipPanel"), true);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopShipPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopCrewPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopResourcesPanel"), false);
}

void ChangeToShips()
{
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopModEquipPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopShipPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopCrewPanel"), true);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopResourcesPanel"), false);
}

void ChangeToCrew()
{
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopModEquipPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopShipPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopCrewPanel"), true);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopResourcesPanel"), false);
}

void tradeItems(int id, Item* product, Item* price)
{
	int count = 0;
	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{
		if (gEnv->game.player.inventory[i] != NULL)
		{
			if (gEnv->game.player.inventory[i]->itemId == price->itemId)
			{
				count += static_cast<ItemResource*>(gEnv->game.player.inventory[i])->count;
			}
		}
	}
	if (count >= static_cast<ItemResource*>(price)->count)
	{
		int paid = 0;
		for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
		{
			if (gEnv->game.player.inventory[i] != NULL)
			{
				if (gEnv->game.player.inventory[i]->itemId == price->itemId)
				{
					if (paid == static_cast<ItemResource*>(price)->count)
						break;
					if (static_cast<ItemResource*>(price)->count - paid >= static_cast<ItemResource*>(gEnv->game.player.inventory[i])->count)
					{
						paid += static_cast<ItemResource*>(gEnv->game.player.inventory[i])->count;
						gEnv->game.player.inventory[i] = NULL;
					}
					else
					{
						static_cast<ItemResource*>(gEnv->game.player.inventory[i])->count -= static_cast<ItemResource*>(price)->count - paid;
						updateInventoryCell(i);
						break;
					}
				}
			}
		}
		for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
		{
			if (gEnv->game.player.inventory[i] == NULL)
			{
				gEnv->game.player.inventory[i] = product;
				break;
			}
		}
		rebuildAll();
	}
}

void applyShopTooltip(Item* i, tgui::Widget::Ptr widget, const std::string& signalName)
{
	switch (i->itemType)
	{
	case itemType::resource:
		if (!i->tooltipWasCreated)
		{
			createResourseTooltip(static_cast<ItemResource*>(i));
			i->tooltipWasCreated = true;
		}
		widget->setToolTip(i->tooltipDescription);
		tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
		break;
	}
}

void removeShop()
{

}