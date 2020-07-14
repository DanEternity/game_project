#include "ShipHandlers.h"

void handleShipModulesPanelEvent(const int id, tgui::Widget::Ptr widget, const std::string & signalName)
{

	if (signalName == "MouseReleased")
	{
		if (gEnv->game.player.pickedItem != NULL)
		{
			swapElements(TargetInventory::shipPanel, id);
		}
	}
	if (signalName == "RightMouseReleased" && !gEnv->game.ui.rmWasClicked)
	{
		//ui->activermModule = widget->cast<tgui::Button>()->getText();
		tgui::Panel::Ptr temp = tgui::Panel::create();
		temp->setSize(100, 90);
		int x = sf::Mouse::getPosition(gEnv->globalWindow).x;
		int y = sf::Mouse::getPosition(gEnv->globalWindow).y - 5;
		temp->setPosition(x, y);
		temp->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
		gEnv->game.adventureGUI.add(temp, "tempRightPanel");
		gEnv->game.ui.rmWasClicked = true;

		tgui::Button::Ptr btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 0);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Add");
		btn->connect("MouseReleased", rmPanelClickedShip, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 30);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Unequip");
		btn->connect("MouseReleased", rmPanelClickedShip, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 60);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Cancel");
		btn->connect("MouseReleased", rmPanelClickedShip, id);
	}

}

void rmPanelClickedShip(const int id, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (widget->cast<tgui::Button>()->getText() == L"Cancel")
	{
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
		gEnv->game.ui.rmWasClicked = false;
		if (gEnv->game.ui.tempAddPanelClicked)
		{
			gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
			gEnv->game.ui.tempAddPanelClicked = false;
		}
	}
	else if (widget->cast<tgui::Button>()->getText() == L"Unequip")
	{
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));

		// need to delete module correctly
		// = nullptr;
		for (int i(0); i < gEnv->game.player.inventory.size(); i++)
		{
			if (gEnv->game.player.inventory[i] == NULL)
			{
				gEnv->game.player.inventory[i] = gEnv->game.player.ship->modules[id];
				gEnv->game.player.ship->modules[id] = NULL;
				break;
			}
		}

		tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel");
		updateShipSchemeUI();
		gEnv->game.ui.rmWasClicked = false;
		if (gEnv->game.ui.tempAddPanelClicked)
		{
			gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
			gEnv->game.ui.tempAddPanelClicked = false;
		}

		updateShipValues(gEnv->game.player.ship);
		RebuildInventoryGridPanel();
		buildShipStats();

		BuildInventoryUI(9);
		deleteAllTooltipsShipUI();
	}
	else if (widget->cast<tgui::Button>()->getText() == L"Add")
	{
		if (!gEnv->game.ui.tempAddPanelClicked)
		{
			gEnv->game.ui.tempAddPanelClicked = true;
			int goodItemsCount = 0;
			tgui::Button::Ptr btn;
			tgui::Panel::Ptr panel = tgui::Panel::create();
			for (int i(0); i < gEnv->game.player.inventory.size(); i++)
			{
				if (gEnv->game.player.inventory[i] == nullptr) continue;
				if (gEnv->game.player.inventory[i]->itemType == itemType::module)
				{
					if (static_cast<Module*>(gEnv->game.player.inventory[i])->slot == gEnv->game.player.ship->slots[id].type)
					{
						btn = tgui::Button::create();
						btn->setSize(107, 31);
						btn->setPosition(0, 30 * goodItemsCount);
						btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
						btn->setText(gEnv->game.player.inventory[i]->name);
						const int num = i;
						btn->connect("MouseReleased", rmPanelChoosenAdded, num, id);
						panel->add(btn);
						goodItemsCount++;
					}
				}

			}
			if (goodItemsCount != 0)
			{
				panel->setSize(100, 30 * goodItemsCount);
				auto pos = gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->getPosition();
				pos.x += 100;
				panel->setPosition(pos);
				panel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
				gEnv->game.adventureGUI.add(panel, "tempAddPanel");
			}
			else
				gEnv->game.ui.tempAddPanelClicked = false;
		}


	}
}

void rmPanelChoosenAdded(const int id, const int module_id, tgui::Widget::Ptr widget, const std::string& signalName)
{

	gEnv->game.ui.tempAddPanelClicked = true;
	Module* temp = static_cast<Module*>(gEnv->game.player.inventory[id]);

	gEnv->game.player.inventory[id] = gEnv->game.player.ship->modules[module_id];
	gEnv->game.player.ship->modules[module_id] = temp;

	updateShipSchemeUI();
	BuildInventoryUI(9);

	gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
	gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
	gEnv->game.ui.rmWasClicked = false;
	gEnv->game.ui.tempAddPanelClicked = false;

	updateShipValues(gEnv->game.player.ship);
	RebuildInventoryGridPanel();
	buildShipStats();
	deleteAllTooltipsShipUI();

}