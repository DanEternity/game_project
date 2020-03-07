#include "shipModulesUI.h"
#include "enviroment.h"

void BuildShipSchemeUI(int moduleSizeUI)
{

	tgui::Panel::Ptr mainShipPanel = tgui::Panel::create();
	mainShipPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel3"));
	mainShipPanel->setSize(600, 300);
	mainShipPanel->setPosition("1%", "2%");
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(mainShipPanel, "ShipSchemeModulesPanel");

	for (int i(0); i < gEnv->game.player.ship->modules.size(); i++)
	{
		tgui::Button::Ptr btn = tgui::Button::create();
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setSize(moduleSizeUI, moduleSizeUI);
		btn->setPosition((rand() % 550) + 25, (rand() % 200) + 12);
		if (gEnv->game.player.ship->modules[i] != NULL)
			btn->setText(gEnv->game.player.ship->modules[i]->name);
		mainShipPanel->add(btn, "ShipSchemeModule" + std::to_string(i));
		const int id = i;

	//	btn->connect("RightMouseReleased", UIbuttonWasClicked, id);
	//	btn->connect("MouseReleased", UIbuttonWasClicked, id);

		btn->connect("MouseReleased", handleShipModulesPanelEvent, id);
		btn->connect("RightMouseReleased", handleShipModulesPanelEvent, id);
	}

	mainShipPanel->setVisible(false);
	mainShipPanel->setEnabled(false);
}

void UIbuttonWasClicked(const int id, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (signalName == "MouseReleased")
	{
		if (gEnv->game.ui.selected != -1)
		{
			if (static_cast<Module*>(gEnv->game.player.inventory[gEnv->game.ui.selected])->slot == gEnv->game.player.ship->modules[id]->slot)
			{
				Module* temp = static_cast<Module*>(gEnv->game.player.inventory[gEnv->game.ui.selected]);

				gEnv->game.player.inventory[gEnv->game.ui.selected] = gEnv->game.player.ship->modules[id];
				gEnv->game.player.ship->modules[id] = temp;

				tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel");
				tgui::Panel::Ptr panel2 = gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel");

				if (gEnv->game.player.inventory[gEnv->game.ui.selected] != NULL)
					panel->get<tgui::Button>("InventoryCell" + std::to_string(gEnv->game.ui.selected))->setText(gEnv->game.player.inventory[gEnv->game.ui.selected]->name);
				else
					panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(L"");

				if (gEnv->game.player.ship->modules[id] != NULL)
					panel2->get<tgui::Button>("ShipSchemeModule" + std::to_string(id))->setText(gEnv->game.player.ship->modules[id]->name);
				else
					panel2->get<tgui::Button>("ShipSchemeModule" + std::to_string(id))->setText(L"");
				gEnv->game.ui.selected = -1;
			}
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
		btn->setText(L"Delete");
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
	else if (widget->cast<tgui::Button>()->getText() == L"Delete")
	{
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));

		// need to delete module correctly
		gEnv->game.player.ship->modules[id] = nullptr;
		
		tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel");
		panel->get<tgui::Button>("ShipSchemeModule" + std::to_string(id))->setText("");
		gEnv->game.ui.rmWasClicked = false;
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

	tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel");
	tgui::Panel::Ptr panel2 = gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel");

	if (gEnv->game.player.inventory[id] != NULL)
		panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(gEnv->game.player.inventory[id]->name);
	else
		panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(L"");

	if (gEnv->game.player.ship->modules[module_id] != NULL)
		panel2->get<tgui::Button>("ShipSchemeModule" + std::to_string(module_id))->setText(gEnv->game.player.ship->modules[module_id]->name);
	else
		panel2->get<tgui::Button>("ShipSchemeModule" + std::to_string(module_id))->setText(L"");

	gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
	gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
	gEnv->game.ui.rmWasClicked = false;
	gEnv->game.ui.tempAddPanelClicked = false;

}

void handleShipModulesPanelEvent(const int id, tgui::Widget::Ptr widget, const std::string & signalName)
{

	if (signalName == "MouseReleased")
	{
		if (gEnv->game.player.pickedItem != NULL)
		{
			auto p_module = static_cast<Module*>(gEnv->game.player.pickedItem);
			auto type = p_module->slot;

			auto s_slot = gEnv->game.player.ship->slots[id];

			// compare to compability

			if (s_slot.type == type)
			{
				auto tmp = gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId];
				
				gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.ship->modules[id];
				gEnv->game.player.ship->modules[id] = static_cast<Module*>(tmp);
					
				widget->cast<tgui::Button>()->setText(gEnv->game.player.ship->modules[id]->name);

				gEnv->game.player.pickedItemInvId = -1;
				gEnv->game.player.pickedItem = NULL;
				gEnv->game.player.pickedLocalInventory = -1;

				RebuildInventoryGridPanel();

			}
			else
			{
				// nothing
				return;
			}


		}
	}

}
