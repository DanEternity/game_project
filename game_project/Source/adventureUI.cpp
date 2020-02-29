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
	tgui::Panel::Ptr adventureUIPanel = tgui::Panel::create();
	adventureUIPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
	adventureUIPanel->setSize(1200, 675);
	adventureUIPanel->setPosition("20%", "15%");
	gEnv->game.adventureGUI.add(adventureUIPanel, "adventuryUIInventoryMainPanel");
	adventureUIPanel->setEnabled(false);
	adventureUIPanel->setVisible(false);

	tgui::Button::Ptr btn = tgui::Button::create();
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
	btn->connect("MouseReleased", adventureUIChangeState, AdventureUIInventoryStateNamespace::AdventureUIInventoryState::characterInventory);
	gEnv->game.adventureGUI.add(btn);

	btn = tgui::Button::create();
	btn->setPosition(1800, 960);
	btn->setSize(120, 120);
	btn->setText("Ship");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	btn->connect("MouseReleased", adventureUIChangeState, AdventureUIInventoryStateNamespace::AdventureUIInventoryState::shipInventory);
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

}

void adventureUIChangeState(AdventureUIInventoryStateNamespace::AdventureUIInventoryState state)
{
	gEnv->game.adventureGUI.get<tgui::Panel>("adventuryUIInventoryMainPanel")->setEnabled(true);
	gEnv->game.adventureGUI.get<tgui::Panel>("adventuryUIInventoryMainPanel")->setVisible(true);
	gEnv->game.adventureUI.isInventoryOpen = !gEnv->game.adventureUI.isInventoryOpen;
	if (gEnv->game.adventureUI.isInventoryOpen)
	{
		switch (state)
		{
		case AdventureUIInventoryStateNamespace::AdventureUIInventoryState::shipInventory:
			gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setEnabled(true);
			gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setVisible(true);
			gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setEnabled(true);
			gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setVisible(true);
			break;
		case AdventureUIInventoryStateNamespace::AdventureUIInventoryState::characterInventory:
			gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setEnabled(true);
			gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setVisible(true);
			gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setEnabled(true);
			gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setVisible(true);
			break;
		}
		
	}
	else
	{
		gEnv->game.adventureGUI.get<tgui::Panel>("adventuryUIInventoryMainPanel")->setEnabled(false);
		gEnv->game.adventureGUI.get<tgui::Panel>("adventuryUIInventoryMainPanel")->setVisible(false);
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setEnabled(false);
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setVisible(false);
		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setEnabled(false);
		gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel")->setVisible(false);
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setEnabled(false);
		gEnv->game.adventureGUI.get<tgui::Panel>("PersonSchemeEquipPanel")->setVisible(false);
	}
}

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