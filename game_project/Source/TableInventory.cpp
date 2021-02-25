#include "tableInventory.h"

void BuildInventoryUI(int cellSize)
{
	if (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("inventoryPanel") != nullptr)
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("inventoryPanel")->removeAllWidgets();
	else gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::ScrollablePanel, "Panel3", "45%", "60%", "1%", "1%", false), "inventoryPanel");

	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{

		int positionX = i % cellSize;
		int positionY = i / cellSize;
		const int number = i;
		tgui::BitmapButton::Ptr button = createWidget(WidgetType::BitmapButton, "Button", "50", "50", std::to_string(10 + positionX * 55), std::to_string(10 + positionY * 55))->cast<tgui::BitmapButton>();
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("inventoryPanel")->add(button, "InventoryCell"+ std::to_string(i));

		if (gEnv->game.player.inventory[i] != NULL)
		{
			if (gEnv->game.player.inventory[i]->icon != nullptr)
				button->setImage(*gEnv->game.player.inventory[i]->icon);
			else button->setImage(gEnv->modelDB[L"itemDefault"]->tex);
		}
		else button->setImage(gEnv->modelDB[L"itemEmpty"]->tex);

		button->connect("MouseReleased", InventoryResponseSignal, number, std::string("ShipInventory"));
		button->connect("RightMouseReleased", InventoryResponseSignal, number, std::string("ShipInventory"));
		button->connect("MouseEntered", applyStorageTooltip, i);

		button->setToolTip(gEnv->game.ui.tooltipDescription);
		tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
	}
}

void updateInventoryCell(int id)
{
	if (gEnv->game.player.inventory[id] != NULL && gEnv->game.player.inventory[id]->itemType == itemType::resource)
	{
		createResourseTooltip(static_cast<ItemResource*>(gEnv->game.player.inventory[id]));
		//gEnv->game.ui.tooltipDescription->get<tgui::Label>("resourceCount")->setText(
			//L"Count: " + std::to_wstring(static_cast<ItemResource*>(gEnv->game.player.inventory[id])->count) + L"/" + std::to_wstring(static_cast<ItemResource*>(gEnv->game.player.inventory[id])->maxCount));
	}

	if (gEnv->game.player.inventory[id]->icon != nullptr)
		gEnv->game.adventureGUI.get<tgui::BitmapButton>("InventoryCell" + std::to_string(id))->setImage(*gEnv->game.player.inventory[id]->icon);
	else gEnv->game.adventureGUI.get<tgui::BitmapButton>("InventoryCell" + std::to_string(id))->setImage(gEnv->modelDB[L"itemDefault"]->tex);
}

void CreateInventoryGridPanel(int length)
{
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->add(createWidget(WidgetType::ScrollablePanel, "Panel2", "520", "140", "3%", "25%"), "inventoryGridPanel");
	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{
		int positionX = i % length;
		int positionY = i / length;
		const int number = i;
		tgui::BitmapButton::Ptr button = createWidget(WidgetType::BitmapButton, "Button", "45", "40", std::to_string(5 + positionX * 50), std::to_string(10 + positionY * 50))->cast<tgui::BitmapButton>();
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->add(button, "InventoryItem" + std::to_string(i));
		button->setText(L"");
		button->connect("MouseReleased", InventoryGridPanelEventHandler, number);
		button->connect("RightMouseReleased", InventoryGridPanelEventHandler, number);
		button->connect("MouseEntered", applyGridTooltip, i);
		button->setToolTip(gEnv->game.ui.tooltipDescription);
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

	for (int id(0); id < gEnv->game.player.inventory.size(); id++)
	{	
		if (id < gEnv->game.player.localInventory.size() && gEnv->game.player.localInventory[id] != -1)
		{
			if (gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->icon != nullptr)
				gEnv->game.adventureGUI.get<tgui::BitmapButton>("InventoryItem" + std::to_string(id))->
				setImage(*gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->icon);
			else
				gEnv->game.adventureGUI.get<tgui::BitmapButton>("InventoryItem" + std::to_string(id))->
				setImage(gEnv->modelDB[L"itemDefault"]->tex);
		}
		else
			gEnv->game.adventureGUI.get<tgui::BitmapButton>("InventoryItem" + std::to_string(id))->
			setImage(gEnv->modelDB[L"itemEmpty"]->tex);
	}
}

void ApplyDefaultFilterToInventoryPanel()
{

	// current menu
	auto q = gEnv->game.player.shipMenu;
	
	if (q == shipMenu::ship || q == shipMenu::hangar)
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