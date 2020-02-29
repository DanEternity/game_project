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
	btn->connect("MouseReleased", adventureUIChangeState, adventureUIState::AdventureUIInventoryState::characterInventory);
	gEnv->game.adventureGUI.add(btn);

	btn = tgui::Button::create();
	btn->setPosition(1800, 960);
	btn->setSize(120, 120);
	btn->setText("Ship");
	btn->setTextSize(22);
	btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	btn->connect("MouseReleased", adventureUIChangeState, adventureUIState::AdventureUIInventoryState::shipInventory);
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
}

void adventureUIChangeState(adventureUIState::AdventureUIInventoryState state)
{
	
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