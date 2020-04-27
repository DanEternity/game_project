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


	//minimap

	tgui::Panel::Ptr minimap = tgui::Panel::create();
	minimap->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
	minimap->setPosition(10, 700);
	minimap->setSize(400, 300);
	gEnv->game.adventureGUI.add(minimap, "minimap");

	//create main interface panel

	tgui::Panel::Ptr adventureUIPanel = tgui::Panel::create();
	adventureUIPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
	adventureUIPanel->setSize(1200, 675);
	adventureUIPanel->setPosition("20%", "15%");
	gEnv->game.adventureGUI.add(adventureUIPanel, "playerUIMainPanel");
	adventureUIPanel->setEnabled(false);
	adventureUIPanel->setVisible(false);

	tgui::Panel::Ptr adventureUISubPanel = tgui::Panel::create();
	adventureUISubPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));
	adventureUISubPanel->setSize(1176, 590);
	adventureUISubPanel->setPosition("1%", "1%");
	adventureUIPanel->add(adventureUISubPanel, "playerUISubPanel");
	adventureUISubPanel->setEnabled(false);
	adventureUISubPanel->setVisible(false);

	tgui::Panel::Ptr adventureUIGridSubPanel = tgui::Panel::create();
	adventureUIGridSubPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel3"));
	adventureUIGridSubPanel->setSize(600, 200);
	adventureUIGridSubPanel->setPosition("1%", "65%");
	adventureUISubPanel->add(adventureUIGridSubPanel, "playerUIGridSubPanel");
	adventureUIGridSubPanel->setEnabled(false);
	adventureUIGridSubPanel->setVisible(false);

	tgui::ScrollablePanel::Ptr shipStatsPanel = tgui::ScrollablePanel::create();
	shipStatsPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel3"));
	shipStatsPanel->setSize(450, 570);
	shipStatsPanel->setPosition("60%", "2%");
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(shipStatsPanel, "shipStatsPanel");
	shipStatsPanel->setEnabled(false);
	shipStatsPanel->setVisible(false);

	// create buttons on main interface panel

	tgui::Button::Ptr btn = tgui::Button::create();
	btn->setPosition(35, "90%");
	btn->setSize(140, 50);
	btn->setText("Ship");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	adventureUIPanel->add(btn, "playerUIship");
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::ship, 1);

	btn = tgui::Button::create();
	btn->setPosition(198, "90%");
	btn->setSize(140, 50);
	btn->setText("Lab");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	adventureUIPanel->add(btn, "playerUIlab");
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::lab, 1);

	btn = tgui::Button::create();
	btn->setPosition(361, "90%");
	btn->setSize(140, 50);
	btn->setText("Crew");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	adventureUIPanel->add(btn, "playerUIcrew");
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::crew, 1);

	btn = tgui::Button::create();
	btn->setPosition(524, "90%");
	btn->setSize(140, 50);
	btn->setText("Craft");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	adventureUIPanel->add(btn, "playerUIcraft");
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::craft, 1);

	btn = tgui::Button::create();
	btn->setPosition(687, "90%");
	btn->setSize(140, 50);
	btn->setText("Storage");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	adventureUIPanel->add(btn, "playerUIstorage");
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::storage, 1);

	btn = tgui::Button::create();
	btn->setPosition(850, "90%");
	btn->setSize(140, 50);
	btn->setText("Stats");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	adventureUIPanel->add(btn, "playerUImainStats");
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::stats, 1);

	btn = tgui::Button::create();
	btn->setPosition(1013, "90%");
	btn->setSize(140, 50);
	btn->setText("Hangar");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	adventureUIPanel->add(btn, "playerUIhangar");
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::hangar, 1);

	//create buttons and some other stuff on main adventure interface

	btn = tgui::Button::create();
	btn->setPosition(1800, 600);
	btn->setSize(120, 120);
	btn->setText("Logs");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	gEnv->game.adventureGUI.add(btn);

	btn = tgui::Button::create();
	btn->setPosition(1800, 720);
	btn->setSize(120, 120);
	btn->setText("Map");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	btn->connect("MouseReleased", openMap);
	gEnv->game.adventureGUI.add(btn);

	btn = tgui::Button::create();
	btn->setPosition(1800, 840);
	btn->setSize(120, 120);
	btn->setText("Characters");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::crew, 1);
	gEnv->game.adventureGUI.add(btn);

	btn = tgui::Button::create();
	btn->setPosition(1800, 960);
	btn->setSize(120, 120);
	btn->setText("Ship");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::ship, 0);
	gEnv->game.adventureGUI.add(btn);

	btn = tgui::Button::create();
	btn->setPosition(1800, 0);
	btn->setSize(120, 120);
	btn->setText("Menu");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	gEnv->game.adventureGUI.add(btn);
	btn->connect("MouseReleased", createPauseMenu);

	tgui::ProgressBar::Ptr bar = tgui::ProgressBar::create();
	bar->setPosition(1480, 960);
	bar->setSize(300, 30);
	bar->setMinimum(0);
	bar->setMaximum(gEnv->game.player.ship->hull.total);
	bar->setValue(gEnv->game.player.ship->hull.current);
	bar->setText("Hull: " 
					+ std::to_string((int)gEnv->game.player.ship->hull.current)
					+ "/"
					+ std::to_string((int)gEnv->game.player.ship->hull.total));
	bar->setRenderer(gEnv->globalTheme.getRenderer("ProgressBar"));
	gEnv->game.adventureGUI.add(bar);

	bar = tgui::ProgressBar::create();
	bar->setPosition(1480, 1000);
	bar->setSize(300, 30);
	bar->setMinimum(0);
	bar->setMaximum(100);
	bar->setValue(100);
	bar->setText("SD: 250/250");
	bar->setRenderer(gEnv->globalTheme.getRenderer("ProgressBar"));
	gEnv->game.adventureGUI.add(bar);

	bar = tgui::ProgressBar::create();
	bar->setPosition(1480, 1040);
	bar->setSize(300, 30);
	bar->setMinimum(0);
	bar->setMaximum(100);
	bar->setValue(25);
	bar->setText("Fuel: 20/80");
	bar->setRenderer(gEnv->globalTheme.getRenderer("ProgressBar"));
	gEnv->game.adventureGUI.add(bar);

	/* INITIALIZE SHIP SLOTS */

	//gEnv->game.player.crew = new Crew();

	//gEnv->game.player.crew->shipCrew.resize(5, nullptr);
	//gEnv->game.player.crew->shipCrew[0] = new Person();
	//gEnv->game.player.crew->shipCrew[0]->personEquipment.resize(7, nullptr);


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



void updateShipMenuUIState(shipMenu::ShipMenu state, int whereCalled) // whereCalled - 0 для кнопок в нижнем левом углу экрана, 1 для кнопок на панели интерфейса
{
	disableAllAdventureUI();
	gEnv->game.ui.puistate = PUIState::defaultState;
	if (whereCalled == 0)
	{
		gEnv->game.player.shipMenu = shipMenu::null;
		gEnv->game.adventureUI.isInventoryOpen = !gEnv->game.adventureUI.isInventoryOpen;
	}
	if (!gEnv->game.adventureUI.isInventoryOpen)
		return;
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->setEnabled(true);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->setVisible(true);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->setEnabled(true);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->setVisible(true); 
	gEnv->game.player.shipMenu = state;
	switch (gEnv->game.player.shipMenu)
	{
	case shipMenu::ship:
		updateShipValues(gEnv->game.player.ship);
		updateShipStatsScreen();
		//module
		//UpdateInventoryUI();
		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->setVisible(true);
		break;
	case shipMenu::craft:
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("PlanPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("PlanPanel")->setVisible(true);
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
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setVisible(true);
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



void updateCategoryFilters()
{

	// clear

	auto p = gEnv->game.adventureGUI.get<tgui::ComboBox>("comboBoxFilter");
	p->removeAllItems();

	auto t = gEnv->game.player.shipMenu;

	p->addItem(GetString("No filter"), "No filter");
	p->setSelectedItem(GetString("No filter"));

	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{
		gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(i))->setToolTip(NULL);
		gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(i))->disconnectAll("MouseEntered");
	}

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
	tgui::Button::Ptr btn = tgui::Button::create();
	btn->setPosition(900, 450);
	btn->setSize(120, 120);
	btn->setText("Hello");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	gEnv->game.adventureGUI.add(btn);
}



void showItemsReward(std::vector<Item*> items)
{
	tgui::Panel::Ptr rewardPanel = tgui::Panel::create();
	rewardPanel->setSize(700, 500);
	rewardPanel->setPosition("30%", "15%");
	rewardPanel->setRenderer(globalEnviroment->globalTheme.getRenderer("Panel"));
	globalEnviroment->game.adventureGUI.add(rewardPanel, "rewardPanel");

	int i = 0;
	for (auto item : items)
	{
		tgui::Button::Ptr button = tgui::Button::create();
		button->setSize(200, 50);
		button->setPosition("(&.width - width) / 2", 25 + i);
		button->setText(item->name);
		button->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		rewardPanel->add(button);
		applyRewardTooltip(item);
		button->setToolTip(item->tooltipDescription);

		i += 75;
	}

	tgui::Button::Ptr exit = tgui::Button::create();
	exit->setSize(200, 50);
	exit->setPosition("70%", "88%");
	exit->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	exit->connect("MouseReleased", closeRewardWindow);
	exit->setText("Snova huina, skip");
	rewardPanel->add(exit);
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