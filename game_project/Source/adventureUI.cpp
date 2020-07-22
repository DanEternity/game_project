#include "adventureUI.h"

void updateAdventureUI()
{
	if (gEnv->game.adventureUI.adventureUIDrawRequired)
	{
		gEnv->game.adventureGUI.draw();
	}

	if (gEnv->game.adventureUI.widgetDisable)
	{
		disableAllAdventureUIWidgets();
		gEnv->game.mainMenu.widgetDisable = false;
	}
}

void DrawAdventureUI()
{
	if (gEnv->game.adventureUI.adventureUIDrawRequired)
	{
		gEnv->game.adventureGUI.draw();
	}
}

void disableAllAdventureUIWidgets()
{
	for (const auto& widget : gEnv->game.adventureUI.adventureUIWidgets)
	{
		widget->setVisible(false);
		widget->setEnabled(false);
	}
}

void createAdventureUIButtons()
{
	gEnv->game.player.ship = new Ship();

	gEnv->game.player.ship->hull.baseValue = 500;
	gEnv->game.player.ship->hull.total = 500;
	gEnv->game.player.ship->hull.current = 200;

	gEnv->game.player.ship->powerSupply.baseValue = 0;
	gEnv->game.player.ship->powerSupply.total = 0;
	gEnv->game.player.ship->powerSupply.current = 0;

	gEnv->game.player.ship->highPowerSupply.baseValue = 0;
	gEnv->game.player.ship->highPowerSupply.total = 0;
	gEnv->game.player.ship->highPowerSupply.current = 0;

	gEnv->game.player.ship->actionPoints.baseValue = 0;
	gEnv->game.player.ship->actionPoints.total = 0;
	gEnv->game.player.ship->actionPoints.current = 0;

	gEnv->game.player.ship->shield.baseValue = 0;
	gEnv->game.player.ship->shield.total = 0;
	gEnv->game.player.ship->shield.current = 0;

	gEnv->game.player.ship->hullResistEnergy.baseValue = 100;
	gEnv->game.player.ship->hullResistEnergy.total = 100;
	gEnv->game.player.ship->hullResistEnergy.current = 100;

	//minimap

	gEnv->game.adventureGUI.add(createWidget(WidgetType::Panel, "Panel", "400", "300", "10", "700"), "minimap");

	//create main interface panel

	gEnv->game.adventureGUI.add(createWidget(WidgetType::Panel, "Panel", "1200", "675", "20%", "15%", false), "playerUIMainPanel");
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->add(createWidget(WidgetType::Panel, "Panel2","1176","590","1%","1%", false),"playerUISubPanel");
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::Panel, "Panel3", "600", "200", "1%", "65%", false), "playerUIGridSubPanel");
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::ScrollablePanel, "Panel3", "43%", "570", "55%", "2%", false), "shipStatsPanel");

	// create buttons on main interface panel

	tgui::Button::Ptr btn = createWidget(WidgetType::BitmapButton, "Button", "140", "50", "35", "90%")->cast<tgui::BitmapButton>();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->add(btn);
	btn->setText("Ship");
	btn->setTextSize(22);
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::ship, 1, false);

	btn = createWidget(WidgetType::BitmapButton, "Button", "140", "50", "198", "90%")->cast<tgui::BitmapButton>();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->add(btn);
	btn->setText("Lab");
	btn->setTextSize(22);
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::lab, 1, false);

	btn = createWidget(WidgetType::BitmapButton, "Button", "140", "50", "361", "90%")->cast<tgui::BitmapButton>();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->add(btn, "playerUIcrew");
	btn->setText("Crew");
	btn->setTextSize(22);
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::crew, 1, false);

	btn = createWidget(WidgetType::BitmapButton, "Button", "140", "50", "524", "90%")->cast<tgui::BitmapButton>();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->add(btn, "playerUIcraft");
	btn->setText("Craft");
	btn->setTextSize(22);
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::craft, 1, false);

	btn = createWidget(WidgetType::BitmapButton, "Button", "140", "50", "687", "90%")->cast<tgui::BitmapButton>();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->add(btn, "playerUIstorage");
	btn->setText("Storage");
	btn->setTextSize(22);
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::storage, 1, false);

	btn = createWidget(WidgetType::BitmapButton, "Button", "140", "50", "850", "90%")->cast<tgui::BitmapButton>();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->add(btn, "playerUImainStats");
	btn->setText("Stats");
	btn->setTextSize(22);
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::stats, 1, false);

	btn = createWidget(WidgetType::BitmapButton, "Button", "140", "50", "1013", "90%")->cast<tgui::BitmapButton>();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->add(btn, "playerUIhangar");
	btn->setText("Hangar");
	btn->setTextSize(22);
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::hangar, 1, false);

	//create buttons and some other stuff on main adventure interface

	btn = createWidget(WidgetType::BitmapButton, "Button", "120", "120", "1800", "720")->cast<tgui::BitmapButton>();
	btn->setText("Logs");
	btn->setTextSize(22);
	gEnv->game.adventureGUI.add(btn);

	btn = createWidget(WidgetType::BitmapButton, "Button", "120", "120", "1800", "840")->cast<tgui::BitmapButton>();
	btn->setText("Map");
	btn->setTextSize(22);
	btn->connect("MouseReleased", openMap);
	gEnv->game.adventureGUI.add(btn);

	btn = createWidget(WidgetType::BitmapButton, "Button", "120", "120", "1800", "960")->cast<tgui::BitmapButton>();
	btn->setText("Ship");
	btn->setTextSize(22);
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::ship, 0, false);
	gEnv->game.adventureGUI.add(btn);

	btn = createWidget(WidgetType::BitmapButton, "Button", "120", "120", "1800", "0")->cast<tgui::BitmapButton>();
	btn->setText("Menu");
	btn->setTextSize(22);
	btn->connect("MouseReleased", createPauseMenu);
	gEnv->game.adventureGUI.add(btn);

	tgui::ProgressBar::Ptr bar = createWidget(WidgetType::ProgressBar, "ProgressBar", "300", "30", "1480", "960")->cast<tgui::ProgressBar>();
	bar->setMinimum(0);
	bar->setMaximum(gEnv->game.player.ship->hull.total);
	bar->setValue(gEnv->game.player.ship->hull.current);
	bar->setText("Hull: " 
					+ std::to_string((int)gEnv->game.player.ship->hull.current)
					+ "/"
					+ std::to_string((int)gEnv->game.player.ship->hull.total));
	gEnv->game.adventureGUI.add(bar);

	// filter components
	tgui::ComboBox::Ptr comboBox = tgui::ComboBox::create();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->add(comboBox, "comboBoxFilter");
	comboBox->setRenderer(gEnv->globalTheme.getRenderer("ComboBox"));
	comboBox->setSize(250, 30);
	comboBox->setPosition("50%", "5%");
	comboBox->addItem(L"No filter");
	comboBox->addItem(L"Modules");
	comboBox->addItem(L"Equipment");
	comboBox->setSelectedItem(L"No filter");
	comboBox->connect("ItemSelected", filterCategoryFieldChanged);

	updateCategoryFilters();

	tgui::EditBox::Ptr editBox = tgui::EditBox::create();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->add(editBox, "editBoxFilter");
	editBox->setRenderer(gEnv->globalTheme.getRenderer("EditBox"));
	editBox->setSize(250, 30);
	editBox->setTextSize(18);
	editBox->setPosition("5%", "5%");
	editBox->setDefaultText("Search");
	editBox->connect("TextChanged", filterSearchFieldChanged);

	buildShipStats();
	BuildPlanPanel();
	createShipModulePriorityPanel();

}



void updateShipMenuUIState(shipMenu::ShipMenu state, int whereCalled, bool openShop) // whereCalled - 0 для кнопок в нижнем правом углу экрана, 1 для кнопок на панели интерфейса
{
	if (gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse") != NULL) gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse"));
	if (gEnv->game.player.pickedItem != NULL && !gEnv->game.ui.shiftedItem)
	{
		gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.pickedItem;
	}
	else if (gEnv->game.player.pickedItem != NULL && gEnv->game.ui.shiftedItem)
	{
		if (gEnv->game.ui.shiftedItemTakedAll)
		{
			gEnv->game.player.inventory[gEnv->game.ui.shiftedItemStartId] = gEnv->game.player.pickedItem;
		}
		else
		{
			static_cast<ItemResource*>(gEnv->game.player.inventory[gEnv->game.ui.shiftedItemStartId])->count += static_cast<ItemResource*>(gEnv->game.player.pickedItem)->count;
			updateInventoryCell(gEnv->game.player.pickedItemInvId);
		}
	}
	gEnv->game.player.pickedItem = NULL;
	gEnv->game.player.pickedItemInvId = -1;
	gEnv->game.player.pickedLocalInventory = -1;
	disableAllAdventureUI();
	if (whereCalled == 0)
	{
		gEnv->game.player.shipMenu = shipMenu::null;
		gEnv->game.adventureUI.isInventoryOpen = !gEnv->game.adventureUI.isInventoryOpen;
	}
	if (openShop) gEnv->game.adventureUI.isInventoryOpen = true;
	if (!gEnv->game.adventureUI.isInventoryOpen && !openShop)
		return;
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel"), true);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel"), true);
	gEnv->game.player.shipMenu = state;

	switch (gEnv->game.player.shipMenu)
	{
	case shipMenu::ship:
		updateShipValues(gEnv->game.player.ship);
		buildShipStats();
		//module
		//UpdateInventoryUI();
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel"), true);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel"), true);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel"), true);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel"), true);
		break;
	case shipMenu::craft:
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel"), true);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel"), true);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("PlanPanel"), true);
		break;
	case shipMenu::crew:
		gEnv->game.ui.puistate = PUIState::defaultState;
		ChangePersonPanelsState(gEnv->game.ui.puistate);
		break;
	case shipMenu::hangar:
		break;
	case shipMenu::lab:
		break;
	case shipMenu::stats:
		break;
	case shipMenu::storage:
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel"), true);
		if (openShop) enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop"), true);
		break;
	case shipMenu::null:
		break;
	default:
		break;
	}
	updateCategoryFilters();
	ApplyDefaultFilterToInventoryPanel();
	RebuildInventoryGridPanel();
}

void disableAllAdventureUI()
{
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel"), false);
	for (int i = 0; i < gEnv->game.player.crew.characters.size(); i++)
	{
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(i)), false);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(i)), false);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("PersonFirstSkillTree" + std::to_string(i)), false);
		enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("NamePointsPanel" + std::to_string(i)), false);
	}
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("PlanPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("PanelChangePersonState"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel"), false);
	enableWidget(gEnv->game.adventureGUI.get<tgui::Panel>("adventureShop"), false);
}

void updateCategoryFilters()
{

	// clear

	auto p = gEnv->game.adventureGUI.get<tgui::ComboBox>("comboBoxFilter");
	p->removeAllItems();

	auto t = gEnv->game.player.shipMenu;

	p->addItem(GetString("No filter"), "No filter");
	p->setSelectedItem(GetString("No filter"));
	


	switch (t)
	{
	case shipMenu::null:
		break;
	case shipMenu::ship:
		p->addItem(GetString("Primary weapon"), "Primary weapon");
		p->addItem(GetString("Secondary weapon"), "Secondary weapon");
		p->addItem(GetString("Engine"), "Engine");
		p->addItem(GetString("Hyperdrive"), "Hyperdrive");
		p->addItem(GetString("Core"), "Core");
		p->addItem(GetString("System"), "System");
		p->addItem(GetString("Universal"), "Universal");
		break;
	case shipMenu::lab:
		break;
	case shipMenu::crew:
		break;
	case shipMenu::craft:
		break;
	case shipMenu::storage:
		break;
	case shipMenu::stats:
		break;
	case shipMenu::hangar:

		break;
	default:
		break;
	}

}

//this not works yet :) 
void createPauseMenu()
{
	//tgui::Button::Ptr btn = tgui::Button::create();
	//btn->setPosition(900, 450);
	//btn->setSize(120, 120);
	//btn->setText("Hello");
	//btn->setTextSize(22);
	//btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	//gEnv->game.adventureGUI.add(btn);
}



void showItemsReward(std::vector<Item*> items)
{
	gEnv->game.adventureGUI.add(createWidget(WidgetType::Panel, "Panel", "700", "500", "30%", "15%"), "rewardPanel");

	int i = 0;
	for (auto item : items)
	{
		tgui::Button::Ptr button = createWidget(WidgetType::BitmapButton, "Button", "200", "50", "(&.width - width) / 2", "25" + std::to_string(i))->cast<tgui::Button>();
		button->setText(item->name);
		gEnv->game.adventureGUI.get<tgui::Panel>("rewardPanel")->add(button);
		applyRewardTooltip(item);
		button->setToolTip(item->tooltipDescription);

		i += 75;
	}

	tgui::Button::Ptr exit = createWidget(WidgetType::BitmapButton, "Button", "200", "50", "70%", "88%" + std::to_string(i))->cast<tgui::Button>();
	exit->connect("MouseReleased", closeRewardWindow);
	exit->setText("Snova huina, skip");
	gEnv->game.adventureGUI.get<tgui::Panel>("rewardPanel")->add(exit);
}

void applyRewardTooltip(Item *item)
{
	if (item != NULL)
	{
		switch (item->itemType)
		{
		case itemType::module:
			createModuleTooltip(static_cast<Module*>(item));
			tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
		}
	}
}

void closeRewardWindow()
{
	gEnv->game.adventureGUI.get<tgui::Panel>("rewardPanel")->removeAllWidgets();
	gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("rewardPanel"));
}