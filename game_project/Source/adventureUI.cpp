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
	gEnv->game.adventureGUI.add(btn);

	btn = tgui::Button::create();
	btn->setPosition(1800, 840);
	btn->setSize(120, 120);
	btn->setText("Characters");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	btn->connect("MouseReleased", updateShipMenuUIState, shipMenu::crew, 0);
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
	bar->setMaximum(100);
	bar->setValue(60);
	bar->setText("Hull: 600/1000");
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
	
	// create some stuff in subPanel inventories

	// create and fill inventories
	gEnv->game.player.inventory.resize(50, nullptr);

	gEnv->game.player.inventory[2] = new Module();
	gEnv->game.player.inventory[2]->name = L"roflanEbalo";
	gEnv->game.player.inventory[2]->itemType = itemType::module;
	static_cast<Module*>(gEnv->game.player.inventory[2])->slot = moduleSlot::engine;

	gEnv->game.player.inventory[7] = new Module();
	static_cast<Module*>(gEnv->game.player.inventory[7])->slot = moduleSlot::hyperdrive;
	gEnv->game.player.inventory[7]->name = L"roflanContent";
	gEnv->game.player.inventory[5] = new Module();
	static_cast<Module*>(gEnv->game.player.inventory[5])->slot = moduleSlot::engine;
	gEnv->game.player.inventory[5]->name = L"roflanGorit";

	gEnv->game.player.inventory[0] = new Equipment();
	gEnv->game.player.inventory[0]->name = L"roflanTelo";
	static_cast<Equipment*>(gEnv->game.player.inventory[0])->equipmentSlotType = equipmentSlot::body;

	gEnv->game.player.inventory[11] = new Equipment();
	gEnv->game.player.inventory[11]->name = L"roflanBody";
	static_cast<Equipment*>(gEnv->game.player.inventory[11])->equipmentSlotType = equipmentSlot::body;

	BuildInventoryUI(10);

	gEnv->game.player.ship = new Ship();

	/* INITIALIZE SHIP SLOTS */
	gEnv->game.player.ship->slots.resize(5, moduleSlot::ModuleSlot());
	gEnv->game.player.ship->slots[0].type = moduleSlot::core;
	gEnv->game.player.ship->slots[1].type = moduleSlot::hyperdrive;
	gEnv->game.player.ship->slots[2].type = moduleSlot::engine;
	gEnv->game.player.ship->slots[3].type = moduleSlot::system;
	gEnv->game.player.ship->slots[4].type = moduleSlot::primaryWeapon;

	/* INITIALIZE SHIP BASE MODULES */
	gEnv->game.player.ship->modules.resize(5, nullptr);
	gEnv->game.player.ship->modules[0] = new Module();
	gEnv->game.player.ship->modules[0]->name = L"roflanPomoika";
	gEnv->game.player.ship->modules[0]->slot = moduleSlot::core;
	gEnv->game.player.ship->modules[0]->itemType = itemType::module;

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

	BuildShipSchemeUI(50);

	//gEnv->game.player.crew = new Crew();

	//gEnv->game.player.crew->shipCrew.resize(5, nullptr);
	//gEnv->game.player.crew->shipCrew[0] = new Person();
	//gEnv->game.player.crew->shipCrew[0]->personEquipment.resize(7, nullptr);

	gEnv->game.player.crew.characters.push_back(new Character());
	gEnv->game.player.crew.characters[0]->name = L"roflanDaun";
	gEnv->game.player.crew.characters[0]->slot.resize(7, equipmentSlot::head);
	gEnv->game.player.crew.characters[0]->slot[0] = equipmentSlot::head;
	gEnv->game.player.crew.characters[0]->slot[1] = equipmentSlot::body;
	gEnv->game.player.crew.characters[0]->slot[2] = equipmentSlot::arms;
	gEnv->game.player.crew.characters[0]->slot[3] = equipmentSlot::legs;
	gEnv->game.player.crew.characters[0]->slot[4] = equipmentSlot::universal;
	gEnv->game.player.crew.characters[0]->slot[5] = equipmentSlot::universal;
	gEnv->game.player.crew.characters[0]->slot[6] = equipmentSlot::universal;
	gEnv->game.player.crew.characters[0]->equipment.resize(7, nullptr);
	gEnv->game.player.crew.characters[0]->equipment[0] = new Equipment();
	gEnv->game.player.crew.characters[0]->equipment[0]->name = L"roflanBoshka";
	gEnv->game.player.crew.characters[0]->equipment[0]->equipmentSlotType = equipmentSlot::head;

	BuildPersonSchemeUI(50, 0);
	CreateInventoryGridPanel(10);

	// filter components
	tgui::ComboBox::Ptr comboBox = tgui::ComboBox::create();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->add(comboBox, "comboBoxFilter");
	comboBox->setRenderer(gEnv->globalTheme.getRenderer("ComboBox"));
	comboBox->setSize(150, 30);
	comboBox->setPosition("5%", "5%");
	comboBox->addItem(L"No filter");
	comboBox->addItem(L"Modules");
	comboBox->addItem(L"Equipment");
	comboBox->setSelectedItem(L"No filter");
	comboBox->connect("ItemSelected", filterCategoryFieldChanged);

	updateCategoryFilters();

	tgui::EditBox::Ptr editBox = tgui::EditBox::create();
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->add(editBox, "editBoxFilter");
	editBox->setRenderer(gEnv->globalTheme.getRenderer("EditBox"));
	editBox->setSize(150, 30);
	editBox->setTextSize(18);
	editBox->setPosition("40%", "5%");
	editBox->setDefaultText("Search");
	editBox->connect("TextChanged", filterSearchFieldChanged);
}



void updateShipMenuUIState(shipMenu::ShipMenu state, int whereCalled) // whereCalled - 0 ��� ������ � ������ ����� ���� ������, 1 ��� ������ �� ������ ����������
{
	disableAllAdventureUI();
	if (whereCalled == 0)
		gEnv->game.adventureUI.isInventoryOpen = !gEnv->game.adventureUI.isInventoryOpen;
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
		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setVisible(true);
		break;
	case shipMenu::craft:
		break;
	case shipMenu::crew:
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setVisible(true);
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
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->setVisible(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setEnabled(false);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->setVisible(false);
}

//this function called when we open inventory
//void adventureUIChangeState(AdventureUIInventoryStateNamespace::AdventureUIInventoryState state)
//{
//	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->setEnabled(true);
//	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->setVisible(true);
//	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->setEnabled(true);
//	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->setVisible(true);
//	gEnv->game.adventureUI.isInventoryOpen = !gEnv->game.adventureUI.isInventoryOpen;
//
//	if (gEnv->game.adventureUI.isInventoryOpen)
//	{
//		switch (state)
//		{
//		case AdventureUIInventoryStateNamespace::AdventureUIInventoryState::shipInventory:
//			gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setEnabled(true);
//			gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setVisible(true);
//			gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setEnabled(true);
//			gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setVisible(true);
//			gEnv->game.player.shipMenu = shipMenu::ship;
//			printf("Ship menu opened\n");
//			break;
//		case AdventureUIInventoryStateNamespace::AdventureUIInventoryState::characterInventory:
//			gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setEnabled(true);
//			gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setVisible(true);
//			gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setEnabled(true);
//			gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setVisible(true);
//			gEnv->game.player.shipMenu = shipMenu::crew;
//			printf("Crew menu opened\n");
//			break;
//		}
//		
//	}
//	else
//	{
//		gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->setEnabled(false);
//		gEnv->game.adventureGUI.get<tgui::Panel>("playerUIMainPanel")->setVisible(false);
//		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setEnabled(false);
//		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setVisible(false);
//		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setEnabled(false);
//		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setVisible(false);
//		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setEnabled(false);
//		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setVisible(false);
//		gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->setEnabled(false);
//		gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->setVisible(false);
//	}
//
//	RebuildInventoryGridPanel();
//
//}
//
//
////this function called when we click  button on main interface panel 
//void adventureUIInventorySpecialButtons(AdventureUIInventoryStateNamespace::AdventureUIInventoryState newState)
//{
//	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setEnabled(false);
//	gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setVisible(false);
//	gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setEnabled(false);
//	gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setVisible(false);
//
//	switch (newState)
//	{
//	case AdventureUIInventoryStateNamespace::AdventureUIInventoryState::characterInventory:
//		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setEnabled(true);
//		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setVisible(true);
//		gEnv->game.player.shipMenu = shipMenu::crew;
//		printf("Crew menu opened\n");
//
//		break;
//	case AdventureUIInventoryStateNamespace::AdventureUIInventoryState::shipInventory:
//		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setEnabled(true);
//		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setVisible(true);
//		gEnv->game.player.shipMenu = shipMenu::ship;
//		printf("Ship menu opened\n");
//		break;
//	case AdventureUIInventoryStateNamespace::AdventureUIInventoryState::storageInventory:
//		gEnv->game.player.shipMenu = shipMenu::storage;
//		printf("Storage menu opened\n");
//		break;
//	}
//
//	RebuildInventoryGridPanel();
//}

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