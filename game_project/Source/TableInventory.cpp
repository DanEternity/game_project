#include "tableInventory.h"

void BuildInventoryUI(int cellSize)
{

	tgui::ScrollablePanel::Ptr scrollablePanel = tgui::ScrollablePanel::create();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(scrollablePanel, "inventoryPanel");
	scrollablePanel->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));
	scrollablePanel->setPosition("5%", "15%");
	scrollablePanel->setSize(520, 200);
	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{

		int positionX = i % cellSize;
		int positionY = i / cellSize;
		const int number = i;
		tgui::BitmapButton::Ptr button = tgui::BitmapButton::create();

		scrollablePanel->add(button, "InventoryCell"+ std::to_string(i));

		button->setSize(45, 40);
		button->setPosition(5 + positionX * 50, 10 + positionY * 50);
		button->setRenderer(gEnv->globalTheme.getRenderer("Button"));

		//tgui::Texture* tex = new tgui::Texture(gEnv->modelDB[L"butText"]->tex,sf::IntRect(0,0,45,40), sf::IntRect(0,0,45,40));
		//button->setImage(*tex);

		if (gEnv->game.player.inventory[i] != NULL)
			button->setText(gEnv->game.player.inventory[i]->name);
		else
			button->setText(L"");



		button->connect("MouseReleased", IntentoryResponseSignal, number, std::string("ShipInventory"));
		button->connect("RightMouseReleased", IntentoryResponseSignal, number, std::string("ShipInventory"));
		button->connect("MouseEntered", applyStorageTooltip, i);

		//auto tooltop = tgui::Panel::create();
		//tooltop->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
		//tooltop->setSize(500, 100);
		//tgui::Button::Ptr but = tgui::Button::create();
		//but->setSize(9, 50);
		//but->setPosition(50, 50);
		//but->setText("O");
		//but->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		//tooltop->add(but);
		//button->setToolTip(tooltop);
	}
	scrollablePanel->setEnabled(false);
	scrollablePanel->setVisible(false);
}

void UpdateInventoryUI()
{
	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{
		if (gEnv->game.player.inventory[i] != NULL)
			gEnv->game.adventureGUI.get<tgui::Button>("InventoryCell" + std::to_string(i))->setText(gEnv->game.player.inventory[i]->name);
		else gEnv->game.adventureGUI.get<tgui::Button>("InventoryCell" + std::to_string(i))->setText("");
	}
}

void DeleteInventoryUI()
{
}

void IntentoryResponseSignal( int cellId, std::string inventoryId, tgui::Widget::Ptr widget, const std::string & signalName)
{
	if (signalName == "MouseReleased")
	{
		if (gEnv->game.ui.selected != -1)
		{
			// swap

			std::swap(gEnv->game.player.inventory[cellId], gEnv->game.player.inventory[gEnv->game.ui.selected]);


			// update cell images
			tgui::ScrollablePanel::Ptr panel = gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("inventoryPanel");

			if (gEnv->game.player.inventory[cellId] != NULL)
				panel->get<tgui::Button>("InventoryCell" + std::to_string(cellId))->setText(gEnv->game.player.inventory[cellId]->name);
			else
				panel->get<tgui::Button>("InventoryCell" + std::to_string(cellId))->setText(L"");

			if (gEnv->game.player.inventory[gEnv->game.ui.selected] != NULL)
				panel->get<tgui::Button>("InventoryCell" + std::to_string(gEnv->game.ui.selected))->setText(gEnv->game.player.inventory[gEnv->game.ui.selected]->name);
			else
				panel->get<tgui::Button>("InventoryCell" + std::to_string(gEnv->game.ui.selected))->setText(L"");

			gEnv->game.ui.selected = -1;
			UpdateInventoryUI();
			deleteAllInventoryTooltips();
		}
		else
		{

			if (gEnv->game.player.inventory[cellId] != NULL)
			{
				gEnv->game.ui.selected = cellId;
			}
		}
	}
	else if (signalName == "RightMouseReleased" && !gEnv->game.ui.rmWasClicked)
	{
		tgui::Panel::Ptr temp = tgui::Panel::create();
		temp->setSize(100, 90);
		int x = sf::Mouse::getPosition(gEnv->globalWindow).x;
		int y = sf::Mouse::getPosition(gEnv->globalWindow).y - 5;
		temp->setPosition(x, y);
		temp->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
		gEnv->game.adventureGUI.add(temp, "tempRightPanel");
		gEnv->game.ui.rmWasClicked = true;

		const int id = cellId;

		tgui::Button::Ptr btn = tgui::Button::create();

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 0);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Install into");
		btn->connect("MouseReleased", rmPanelClickedInventory, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 30);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Delete");
		btn->connect("MouseReleased", rmPanelClickedInventory, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 60);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Cancel");
		btn->connect("MouseReleased", rmPanelClickedInventory, id);
	}
}

void rmPanelClickedInventory(const int id, tgui::Widget::Ptr widget, const std::string& signalName)
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

	}
	else if (widget->cast<tgui::Button>()->getText() == L"Install into")
	{
		if (gEnv->game.player.inventory[id]->itemType == itemType::module)
		{
			gEnv->game.ui.tempAddPanelClicked = true;
			int goodItemsCount = 0;
			tgui::Button::Ptr btn;
			tgui::Panel::Ptr panel = tgui::Panel::create();
			for (int i(0); i < gEnv->game.player.ship->slots.size(); i++)
			{
				if (static_cast<Module*>(gEnv->game.player.inventory[id])->slot == gEnv->game.player.ship->slots[i].type)
				{
					btn = tgui::Button::create();
					btn->setSize(187, 31);
					btn->setPosition(0, 30 * goodItemsCount);
					btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
					btn->setText(L"Insert instead: " + gEnv->game.player.ship->modules[i]->name);
					const int num = i;
					btn->connect("MouseReleased", rmPanelChoosenInsert, id, num, 0);
					panel->add(btn);
					goodItemsCount++;
				}
			}
			if (goodItemsCount != 0)
			{
				panel->setSize(180, 30 * goodItemsCount);
				auto pos = gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->getPosition();
				pos.x += 100;
				panel->setPosition(pos);
				panel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
				gEnv->game.adventureGUI.add(panel, "tempAddPanel");
			}
			else
				gEnv->game.ui.tempAddPanelClicked = false;
		}
		else if (gEnv->game.player.inventory[id]->itemType == itemType::equipment)
		{
			gEnv->game.ui.tempAddPanelClicked = true;
			int goodItemsCount = 0;
			tgui::Button::Ptr btn;
			tgui::Panel::Ptr panel = tgui::Panel::create();
			for (int i(0); i < gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->slot.size(); i++)
			{
				if (static_cast<Equipment*>(gEnv->game.player.inventory[id])->equipmentSlotType == gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->slot[i])
				{
					btn = tgui::Button::create();
					btn->setSize(187, 31);
					btn->setPosition(0, 30 * goodItemsCount);
					btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
					if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[i] != NULL)
						btn->setText(L"Insert instead: " + gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[i]->name);
					else btn->setText(L"Insert instead: Empty");
					const int num = i;
					btn->connect("MouseReleased", rmPanelChoosenInsert, id, num, 1);
					panel->add(btn);
					goodItemsCount++;
				}
			}
			if (goodItemsCount != 0)
			{
				panel->setSize(180, 30 * goodItemsCount);
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

void rmPanelChoosenInsert(const int id, const int item_id, int inventory, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (inventory == 0)
	{
		gEnv->game.ui.tempAddPanelClicked = true;
		Module* temp = static_cast<Module*>(gEnv->game.player.inventory[id]);

		gEnv->game.player.inventory[id] = gEnv->game.player.ship->modules[item_id];
		gEnv->game.player.ship->modules[item_id] = temp;

		tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel");
		tgui::Panel::Ptr panel2 = gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel");

		if (gEnv->game.player.inventory[id] != NULL)
			panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(gEnv->game.player.inventory[id]->name);
		else
			panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(L"");

		if (gEnv->game.player.ship->modules[item_id] != NULL)
			panel2->get<tgui::Button>("ShipSchemeModule" + std::to_string(item_id))->setText(gEnv->game.player.ship->modules[item_id]->name);
		else
			panel2->get<tgui::Button>("ShipSchemeModule" + std::to_string(item_id))->setText(L"");

		UpdateInventoryUI();
		deleteAllInventoryTooltips();

		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
		gEnv->game.ui.rmWasClicked = false;
		gEnv->game.ui.tempAddPanelClicked = false;
	}
	else if (inventory == 1)
	{
		gEnv->game.ui.tempAddPanelClicked = true;
		Equipment* temp = static_cast<Equipment*>(gEnv->game.player.inventory[id]);

		gEnv->game.player.inventory[id] = gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[item_id];
		gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[item_id] = temp;

		tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel");
		tgui::Panel::Ptr panel2 = gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel");

		if (gEnv->game.player.inventory[id] != NULL)
			panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(gEnv->game.player.inventory[id]->name);
		else
			panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(L"");

		if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[item_id] != NULL)
			panel2->get<tgui::Button>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(item_id))->setText(gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[item_id]->name);
		else
			panel2->get<tgui::Button>("Person" + std::to_string(gEnv->game.ui.activeOpenPersonWindow) + "Equip" + std::to_string(item_id))->setText(L"");

		UpdateInventoryUI();
		deleteAllInventoryTooltips();

		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
		gEnv->game.ui.rmWasClicked = false;
		gEnv->game.ui.tempAddPanelClicked = false;
	}
}

void CreateInventoryGridPanel(int length)
{

	tgui::ScrollablePanel::Ptr scrollablePanel = tgui::ScrollablePanel::create();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->add(scrollablePanel, "inventoryGridPanel");
	scrollablePanel->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));
	scrollablePanel->setPosition("3%", "25%");
	scrollablePanel->setSize(520, 140);


	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{

		int positionX = i % length;
		int positionY = i / length;
		const int number = i;
		tgui::Button::Ptr button = tgui::Button::create();

		scrollablePanel->add(button, "InventoryItem" + std::to_string(i));

		button->setSize(45, 40);
		button->setPosition(5 + positionX * 50, 10 + positionY * 50);
		button->setRenderer(gEnv->globalTheme.getRenderer("Button"));

		button->setText(L"");

		button->connect("MouseReleased", InventoryGridPanelEventHandler, number);
		button->connect("RightMouseReleased", InventoryGridPanelEventHandler, number);
	}

}

void RebuildInventoryGridPanel()
{

	gEnv->game.player.localInventory.clear();

	// apply category filter
	//gEnv->game.player.inventoryFilter.searchString = L"Ebalo";
	//
	for (int id(0); id < gEnv->game.player.inventory.size(); id++)
	{
		if (gEnv->game.player.inventory[id] != NULL)
		{

			// compare to filter
			//

			auto p = gEnv->game.player.inventory[id];

			//if (p->itemType in filter.itemTypes && p->name in filter.nameSeacrh)

			bool filter_ok = true;
			IntventoryFilter* filter = &gEnv->game.player.inventoryFilter;
			
			if (filter->searchString != L"")
			{
				if (p->name.find(filter->searchString) == std::wstring::npos)
				{
					filter_ok = false;
				}
			}

			if (filter->itemType.size() > 0)
			{
				if (filter->itemType.find(p->itemType) == filter->itemType.end())
				{
					filter_ok = false;
				}
			}

			if (p->itemType == itemType::module)
			{
				if (filter->moduleSlotType.size() > 0)
				{
					if (filter->moduleSlotType.find(static_cast<Module*>(p)->slot) == filter->moduleSlotType.end())
					{
						filter_ok = false;
					}
				}
			}

			if (p->itemType == itemType::equipment)
			{
				if (filter->equipmentType.size() > 0)
				{
					if (filter->equipmentType.find(static_cast<Equipment*>(p)->equipmentType) == filter->equipmentType.end())
					{
						filter_ok = false;
					}
				}
			}
			if (p->itemType == itemType::resource)
			{
				if (filter->equipmentType.size() > 0)
				{
						filter_ok = false;
				}
			}

			if (!filter_ok)
				continue;
			gEnv->game.player.localInventory.push_back(id);

		}
	}

	UpdateInventoryUI();
	deleteAllGridTooltips();
	for (int id(0); id < gEnv->game.player.inventory.size(); id++)
	{	
		if (id < gEnv->game.player.localInventory.size() && gEnv->game.player.localInventory[id] != -1)
			gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(id))->
			setText(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->name);
		else
			gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(id))->
			setText(L"");
		if (gEnv->game.player.localInventory.size() > id) {
			if (gEnv->game.player.inventory[gEnv->game.player.localInventory[id]] != NULL)
			{
				switch (gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->itemType)
				{
				case itemType::module:
					gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(id))->connect("MouseEntered", applyGridModuleTooltip, id);
					break;
				case itemType::equipment:
					gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(id))->connect("MouseEntered", applyGridEquipmentTooltip, id);
					break;
				}
			}
		}
	}
}

void ApplyDefaultFilterToInventoryPanel()
{

	// current menu
	auto q = gEnv->game.player.shipMenu;
	
	if (q == shipMenu::ship)
	{
		gEnv->game.player.inventoryFilter.itemType.insert(itemType::module);
	}

	if (q == shipMenu::crew)
	{
		gEnv->game.player.inventoryFilter.itemType.insert(itemType::equipment);
	}
	if (q == shipMenu::craft)
	{
		gEnv->game.player.inventoryFilter.itemType.insert(itemType::resource);
	}
}

void filterSearchFieldChanged(tgui::Widget::Ptr widget, const std::string & signalName)
{

	gEnv->game.player.inventoryFilter.searchString = widget->cast<tgui::EditBox>()->getText();

	RebuildInventoryGridPanel();

}

void filterCategoryFieldChanged(tgui::Widget::Ptr widget, const std::string & signalName)
{

	auto p = widget->cast<tgui::ComboBox>();
	std::string s = p->getSelectedItemId();

	printf("Filter set: %s \n", s.c_str());

	gEnv->game.player.inventoryFilter.itemType.clear();
	gEnv->game.player.inventoryFilter.equipmentType.clear();
	gEnv->game.player.inventoryFilter.moduleSlotType.clear();

	if (s == "Primary weapon")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::primaryWeapon);
	}
	if (s == "Secondary weapon")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::secondaryWeapon);
	}
	if (s == "Engine")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::engine);
	}
	if (s == "Hyperdrive")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::hyperdrive);
	}
	if (s == "Core")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::core);
	}
	if (s == "System")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::system);
	}
	if (s == "Universal")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::universal);
	}

	


	// currently do nothing because not all windows are completed
	ApplyDefaultFilterToInventoryPanel();

	RebuildInventoryGridPanel();

}

void InventoryGridPanelEventHandler(const int id, tgui::Widget::Ptr widget, const std::string & signalName)
{
	if (signalName == "MouseReleased")
	{
		// handle left click
		if (gEnv->game.player.pickedItem == NULL)
		{
			if ( id < gEnv->game.player.localInventory.size() && gEnv->game.player.localInventory[id] != -1)
				if (gEnv->game.player.inventory[gEnv->game.player.localInventory[id]] != NULL)
				{
					gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(id))->setRenderer(gEnv->globalTheme.getRenderer("Button2"));
					gEnv->game.player.pickedItem = gEnv->game.player.inventory[gEnv->game.player.localInventory[id]];
					gEnv->game.player.pickedLocalInventory = id;
					gEnv->game.player.pickedItemInvId = gEnv->game.player.localInventory[id];
					return;
				}
		}
		else
		{
			// swap items if can
			if (id < gEnv->game.player.localInventory.size() && gEnv->game.player.localInventory[id] != -1)
				if (gEnv->game.player.inventory[gEnv->game.player.localInventory[id]] != NULL)
				{
					gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(gEnv->game.player.pickedLocalInventory))->setRenderer(gEnv->globalTheme.getRenderer("Button"));
					std::swap(
						gEnv->game.player.inventory[gEnv->game.player.localInventory[id]], 
						gEnv->game.player.inventory[gEnv->game.player.localInventory[gEnv->game.player.pickedLocalInventory]]);

					gEnv->game.player.pickedLocalInventory = -1;
					gEnv->game.player.pickedItem = NULL;
					RebuildInventoryGridPanel();
					return;

				}
		}
	}

	if (signalName == "RightMouseReleased")
	{
		// handle right click
		
	}

}

void createModuleTooltip(Module * m)
{
	m->tooltipDescription->setSize(300, 250 + m->effects.size() * 30);
	m->tooltipDescription->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));

	tgui::Button::Ptr button = tgui::Button::create();
	button->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	button->setPosition(0, 0);
	button->setSize(300, 30);
	button->setText(m->name);
	m->tooltipDescription->add(button, "nameButtonTooltip");

	tgui::Label::Ptr label = tgui::Label::create();
	label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label->setPosition("(&.width - width) / 2", 30);
	label->setText("Module");
	label->setTextSize(18);
	m->tooltipDescription->add(label);

	tgui::Label::Ptr label2 = tgui::Label::create();
	label2->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label2->setPosition("(&.width - width) / 4 - 20", 60);
	label2->setText(L"Level: " + std::to_wstring(m->level));
	label2->setTextSize(18);
	m->tooltipDescription->add(label2);

	tgui::Label::Ptr label3 = tgui::Label::create();
	label3->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label3->setPosition("(&.width - width) / 4 * 3", 60);
	label3->setText(L"Rarity: " + std::to_wstring(m->rarity));
	label3->setTextSize(18);
	m->tooltipDescription->add(label3);

	tgui::Label::Ptr label4 = tgui::Label::create();
	label4->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label4->setPosition("(&.width - width) / 2", 90);
	switch (m->slot)
	{
	case moduleSlot::core:
		label4->setText("Slot type: Core");
		break;
	case moduleSlot::hyperdrive:
		label4->setText("Slot type: Hyperdrive");
		break;
	case moduleSlot::engine:
		label4->setText("Slot type: Engine");
		break;
	case moduleSlot::system:
		label4->setText("Slot type: System");
		break;
	case moduleSlot::primaryWeapon:
		label4->setText("Slot type: Primary Weapon");
		break;
	case moduleSlot::secondaryWeapon:
		label4->setText("Slot type: Secondary Weapon");
		break;
	case moduleSlot::universal:
		label4->setText("Slot type: Universal");
		break;
	}
	label4->setTextSize(18);
	m->tooltipDescription->add(label4);


	tgui::Label::Ptr label5 = tgui::Label::create();
	label5->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label5->setPosition(10, 120);
	label5->setTextSize(18);
	m->tooltipDescription->add(label5);

	std::wstring str = L"";
	bool first = true;
	str += L"Usage Power Supply: " + std::to_wstring((int)(static_cast<Module*>(m)->powerSupply)) + L"\n";
	str += L"Usage High Power Supply: " + std::to_wstring((int)(static_cast<Module*>(m)->highPowerSupply)) + L"\n\n";
	for (auto i : static_cast<Module*>(m)->effects)
	{
		switch (static_cast<StatModEffect*>(i)->statName)
		{
		case statNames::hull:
			str += GetString("Hull") + L" ";
			break;
		case statNames::actionPoints:
			str += GetString("Action points in battle") + L" ";
			break;
		case statNames::additionalWeaponAccuracy:
			str += GetString("Additional weapon accuracy") + L" ";
			break;
		case statNames::evasion:
			str += GetString("Evasion rating") + L" ";
			break;
		case statNames::fuel:
			str += GetString("Fuel") + L" ";
			break;
		case statNames::highPowerSupply:
			str += GetString("High power supply") + L" ";
			break;
		case statNames::hullReg:
			str += GetString("Hull regeneration") + L" ";
			break;
		case statNames::hullResist:
			str += GetString("Hull resist") + L" ";
			break;
		case statNames::hullStructureStability:
			str += GetString("Hull structure stability") + L" ";
			break;
		case statNames::hyperDriveFuelEfficiency:
			str += GetString("Hyper drive fuel efficiency") + L" ";
			break;
		case statNames::hyperDrivePower:
			str += GetString("Hyper drive power") + L" ";
			break;
		case statNames::hyperDriveTier:
			str += GetString("Hyper drive tier") + L" ";
			break;
		case statNames::missileDefense:
			str += GetString("Missile defence") + L" ";
			break;
		case statNames::missileDefenseTier:
			str += GetString("Misile defence tier") + L" ";
			break;
		case statNames::mobility:
			str += GetString("Mobility") + L" ";
			break;
		case statNames::powerSupply:
			str += GetString("Power supply") + L" ";
			break;
		case statNames::sensorPower:
			str += GetString("Sensor power") + L" ";
			break;
		case statNames::sensorTier:
			str += GetString("Sensor tier") + L" ";
			break;
		case statNames::shield:
			str += GetString("Shield") + L" ";
			break;
		case statNames::shieldReg:
			str += GetString("Shield regeneration") + L" ";
			break;
		case statNames::shieldResist:
			str += GetString("Shield resist") + L" ";
			break;
		case statNames::shieldStructureStability:
			str += GetString("Shield structure stability") + L" ";
			break;
		case statNames::stealth:
			str += GetString("Stealth") + L" ";
			break;
		case statNames::stealthTier:
			str += GetString("Stealth tier") + L" ";
			break;
		case statNames::totalDamageMultiplier:
			str += GetString("Total damage multiplier") + L" ";
			break;
		}
		if (static_cast<StatModEffect*>(i)->p_add != 0)
			str += L"+" + std::to_wstring((int)static_cast<StatModEffect*>(i)->p_add) + L" ";
		if (static_cast<StatModEffect*>(i)->p_mul != 0)
			str += L"+" + std::to_wstring((int)(static_cast<StatModEffect*>(i)->p_mul * 100)) + L"% ";
		if (static_cast<StatModEffect*>(i)->p_sub != 0)
			str += L"-" + std::to_wstring((int)static_cast<StatModEffect*>(i)->p_sub) + L" ";
		if (static_cast<StatModEffect*>(i)->p_negMul != 0)
			str += L"-" + std::to_wstring((int)(static_cast<StatModEffect*>(i)->p_negMul * 100)) + L"% ";

		if (!first)
			label5->setText(label5->getText() + str + L"\n");
		else 
			label5->setText(str + L"\n");
		first = false;
		str = L"";
	}
}

void createResourseTooltip(ItemResource * r)
{
	r->tooltipDescription->setSize(300, 100);
	r->tooltipDescription->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));

	tgui::Button::Ptr button = tgui::Button::create();
	button->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	button->setPosition(0, 0);
	button->setSize(300, 30);
	button->setText(r->name);
	r->tooltipDescription->add(button, "nameButtonTooltip");

	tgui::Label::Ptr label = tgui::Label::create();
	label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label->setPosition("(&.width - width) / 2", 30);
	label->setText("Level " + std::to_string(r->level));
	label->setTextSize(18);
	r->tooltipDescription->add(label);

	tgui::Label::Ptr label2 = tgui::Label::create();
	label2->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label2->setPosition("(&.width - width) / 2", 60);
	label2->setText(L"Count: " + std::to_wstring(r->count) + L"/" + std::to_wstring(r->maxCount));
	label2->setTextSize(18);
	r->tooltipDescription->add(label2);
}

void createEquipmentTooltip(Equipment* e)
{
	e->tooltipDescription->setSize(300, 250 + e->effects.size() * 30);
	e->tooltipDescription->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));

	tgui::Button::Ptr button = tgui::Button::create();
	button->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	button->setPosition(0, 0);
	button->setSize(300, 30);
	button->setText(e->name);
	e->tooltipDescription->add(button, "nameButtonTooltip");

	tgui::Label::Ptr label = tgui::Label::create();
	label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label->setPosition("(&.width - width) / 2", 30);
	label->setText("Equipment");
	label->setTextSize(18);
	e->tooltipDescription->add(label);

	tgui::Label::Ptr label2 = tgui::Label::create();
	label2->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label2->setPosition("(&.width - width) / 4 - 20", 60);
	label2->setText(L"Level: " + std::to_wstring(e->level));
	label2->setTextSize(18);
	e->tooltipDescription->add(label2);

	tgui::Label::Ptr label3 = tgui::Label::create();
	label3->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label3->setPosition("(&.width - width) / 4 * 3", 60);
	label3->setText(L"Rarity: " + std::to_wstring(e->rarity));
	label3->setTextSize(18);
	e->tooltipDescription->add(label3);

	tgui::Label::Ptr label4 = tgui::Label::create();
	label4->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label4->setPosition("(&.width - width) / 2", 90);
	switch (e->equipmentSlotType)
	{
	case equipmentSlot::head:
		label4->setText("Slot type: Helmet");
		break;
	case equipmentSlot::arms:
		label4->setText("Slot type: Arms");
		break;
	case equipmentSlot::body:
		label4->setText("Slot type: Body");
		break;
	case equipmentSlot::legs:
		label4->setText("Slot type: Legs");
		break;
	case equipmentSlot::universal:
		label4->setText("Slot type: Universal");
	}
	label4->setTextSize(18);
	e->tooltipDescription->add(label4);


	tgui::Label::Ptr label5 = tgui::Label::create();
	label5->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label5->setPosition(10, 120);
	label5->setTextSize(18);
	e->tooltipDescription->add(label5);

	std::wstring str = L"";
	bool first = true;
	for (auto i : static_cast<Equipment*>(e)->effects)
	{
		switch (static_cast<StatModEffect*>(i)->statName)
		{
		case statNames::characterHealth:
			str += GetString("Health") + L" ";
			break;
		case statNames::characterArmor:
			str += GetString("Armor") + L" ";
			break;
		case statNames::characterShield:
			str += GetString("Shield") + L" ";
			break;
		case statNames::characterBlock:
			str += GetString("Block") + L" ";
			break;
		case statNames::characterResist:
			str += GetString("Resist") + L" ";
			break;
		case statNames::characterShieldReg:
			str += GetString("Shield Regeneration") + L" ";
			break;
		case statNames::characterActionPoints:
			str += GetString("Action Points") + L" ";
			break;
		case statNames::characterEnergy:
			str += GetString("Energy") + L" ";
			break;
		case statNames::characterEnergyReg:
			str += GetString("Energy Regeneration") + L" ";
			break;
		case statNames::characterInitiative:
			str += GetString("Initiative") + L" ";
			break;
		}
		if (static_cast<StatModEffect*>(i)->p_add != 0)
			str += L"+" + std::to_wstring((int)static_cast<StatModEffect*>(i)->p_add) + L" ";
		if (static_cast<StatModEffect*>(i)->p_mul != 0)
			str += L"+" + std::to_wstring((int)(static_cast<StatModEffect*>(i)->p_mul * 100)) + L"% ";
		if (static_cast<StatModEffect*>(i)->p_sub != 0)
			str += L"-" + std::to_wstring((int)static_cast<StatModEffect*>(i)->p_sub) + L" ";
		if (static_cast<StatModEffect*>(i)->p_negMul != 0)
			str += L"-" + std::to_wstring((int)(static_cast<StatModEffect*>(i)->p_negMul * 100)) + L"% ";

		if (!first)
			label5->setText(label5->getText() + str + L"\n");
		else
			label5->setText(str + L"\n");
		first = false;
		str = L"";
	}
}

void deleteAllInventoryTooltips()
{
	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{
		gEnv->game.adventureGUI.get<tgui::Button>("InventoryCell" + std::to_string(i))->setToolTip(NULL);
		//gEnv->game.adventureGUI.get<tgui::Button>("InventoryCell" + std::to_string(i))->disconnectAll("MouseEntered");
	}
}

void deleteAllGridTooltips()
{
	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{
		gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(i))->setToolTip(NULL);
		//gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(i))->disconnectAll("MouseEntered");
	}
}


void applyStorageTooltip(int id)
{
	if (gEnv->game.player.inventory[id] != NULL)
	{
		switch (gEnv->game.player.inventory[id]->itemType)
		{
		case itemType::module:
			if (!gEnv->game.player.inventory[id]->tooltipWasCreated)
			{
				createModuleTooltip(static_cast<Module*>(gEnv->game.player.inventory[id]));
				gEnv->game.player.inventory[id]->tooltipWasCreated = true;
			}
			gEnv->game.adventureGUI.get<tgui::Button>("InventoryCell" + std::to_string(id))->setToolTip(gEnv->game.player.inventory[id]->tooltipDescription);
			tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
			break;
		case itemType::resource:
			if (!gEnv->game.player.inventory[id]->tooltipWasCreated)
			{
				createResourseTooltip(static_cast<ItemResource*>(gEnv->game.player.inventory[id]));
				gEnv->game.player.inventory[id]->tooltipWasCreated = true;
			}
			gEnv->game.adventureGUI.get<tgui::Button>("InventoryCell" + std::to_string(id))->setToolTip(gEnv->game.player.inventory[id]->tooltipDescription);
			tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
			break;
		case itemType::equipment:
			if (!gEnv->game.player.inventory[id]->tooltipWasCreated)
			{
				createEquipmentTooltip(static_cast<Equipment*>(gEnv->game.player.inventory[id]));
				gEnv->game.player.inventory[id]->tooltipWasCreated = true;
			}
			gEnv->game.adventureGUI.get<tgui::Button>("InventoryCell" + std::to_string(id))->setToolTip(gEnv->game.player.inventory[id]->tooltipDescription);
			tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
			break;
		}
	}
}

void applyGridModuleTooltip(int id)
{
	if (id < gEnv->game.player.localInventory.size())
	{
		if (!gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->tooltipWasCreated)
		{
			gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->tooltipWasCreated = true;
			createModuleTooltip(static_cast<Module*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]));
		}
		gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(id))->setToolTip(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->tooltipDescription);
		tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
	}
}

void applyGridEquipmentTooltip(int id)
{
	if (id < gEnv->game.player.localInventory.size())
	{
		if (!gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->tooltipWasCreated)
		{
			gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->tooltipWasCreated = true;
			createEquipmentTooltip(static_cast<Equipment*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]));
		}
		gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(id))->setToolTip(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->tooltipDescription);
		tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
	}
}