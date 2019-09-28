#include "mainMenu.h"
#include "enviroment.h"

void updateMainMenu()
{
	if (gEnv->game.mainMenu.menuDrawRequired)
	{
		gEnv->globalGui.draw();
	}

	if (gEnv->game.mainMenu.widgetDisable)
	{
		for (const auto& widget : gEnv->game.mainMenu.mainMenuWidgets)
		{
			widget->setVisible(false);
			widget->setEnabled(false);
		}
		gEnv->game.mainMenu.widgetDisable = false;
	}
}

void disableAllMainMenuWidgets()
{
	for (const auto& widget : gEnv->game.mainMenu.mainMenuWidgets)
	{
		widget->setVisible(false);
		widget->setEnabled(false);
	}
}


void mainMenuChangeState()
{
	disableAllMainMenuWidgets();
	switch (gEnv->game.mainMenu.active)
	{
		case menuState::mainMenu:
			gEnv->globalGui.get<tgui::Button>("startButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("startButton")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>("exitButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("exitButton")->setVisible(true);
			break;
		case menuState::optionsActive:
			break;
		case menuState::exitActive:
			gEnv->globalGui.get<tgui::Button>("startButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("startButton")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>("exitButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("exitButton")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>("exitButtonYes")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("exitButtonYes")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>("exitButtonNo")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("exitButtonNo")->setVisible(true);
			break;
		default:
			break;
	}
	
}


void createMenuButtons()
{
	tgui::Button::Ptr startButton = tgui::Button::create();
	tgui::Button::Ptr exitButton = tgui::Button::create();
	tgui::Button::Ptr exitButtonYes = tgui::Button::create();
	tgui::Button::Ptr exitButtonNo = tgui::Button::create();
	gEnv->globalGui.add(startButton, "startButton");
	gEnv->globalGui.add(exitButton, "exitButton");
	gEnv->globalGui.add(exitButtonYes, "exitButtonYes");
	gEnv->globalGui.add(exitButtonNo, "exitButtonNo");
	startButton->setText("Start");
	exitButton->setText("Exit");
	gEnv->game.mainMenu.mainMenuWidgets.push_back(startButton);
	gEnv->game.mainMenu.mainMenuWidgets.push_back(exitButton);
	int i = 0;
	for (const auto& widget : gEnv->game.mainMenu.mainMenuWidgets)
	{
		widget->setSize(300, 150);
		widget->setPosition("(&.size - size) / 2", 400 + i * 200);
		widget->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		i++;
	}
	gEnv->game.mainMenu.mainMenuWidgets.push_back(exitButtonYes);
	exitButtonYes->setSize(150, 150);
	exitButtonYes->setPosition("exitButton.left - 200", "exitButton.top");
	exitButtonYes->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	exitButtonYes->setText("Yes");
	exitButtonYes->setEnabled(false);
	exitButtonYes->setVisible(false);
	exitButtonYes->connect("MouseReleased", exitButtonsYes);
	gEnv->game.mainMenu.mainMenuWidgets.push_back(exitButtonNo);
	exitButtonNo->setSize(150, 150);
	exitButtonNo->setPosition("exitButton.right + 50", "exitButton.top");
	exitButtonNo->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	exitButtonNo->setText("No");
	exitButtonNo->setEnabled(false);
	exitButtonNo->setVisible(false);
	exitButtonNo->connect("MouseReleased", exitClick);
	exitButton->connect("MouseReleased", exitClick);
	startButton->connect("MouseReleased", startClick);


	//TESTS TESTS TESTS

	tgui::EditBox::Ptr edb = tgui::EditBox::create();
	gEnv->globalGui.add(edb, "editBox");
	edb->setRenderer(gEnv->globalTheme.getRenderer("EditBox"));
	edb->setSize(200, 50);
	edb->setTextSize(18);
	edb->setPosition(10, 270);
	edb->setDefaultText("Click to edit text...");

	tgui::Label::Ptr label = tgui::Label::create();
	gEnv->globalGui.add(label, "label");
	label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label->setText("This is a label.\nAnd these are radio buttons:");
	label->setPosition(10, 90);
	label->setTextSize(18);

}

void startClick()
{
	
}

void exitClick()
{
	gEnv->game.mainMenu.sureExit = !gEnv->game.mainMenu.sureExit;
	if (gEnv->game.mainMenu.sureExit)
	{
		gEnv->game.mainMenu.active = menuState::exitActive;
	}
	else
	{
		gEnv->game.mainMenu.active = menuState::mainMenu;
	}
	mainMenuChangeState();
}

void exitButtonsYes()
{
	gEnv->globalWindow.close();
}