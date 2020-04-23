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
	
	gEnv->game.player.inventory.resize(50, nullptr);

	// create some stuff in subPanel inventories
	/*
	// create and fill inventories
	

	Module * megaSuperModule = new Module(L"MegaKomp", moduleType::system, 
										moduleSlot::ModuleSlotType::system,
										moduleSlot::ModuleSlotSize::medium);

	StatModEffect* effect = new StatModEffect(targetType::ship, statNames::powerSupply, 50, 0, 0, 0);
	megaSuperModule->effects.push_back(effect);

	gEnv->game.player.inventory[10] = megaSuperModule;

	gEnv->game.player.inventory[2] = new Module();
	gEnv->game.player.inventory[2]->name = L"roflanEbalo";
	gEnv->game.player.inventory[2]->itemType = itemType::module;
	static_cast<Module*>(gEnv->game.player.inventory[2])->slot = moduleSlot::engine;
	static_cast<Module*>(gEnv->game.player.inventory[2])->moduleType = moduleType::system;
	static_cast<Module*>(gEnv->game.player.inventory[2])->powerSupply = 50;
	StatModEffect * sme1 = new StatModEffect();
	sme1->targetType = targetType::ship;
	sme1->statName = statNames::hull;
	sme1->p_add = 1000;
	static_cast<Module*>(gEnv->game.player.inventory[2])->effects.push_back(sme1);

	// Basic core
	// type: Core
	// +100 power supply +100 hull +2.5 high power supply


	megaSuperModule = new Module(L"Basic Core", moduleType::system,
		moduleSlot::ModuleSlotType::core,
		moduleSlot::ModuleSlotSize::medium);
	megaSuperModule->powerPriority = 0;
	effect = new StatModEffect(targetType::ship, statNames::powerSupply, 100, 0, 0, 0);
	megaSuperModule->effects.push_back(effect);

	effect = new StatModEffect(targetType::ship, statNames::hull, 100, 0, 0, 0);
	megaSuperModule->effects.push_back(effect);

	effect = new StatModEffect(targetType::ship, statNames::highPowerSupply, 2.5f, 0, 0, 0);
	megaSuperModule->effects.push_back(effect);

	gEnv->game.player.inventory[20] = megaSuperModule;

	// Basic engine
	// Type engine; Required 35 power
	// +10 mobility +3.5% mobility +50 hull +4 evasion

	megaSuperModule = new Module(L"Basic engine", moduleType::system,
		moduleSlot::ModuleSlotType::engine,
		moduleSlot::ModuleSlotSize::medium);
	megaSuperModule->powerPriority = 5;
	megaSuperModule->powerSupply = 35;
	effect = new StatModEffect(targetType::ship, statNames::mobility, 10, 0.035, 0, 0);
	megaSuperModule->effects.push_back(effect);

	effect = new StatModEffect(targetType::ship, statNames::hull, 50, 0, 0, 0);
	megaSuperModule->effects.push_back(effect);

	effect = new StatModEffect(targetType::ship, statNames::evasion, 4, 0, 0, 0);
	megaSuperModule->effects.push_back(effect);

	gEnv->game.player.inventory[21] = megaSuperModule;

	// Advanced engine
	// Type engine; Required 65 power and 1 high power supply
	// +15 mobility +5% mobility +20 hull +8 evasion

	megaSuperModule = new Module(L"Advanced engine", moduleType::system,
		moduleSlot::ModuleSlotType::engine,
		moduleSlot::ModuleSlotSize::medium);
	megaSuperModule->powerPriority = 5;
	megaSuperModule->powerSupply = 65;
	megaSuperModule->highPowerSupply = 1;
	effect = new StatModEffect(targetType::ship, statNames::mobility, 15, 0.05, 0, 0);
	megaSuperModule->effects.push_back(effect);

	effect = new StatModEffect(targetType::ship, statNames::hull, 20, 0, 0, 0);
	megaSuperModule->effects.push_back(effect);

	effect = new StatModEffect(targetType::ship, statNames::evasion, 8, 0, 0, 0);
	megaSuperModule->effects.push_back(effect);

	gEnv->game.player.inventory[22] = megaSuperModule;

	// Basic system
	// Type engine; Required 25 power 
	// +10% energy +10% high power supply +10% evasion

	megaSuperModule = new Module(L"Basic system", moduleType::system,
		moduleSlot::ModuleSlotType::system,
		moduleSlot::ModuleSlotSize::medium);
	megaSuperModule->powerPriority = 5;
	megaSuperModule->powerSupply = 25;
	effect = new StatModEffect(targetType::ship, statNames::powerSupply, 0, 0.1, 0, 0);
	megaSuperModule->effects.push_back(effect);

	effect = new StatModEffect(targetType::ship, statNames::highPowerSupply, 0, 0.1, 0, 0);
	megaSuperModule->effects.push_back(effect);

	effect = new StatModEffect(targetType::ship, statNames::evasion, 0, 0.1, 0, 0);
	megaSuperModule->effects.push_back(effect);

	gEnv->game.player.inventory[23] = megaSuperModule;

	// basic hyperdrive
	// Type hyperdrive; Required ~max~ power 90;
	// +20 hyper drive power  +1 hyperdrive tier

	megaSuperModule = new Module(L"Basic hyperdrive", moduleType::system,
		moduleSlot::ModuleSlotType::hyperdrive,
		moduleSlot::ModuleSlotSize::medium);
	megaSuperModule->powerPriority = 5;
	megaSuperModule->powerSupply = 90;
	effect = new StatModEffect(targetType::ship, statNames::hyperDrivePower, 20, 0, 0, 0);
	megaSuperModule->effects.push_back(effect);

	effect = new StatModEffect(targetType::ship, statNames::hyperDriveTier, 1, 0, 0, 0);
	megaSuperModule->effects.push_back(effect);

	gEnv->game.player.inventory[24] = megaSuperModule;

	// Rd-1000 Engine
	// Type engine; Required power 200;
	// +100 mobility

	megaSuperModule = new Module(L"Rd-1000 Engine", moduleType::system,
		moduleSlot::ModuleSlotType::engine,
		moduleSlot::ModuleSlotSize::medium);
	megaSuperModule->powerPriority = 5;
	megaSuperModule->powerSupply = 200;
	effect = new StatModEffect(targetType::ship, statNames::mobility, 100, 0, 0, 0);
	megaSuperModule->effects.push_back(effect);

	gEnv->game.player.inventory[25] = megaSuperModule;

	// V-1 Shield generator
	// Type universal; Required power 40;
	// +100 shield +10 shield regen 5 shield physical def

	megaSuperModule = new Module(L"V-1 Shield generator", moduleType::system,
		moduleSlot::ModuleSlotType::universal,
		moduleSlot::ModuleSlotSize::medium);
	megaSuperModule->powerPriority = 5;
	megaSuperModule->powerSupply = 40;
	effect = new StatModEffect(targetType::ship, statNames::shield, 100, 0, 0, 0);
	megaSuperModule->effects.push_back(effect);

	effect = new StatModEffect(targetType::ship, statNames::shieldReg, 10, 0, 0, 0);
	megaSuperModule->effects.push_back(effect);

	effect = new StatModEffect(targetType::ship, statNames::shieldResist, 5, 0, 0, 0);
	megaSuperModule->effects.push_back(effect);

	gEnv->game.player.inventory[26] = megaSuperModule;


	gEnv->game.player.inventory[7] = new Module();
	static_cast<Module*>(gEnv->game.player.inventory[7])->slot = moduleSlot::hyperdrive;
	gEnv->game.player.inventory[7]->name = L"roflanContent";
	gEnv->game.player.inventory[5] = new Module();
	static_cast<Module*>(gEnv->game.player.inventory[5])->slot = moduleSlot::engine;
	gEnv->game.player.inventory[5]->name = L"roflanGorit";
	*/
	gEnv->game.player.inventory[0] = new Equipment();
	gEnv->game.player.inventory[0]->name = L"roflanTelo";
	static_cast<Equipment*>(gEnv->game.player.inventory[0])->equipmentSlotType = equipmentSlot::body;

	gEnv->game.player.inventory[11] = new Equipment();
	gEnv->game.player.inventory[11]->name = L"roflanBody";
	static_cast<Equipment*>(gEnv->game.player.inventory[11])->equipmentSlotType = equipmentSlot::body;

	BuildInventoryUI(10);


	/* INITIALIZE SHIP SLOTS */
	gEnv->game.player.ship->slots.resize(8, moduleSlot::ModuleSlot());
	gEnv->game.player.ship->slots[0].type = moduleSlot::core;
	gEnv->game.player.ship->slots[1].type = moduleSlot::hyperdrive;
	gEnv->game.player.ship->slots[2].type = moduleSlot::engine;
	gEnv->game.player.ship->slots[3].type = moduleSlot::system;
	gEnv->game.player.ship->slots[4].type = moduleSlot::primaryWeapon;
	gEnv->game.player.ship->slots[5].type = moduleSlot::universal;
	gEnv->game.player.ship->slots[6].type = moduleSlot::universal;
	gEnv->game.player.ship->slots[7].type = moduleSlot::universal;
	
	gEnv->game.player.ship->modules.resize(8, nullptr);

	/* INITIALIZE SHIP BASE MODULES */ /*
	gEnv->game.player.ship->modules.resize(8, nullptr);
	gEnv->game.player.ship->modules[0] = new Module();
	gEnv->game.player.ship->modules[0]->name = L"roflanPomoika";
	gEnv->game.player.ship->modules[0]->slot = moduleSlot::core;
	gEnv->game.player.ship->modules[0]->itemType = itemType::module;
	gEnv->game.player.ship->modules[0]->powerPriority = 0;

	gEnv->game.player.ship->modules[1] = new Module();
	gEnv->game.player.ship->modules[1]->name = L"roflanVebenya";
	gEnv->game.player.ship->modules[1]->slot = moduleSlot::hyperdrive;
	gEnv->game.player.ship->modules[1]->itemType = itemType::module;

	gEnv->game.player.ship->modules[2] = new Module();
	gEnv->game.player.ship->modules[2]->name = L"roflanGorim";
	gEnv->game.player.ship->modules[2]->slot = moduleSlot::engine;
	gEnv->game.player.ship->modules[2]->itemType = itemType::module;

	gEnv->game.player.ship->modules[3] = new Module();
	gEnv->game.player.ship->modules[3]->name = L"roflanCompukter";
	gEnv->game.player.ship->modules[3]->slot = moduleSlot::system;
	gEnv->game.player.ship->modules[3]->itemType = itemType::module;

	gEnv->game.player.ship->modules[4] = new Module();
	gEnv->game.player.ship->modules[4]->name = L"roflanStrelyai";
	gEnv->game.player.ship->modules[4]->slot = moduleSlot::primaryWeapon;
	gEnv->game.player.ship->modules[4]->itemType = itemType::module;

	*/

	BuildShipSchemeUI(50);

	//gEnv->game.player.crew = new Crew();

	//gEnv->game.player.crew->shipCrew.resize(5, nullptr);
	//gEnv->game.player.crew->shipCrew[0] = new Person();
	//gEnv->game.player.crew->shipCrew[0]->personEquipment.resize(7, nullptr);

	gEnv->game.player.crew.characters.push_back(new Character(L"Person 1"));
	gEnv->game.player.crew.characters[0]->role = characterRole::programmer;

	gEnv->game.player.crew.characters[0]->equipment[0] = new Equipment(L"Base Helmet", equipmentSlot::head);

	StatModEffect * sme10 = new StatModEffect();
	sme10->targetType = targetType::character;
	sme10->statName = statNames::characterHealth;
	sme10->p_add = 60;
	gEnv->game.player.crew.characters[0]->equipment[0]->effects.push_back(sme10);

	gEnv->game.player.crew.characters.push_back(new Character(L"Person 2"));

	BuildSchemeChooseCharacter();
	BuildSchemeRoles();
	BuildPersonSchemeUI(50, 0);
	BuildPersonSchemeUI(50, 1);
	BuildStatPersonScreen(0);
	BuildStatPersonScreen(1);
	BuildPersonSkillTree(0);
	BuildPersonSkillTree(1);
	BuildPanelChangePersonState();
	CreateInventoryGridPanel(10);

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

void openMap()
{
	disableAllAdventureUI();
	gEnv->game.adventureUI.isMapOpen = !gEnv->game.adventureUI.isMapOpen;
	if (gEnv->game.adventureUI.isMapOpen)
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->setVisible(true);
	}


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

void disableAllAdventureUI()
{
	gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("choosePersonPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setVisible(false);
	for (int i = 0; i < gEnv->game.player.crew.characters.size(); i++)
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(i))->setEnabled(false);
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel" + std::to_string(i))->setVisible(false);
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(i))->setEnabled(false);
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonStatScreen" + std::to_string(i))->setVisible(false);		
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonFirstSkillTree" + std::to_string(i))->setEnabled(false);
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonFirstSkillTree" + std::to_string(i))->setVisible(false);
		
	}
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemePersonRoles")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("PlanPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("PlanPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("PanelChangePersonState")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("PanelChangePersonState")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("globalMapPanel")->setVisible(false);
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

void giveIconToItem(Item * item)
{
	switch (item->itemType)
	{
	case itemType::module:
		switch (static_cast<Module*>(item)->slot)
		{
		case moduleSlot::ModuleSlotType::core:
			item->icon = &gEnv->modelDB[L"itemCore"]->tex;
			break;
		case moduleSlot::ModuleSlotType::engine:
			item->icon = &gEnv->modelDB[L"itemEngine"]->tex;
			break;
		case moduleSlot::ModuleSlotType::hyperdrive:
			item->icon = &gEnv->modelDB[L"itemHyperdrive"]->tex;
			break;
		case moduleSlot::ModuleSlotType::system:
			item->icon = &gEnv->modelDB[L"itemSystem"]->tex;
			break;
		default:
			item->icon = &gEnv->modelDB[L"itemDefault"]->tex;
		}
		break;
	}
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