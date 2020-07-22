#include "Shop.h"

void createShopPanel()
{
	tgui::Panel::Ptr shop = createWidget(WidgetType::Panel, "Panel3", "51%", "98%", "47%", "1%", false)->cast<tgui::Panel>();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(shop, "adventureShop");
}

void createShop()
{
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

	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopResourcesPanel")->add(createWidgetLabel("Label", "2%", "0.2%", 24, L"Resources: "));
	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopResourcesPanel")->add(createWidgetLabel("Label", "2%", "43%", 24, L"Components: "));

	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopModEquipPanel")->add(createWidgetLabel("Label", "2%", "0.2%", 24, L"Modules: "));
	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopModEquipPanel")->add(createWidgetLabel("Label", "2%", "43%", 24, L"Equipment: "));

	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopResourcesPanel")->add(createWidget(WidgetType::ScrollablePanel, "ScrollablePanel", "100%", "35%", "0", "7%"), "shopResources");
	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopModEquipPanel")->add(createWidget(WidgetType::ScrollablePanel, "ScrollablePanel", "100%", "35%", "0", "7%"), "shopModules");
	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopModEquipPanel")->add(createWidget(WidgetType::ScrollablePanel, "ScrollablePanel", "100%", "35%", "0", "51%"), "shopEquipments");
	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopCrewPanel")->add(createWidget(WidgetType::ScrollablePanel, "Panel", "100%", "40%", "0", "0%"), "shopCharacters");
	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopCrewPanel")->add(createWidget(WidgetType::ScrollablePanel, "ScrollablePanel", "100%", "60%", "0", "40%"), "shopCharacterStats");

	tgui::BitmapButton::Ptr crewbut = createWidget(WidgetType::BitmapButton, "Button", "30%", "5%", "(&.width - width) / 2", "86%", false)->cast<tgui::BitmapButton>();
	gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopCrewPanel")->add(crewbut, "buyCharacterButton");
	crewbut->setText(L"Buy this character");
	crewbut->connect("MouseReleased", buyCrew);

	tgui::Button::Ptr sellButton = createWidget(WidgetType::Button, "Button", "7%", "&.width * 0.07", "2%", "83%")->cast<tgui::Button>();
	gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop")->add(sellButton);
	sellButton->connect("MouseEntered", sellItem);
	sellButton->connect("MouseReleased", sellItem);
	sellButton->connect("MouseLeft", sellItem);
	gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop")->add(createWidgetLabel("Label", "10%", "85%", 18, L"Place cursor with item to the box to see item price"), "sellItemLabel");
}

void buildShop(Shop* p, bool rebuild)
{
	//resource panel
	std::string shopNumber = "0";
	if (gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopResourcesPanel")->isVisible())
	{
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->removeAllWidgets();
		for (int i = 0; i < p->resources.size(); i++)
		{
			if (p->resources[i].itemPrice == NULL && p->resources[i].creditsPrice == 0) continue;
			int posX = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.03) + (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.4) * i;
			int posY = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().y * 0.15);
			int sizeY = gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.1;
			if (p->resources[i].itemPrice != NULL)
			{
				tgui::BitmapButton::Ptr but = createWidget(WidgetType::BitmapButton, "Button", "10%", std::to_string(sizeY), std::to_string(posX), std::to_string(posY))->cast<tgui::BitmapButton>();
				gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->add(but, "playerItemButton" + std::to_string(i) + shopNumber);
				if (p->resources[i].itemPrice->icon == NULL) giveIconToItem(p->resources[i].itemPrice);
				but->setImage(*p->resources[i].itemPrice->icon);
				but->connect("MouseEntered", applyShopTooltip, &(*p->resources[i].itemPrice));

				int labelPosX = posX + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.12;
				int labelPosY = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().y * 0.15) + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().y * 0.1;
				tgui::BitmapButton::Ptr but2 = createWidget(WidgetType::BitmapButton, "Button", "10%", "15%", std::to_string(labelPosX), std::to_string(labelPosY))->cast<tgui::BitmapButton>();
				but2->setText("<-->");
				but2->setTextSize(18);
				gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->add(but2, "changeItemResourceButton" + std::to_string(i) + shopNumber);
				const int ci = i;
				but2->connect("MouseReleased", tradeItems, p->resources[i], &(*p));
			}

			int posX2 = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.27) + (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.4) * i;
			tgui::BitmapButton::Ptr but3 = createWidget(WidgetType::BitmapButton, "Button", "10%", std::to_string(sizeY), std::to_string(posX2), std::to_string(posY))->cast<tgui::BitmapButton>();
			gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->add(but3, "shopResourceButton" + std::to_string(i) + shopNumber);
			if (p->resources[i].product->icon == NULL) giveIconToItem(p->resources[i].product);
			but3->setImage(*p->resources[i].product->icon);
			but3->connect("MouseEntered", applyShopTooltip, &(*p->resources[i].product));

			if (p->resources[i].itemPrice != NULL && p->resources[i].creditsPrice != 0)
			{
				float orlabelPosX = posX + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.12 + gEnv->game.adventureGUI.get<tgui::BitmapButton>("changeItemResourceButton" + std::to_string(i) + shopNumber)->getSize().x / 4.2;
				float orlabelPosY = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().y * 0.15) + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().y * 0.3;
				gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->add(createWidgetLabel("Label", std::to_string(orlabelPosX), std::to_string(orlabelPosY), 18, L"OR"), "shopOrLabel" + std::to_string(i) + shopNumber);
			}
			if (p->resources[i].creditsPrice != 0)
			{
				float buyButtonPosX = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.03) + (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.4) * i;
				tgui::BitmapButton::Ptr buyButton = createWidget(WidgetType::BitmapButton, "Button", "34%", "20%", std::to_string(buyButtonPosX), "60%")->cast<tgui::BitmapButton>();
				gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->add(buyButton, "buyCreditsButton" + std::to_string(i) + shopNumber);
				buyButton->setText("Buy it for " + std::to_string(p->resources[i].creditsPrice) + " credits.");
				buyButton->connect("MouseReleased", buyItem, p->resources[i], &(*p));
			}
		}
	}

	if (gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopModEquipPanel")->isVisible())
	{
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->removeAllWidgets();
		//modules panel
		shopNumber = "1";
		for (int i = 0; i < p->modules.size(); i++)
		{
			if (p->modules[i].itemPrice == NULL && p->modules[i].creditsPrice == 0) continue;
			int posX = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->getSize().x * 0.03) + (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.4) * i;
			int posY = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->getSize().y * 0.15);
			int sizeY = gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->getSize().x * 0.1;
			if (p->modules[i].itemPrice != NULL)
			{
				tgui::BitmapButton::Ptr but = createWidget(WidgetType::BitmapButton, "Button", "10%", std::to_string(sizeY), std::to_string(posX), std::to_string(posY))->cast<tgui::BitmapButton>();
				gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->add(but, "playerItemButton" + std::to_string(i) + shopNumber);
				if (p->modules[i].itemPrice->icon == NULL) giveIconToItem(p->modules[i].itemPrice);
				but->setImage(*p->modules[i].itemPrice->icon);
				but->connect("MouseEntered", applyShopTooltip, &(*p->modules[i].itemPrice));


				int labelPosX = posX + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->getSize().x * 0.12;
				int labelPosY = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->getSize().y * 0.15) + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->getSize().y * 0.1;
				tgui::BitmapButton::Ptr but2 = createWidget(WidgetType::BitmapButton, "Button", "10%", "15%", std::to_string(labelPosX), std::to_string(labelPosY))->cast<tgui::BitmapButton>();
				but2->setText("<-->");
				but2->setTextSize(18);
				gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->add(but2, "changeItemResourceButton" + std::to_string(i) + shopNumber);
				const int ci = i;
				but2->connect("MouseReleased", tradeItems, p->modules[i], &(*p));
			}

			int posX2 = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->getSize().x * 0.27) + (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->getSize().x * 0.4) * i;
			tgui::BitmapButton::Ptr but3 = createWidget(WidgetType::BitmapButton, "Button", "10%", std::to_string(sizeY), std::to_string(posX2), std::to_string(posY))->cast<tgui::BitmapButton>();
			gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->add(but3, "shopResourceButton" + std::to_string(i) + shopNumber);
			if (p->modules[i].product->icon == NULL) giveIconToItem(p->modules[i].product);
			but3->setImage(*p->modules[i].product->icon);
			but3->connect("MouseEntered", applyShopTooltip, &(*p->modules[i].product));

			if (p->modules[i].itemPrice != NULL && p->modules[i].creditsPrice != 0)
			{
				float orlabelPosX = posX + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->getSize().x * 0.12 + gEnv->game.adventureGUI.get<tgui::BitmapButton>("changeItemResourceButton" + std::to_string(i) + shopNumber)->getSize().x / 4.2;
				float orlabelPosY = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->getSize().y * 0.15) + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->getSize().y * 0.3;
				gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->add(createWidgetLabel("Label", std::to_string(orlabelPosX), std::to_string(orlabelPosY), 18, L"OR"), "shopOrLabel" + std::to_string(i) + shopNumber);
			}

			if (p->modules[i].creditsPrice != 0)
			{
				float buyButtonPosX = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->getSize().x * 0.03) + (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->getSize().x * 0.4) * i;
				tgui::BitmapButton::Ptr buyButton = createWidget(WidgetType::BitmapButton, "Button", "34%", "20%", std::to_string(buyButtonPosX), "60%")->cast<tgui::BitmapButton>();
				gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopModules")->add(buyButton, "buyCreditsButton" + std::to_string(i) + shopNumber);
				buyButton->setText("Buy it for " + std::to_string(p->modules[i].creditsPrice) + " credits.");
				buyButton->connect("MouseReleased", buyItem, p->modules[i], &(*p));
			}
		}
	}

	if (gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopModEquipPanel")->isVisible())
	{
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->removeAllWidgets();
		//equipment panel
		shopNumber = "2";
		for (int i = 0; i < p->equipments.size(); i++)
		{
			if (p->equipments[i].itemPrice == NULL && p->equipments[i].creditsPrice == 0) continue;
			int posX = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->getSize().x * 0.03) + (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopResources")->getSize().x * 0.4) * i;
			int posY = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->getSize().y * 0.15);
			int sizeY = gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->getSize().x * 0.1;
			if (p->equipments[i].itemPrice != NULL)
			{
				tgui::BitmapButton::Ptr but = createWidget(WidgetType::BitmapButton, "Button", "10%", std::to_string(sizeY), std::to_string(posX), std::to_string(posY))->cast<tgui::BitmapButton>();
				gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->add(but, "playerItemButton" + std::to_string(i) + shopNumber);
				if (p->equipments[i].itemPrice->icon == NULL) giveIconToItem(p->equipments[i].itemPrice);
				but->setImage(*p->equipments[i].itemPrice->icon);
				but->connect("MouseEntered", applyShopTooltip, &(*p->equipments[i].itemPrice));

				int labelPosX = posX + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->getSize().x * 0.12;
				int labelPosY = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->getSize().y * 0.15) + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->getSize().y * 0.1;
				tgui::BitmapButton::Ptr but2 = createWidget(WidgetType::BitmapButton, "Button", "10%", "15%", std::to_string(labelPosX), std::to_string(labelPosY))->cast<tgui::BitmapButton>();
				but2->setText("<-->");
				but2->setTextSize(18);
				gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->add(but2, "changeItemResourceButton" + std::to_string(i) + shopNumber);
				const int ci = i;
				but2->connect("MouseReleased", tradeItems, p->equipments[i], &(*p));
			}

			int posX2 = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->getSize().x * 0.27) + (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->getSize().x * 0.4) * i;
			tgui::BitmapButton::Ptr but3 = createWidget(WidgetType::BitmapButton, "Button", "10%", std::to_string(sizeY), std::to_string(posX2), std::to_string(posY))->cast<tgui::BitmapButton>();
			gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->add(but3, "shopResourceButton" + std::to_string(i) + shopNumber);
			if (p->equipments[i].product->icon == NULL) giveIconToItem(p->equipments[i].product);
			but3->setImage(*p->equipments[i].product->icon);
			but3->connect("MouseEntered", applyShopTooltip, &(*p->equipments[i].product));

			if (p->equipments[i].itemPrice != NULL && p->equipments[i].creditsPrice != 0)
			{
				float orlabelPosX = posX + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->getSize().x * 0.12 + gEnv->game.adventureGUI.get<tgui::BitmapButton>("changeItemResourceButton" + std::to_string(i) + shopNumber)->getSize().x / 4.2;
				float orlabelPosY = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->getSize().y * 0.15) + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->getSize().y * 0.3;
				gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->add(createWidgetLabel("Label", std::to_string(orlabelPosX), std::to_string(orlabelPosY), 18, L"OR"), "shopOrLabel" + std::to_string(i) + shopNumber);
			}

			if (p->equipments[i].creditsPrice != 0)
			{
				float buyButtonPosX = (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->getSize().x * 0.03) + (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->getSize().x * 0.4) * i;
				tgui::BitmapButton::Ptr buyButton = createWidget(WidgetType::BitmapButton, "Button", "34%", "20%", std::to_string(buyButtonPosX), "60%")->cast<tgui::BitmapButton>();
				gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopEquipments")->add(buyButton, "buyCreditsButton" + std::to_string(i) + shopNumber);
				buyButton->setText("Buy it for " + std::to_string(p->equipments[i].creditsPrice) + " credits.");
				buyButton->connect("MouseReleased", buyItem, p->equipments[i], &(*p));
			}
		}
	}

	if (gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopCrewPanel")->isVisible())
	{
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopCharacters")->removeAllWidgets();
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopCharacterStats")->removeAllWidgets();
		//crew panel
		for (int i = 0; i < p->characters.size(); i++)
		{
			int posX = gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopCharacters")->getSize().x * 0.2 * i;
			tgui::BitmapButton::Ptr but = createWidget(WidgetType::BitmapButton, "Button", "20%", "100%", std::to_string(posX), "0")->cast<tgui::BitmapButton>();
			but->setText(p->characters[i].first->name);
			gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopCharacters")->add(but);
			but->connect("MouseReleased", crewClick, i, &(*p->characters[i].first), p->characters[i].second);

			std::wstring itemsString = L"Items: ";
			bool flag = false;
			for (int j = 0; j < p->characters[i].first->equipment.size(); j++) if (p->characters[i].first->equipment[j] != NULL) flag = true;
			if (!flag) itemsString += L"Character dont have equipment";

			tgui::Label::Ptr itemsLab = createWidgetLabel("Label", "1%", "4%", 20, itemsString);
			enableWidget(itemsLab, false);
			gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopCharacterStats")->add(itemsLab, "charItemsLab" + std::to_string(i));

			for (int j = 0, k = 0; j < p->characters[i].first->equipment.size(); j++)
			{
				if (p->characters[i].first->equipment[j] != NULL)
				{
					int butPosX = 20 + gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopCharacterStats")->getSize().x * 0.1 * ++k;
					int sizeY = gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopCharacterStats")->getSize().x * 0.08;
					tgui::BitmapButton::Ptr but2 = createWidget(WidgetType::BitmapButton, "Button", "8%", std::to_string(sizeY), std::to_string(butPosX), "2%", false)->cast<tgui::BitmapButton>();
					gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopCharacterStats")->add(but2, "char" + std::to_string(i) + "EquipButton" + std::to_string(j));
					if (p->characters[i].first->equipment[j]->icon == NULL) giveIconToItem(p->characters[i].first->equipment[j]);
					but2->setImage(*p->characters[i].first->equipment[j]->icon);
				}
			}
			gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopCharacterStats")->add(createWidgetLabel("Label", "1%", "20%", 20, L"Class: " + p->characters[i].first->characterClass, false), "shopClassLabel" + std::to_string(i));

		}
	}
	if (!rebuild)
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
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopShipPanel"), true);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopCrewPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopResourcesPanel"), false);
}

void ChangeToCrew()
{
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopModEquipPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopShipPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopCrewPanel"), true);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("iternalShopResourcesPanel"), false);
}

void tradeItems(Goods g, Shop *p)
{
	int count = 0;
	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{
		if (gEnv->game.player.inventory[i] != NULL)
		{
			if (gEnv->game.player.inventory[i]->itemId == g.itemPrice->itemId)
			{
				count += static_cast<ItemResource*>(gEnv->game.player.inventory[i])->count;
			}
		}
	}
	if (count >= static_cast<ItemResource*>(g.itemPrice)->count)
	{
		int paid = 0;
		for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
		{
			if (gEnv->game.player.inventory[i] != NULL)
			{
				if (gEnv->game.player.inventory[i]->itemId == g.itemPrice->itemId)
				{
					if (paid == static_cast<ItemResource*>(g.itemPrice)->count)
						break;
					if (static_cast<ItemResource*>(g.itemPrice)->count - paid >= static_cast<ItemResource*>(gEnv->game.player.inventory[i])->count)
					{
						paid += static_cast<ItemResource*>(gEnv->game.player.inventory[i])->count;
						gEnv->game.player.inventory[i] = NULL;
					}
					else
					{
						static_cast<ItemResource*>(gEnv->game.player.inventory[i])->count -= static_cast<ItemResource*>(g.itemPrice)->count - paid;
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
				gEnv->game.player.inventory[i] = g.product;
				
				switch (g.product->itemType)
				{
				case itemType::resource:
					for (int j = 0; j < p->resources.size(); j++)
					{
						if (g.creditsPrice == p->resources[j].creditsPrice
							&& g.itemPrice == p->resources[j].itemPrice
							&& g.product == p->resources[j].product
							&& g.stock == p->resources[j].stock)
						{
							p->resources.erase(p->resources.begin() + j);
						}
					}
					break;
				case itemType::module:
					for (int j = 0; j < p->resources.size(); j++)
					{
						if (g.creditsPrice == p->modules[j].creditsPrice
							&& g.itemPrice == p->modules[j].itemPrice
							&& g.product == p->modules[j].product
							&& g.stock == p->modules[j].stock)
						{
							p->modules.erase(p->modules.begin() + j);
						}
					}
					break;
				case itemType::equipment:
					for (int j = 0; j < p->equipments.size(); j++)
					{
						if (g.creditsPrice == p->equipments[j].creditsPrice
							&& g.itemPrice == p->equipments[j].itemPrice
							&& g.product == p->equipments[j].product
							&& g.stock == p->equipments[j].stock)
						{
							p->equipments.erase(p->equipments.begin() + j);
						}
					}
					break;
				}
				buildShop(p, true); 
				
				break;
			}
		}
		rebuildAll();
	}
}

void buyItem(Goods g, Shop *p)
{
	if (gEnv->game.player.money >= g.creditsPrice)
	{
		for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
		{
			if (gEnv->game.player.inventory[i] == NULL)
			{
				gEnv->game.player.inventory[i] = g.product;
				updateInventoryCell(i);
				gEnv->game.player.money -= g.creditsPrice;
				gEnv->game.adventureGUI.get<tgui::Label>("moneyLabel")->setText(L"Credits: " + std::to_wstring(gEnv->game.player.money));

				switch (g.product->itemType)
				{
				case itemType::resource:
					for (int j = 0; j < p->resources.size(); j++)
					{
						if (g.creditsPrice == p->resources[j].creditsPrice
							&& g.itemPrice == p->resources[j].itemPrice
							&& g.product == p->resources[j].product
							&& g.stock == p->resources[j].stock)
						{
							p->resources.erase(p->resources.begin() + j);
						}
					}
					break;
				case itemType::module:
					for (int j = 0; j < p->resources.size(); j++)
					{
						if (g.creditsPrice == p->modules[j].creditsPrice
							&& g.itemPrice == p->modules[j].itemPrice
							&& g.product == p->modules[j].product
							&& g.stock == p->modules[j].stock)
						{
							p->modules.erase(p->modules.begin() + j);
						}
					}
					break;
				case itemType::equipment:
					for (int j = 0; j < p->equipments.size(); j++)
					{
						if (g.creditsPrice == p->equipments[j].creditsPrice
							&& g.itemPrice == p->equipments[j].itemPrice
							&& g.product == p->equipments[j].product
							&& g.stock == p->equipments[j].stock)
						{
							p->equipments.erase(p->equipments.begin() + j);
						}
					}
					break;
				}
				buildShop(p, true);
				break;
			}
		}
	}
}

void sellItem(tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (gEnv->game.player.pickedItem != NULL)
	{
		int price = 0;
		switch (gEnv->game.player.pickedItem->itemType)
		{
		case itemType::resource:
			switch (gEnv->game.player.pickedItem->itemId)
			{
			case -10:
				price = 10 * static_cast<ItemResource*>(gEnv->game.player.pickedItem)->count;
				break;
			}
			break;
		}
		if (signalName == "MouseEntered")
		{
			gEnv->game.adventureGUI.get<tgui::Label>("sellItemLabel")->setText("Item price: " + std::to_string(price) + ", click to sell");
		}
		else if (signalName == "MouseReleased")
		{
			gEnv->game.player.money += price;
			gEnv->game.adventureGUI.get<tgui::Label>("moneyLabel")->setText(L"Credits: " + std::to_wstring(gEnv->game.player.money));
			gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse"));
			gEnv->game.player.pickedItem = NULL;
			gEnv->game.player.pickedItemInvId = -1;
			gEnv->game.player.pickedLocalInventory = -1;
			gEnv->game.ui.shiftedItem = false;
			gEnv->game.ui.shiftedItemStartId = -1;
			gEnv->game.ui.shiftedItemTakedAll = false;
			gEnv->game.adventureGUI.get<tgui::Label>("sellItemLabel")->setText("Item sold");
		}
		else if (signalName == "MouseLeft")
		{
			gEnv->game.adventureGUI.get<tgui::Label>("sellItemLabel")->setText(L"Place cursor with item to the box to see item price");
		}
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

void crewClick(int id, Character *c, int price)
{
	auto widgets = gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("shopCharacterStats")->getWidgets();
	for (int i = 0; i < widgets.size(); i++)
	{
		enableWidget(widgets[i], false);
	}
	enableWidget(gEnv->game.adventureGUI.get<tgui::BitmapButton>("buyCharacterButton"), true);

	enableWidget(gEnv->game.adventureGUI.get<tgui::Label>("charItemsLab" + std::to_string(id)), true);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Label>("shopClassLabel" + std::to_string(id)), true);

	for (int i = 0, k = 0; i < c->equipment.size(); i++)
	{
		if (c->equipment[i] != NULL) enableWidget(gEnv->game.adventureGUI.get<tgui::BitmapButton>("char" + std::to_string(id) + "EquipButton" + std::to_string(i)), true);
	}

	gEnv->game.ui.choosenShopCharacter = c;
	gEnv->game.ui.choosenShopCharacterPrice = price;
}

void buyCrew()
{
	registerPlayerCharacter(gEnv->game.ui.choosenShopCharacter);
}

void removeShop()
{

}