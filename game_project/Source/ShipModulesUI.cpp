#include "shipModulesUI.h"


/*
UIShipModules::UIShipModules(shipType st, int subModulesCount)
{
	for (int i(0); i < countBaseShipModules + subModulesCount; i++) modulesItem.push_back(nullptr);
	mainShipPanel = tgui::Panel::create();
	mainShipPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
	mainShipPanel->setSize(600, 400);
	mainShipPanel->setPosition("65%", "50%");
	reactor = tgui::Button::create();
	engine = tgui::Button::create();
	compCore = tgui::Button::create();
	hyperDrive = tgui::Button::create();
	primWeap = tgui::Button::create();
	secWeap = tgui::Button::create();
	gEnv->globalGui.add(mainShipPanel, "mainShipPanel");
	mainShipPanel->add(reactor, "0");
	mainShipPanel->add(engine, "1");
	mainShipPanel->add(compCore, "2");
	mainShipPanel->add(hyperDrive, "3");
	mainShipPanel->add(primWeap, "4");
	mainShipPanel->add(secWeap, "5");
	reactor->setSize(moduleSizeUI, moduleSizeUI);
	engine->setSize(moduleSizeUI, moduleSizeUI);
	compCore->setSize(moduleSizeUI, moduleSizeUI);
	hyperDrive->setSize(moduleSizeUI, moduleSizeUI);
	primWeap->setSize(moduleSizeUI, moduleSizeUI);
	secWeap->setSize(moduleSizeUI, moduleSizeUI);
	reactor->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	engine->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	compCore->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	hyperDrive->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	primWeap->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	secWeap->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	rmWasClicked = false;

	for (int i = 0; i < subModulesCount; i++)
	{
		tgui::Button::Ptr temp = tgui::Button::create();
		subModules.push_back(temp);
		mainShipPanel->add(temp, std::to_wstring(i+6));
		temp->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		temp->setSize(moduleSizeUI, moduleSizeUI);
		temp->connect("RightMouseReleased", UIbuttonWasClicked, this, i+6);
	}

	reactor->connect("RightMouseReleased", UIbuttonWasClicked, this, 0);
	engine->connect("RightMouseReleased", UIbuttonWasClicked, this, 2);
	compCore->connect("RightMouseReleased", UIbuttonWasClicked, this, 3);
	hyperDrive->connect("RightMouseReleased", UIbuttonWasClicked, this, 1);
	primWeap->connect("RightMouseReleased", UIbuttonWasClicked, this, 4);
	secWeap->connect("RightMouseReleased", UIbuttonWasClicked, this, 5);
	
	switch (st)
	{
		case shipType::eagle:
			reactor->setPosition(300, "(&.height - height) / 2");
			engine->setPosition(50, "(&.height - height) / 2");
			compCore->setPosition(500, "(&.height - height) / 2");
			hyperDrive->setPosition(150, "(&.height - height) / 2");
			primWeap->setPosition("(&.width - width) / 2", "15%");
			secWeap->setPosition("(&.width - width) / 2", "65% + 30");

			for (int i = 0; i < subModulesCount; i++)
			{
				subModules[i]->setPosition(50 + 100 * i, "80%");
			}

			break;
	}
}

*/

void UIbuttonWasClicked(const int id, tgui::Widget::Ptr widget, const std::string& signalName)
{
	/*if (signalName == "MouseReleased")
		gEnv->scripts.scriptGui.get<tgui::TextBox>("scriptTextMessage")->setText(gEnv->scripts.scriptGui.get<tgui::TextBox>("scriptTextMessage")->getText());*/
	if (signalName == "RightMouseReleased" && !gEnv->game.ui.rmWasClicked)
	{
		//ui->activermModule = widget->cast<tgui::Button>()->getText();
		tgui::Panel::Ptr temp = tgui::Panel::create();
		temp->setSize(100, 60);
		int x = sf::Mouse::getPosition(gEnv->globalWindow).x;
		int y = sf::Mouse::getPosition(gEnv->globalWindow).y - 5;
		temp->setPosition(x, y);
		temp->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
		gEnv->globalGui.add(temp, "tempRightPanel");
		gEnv->game.ui.rmWasClicked = true;

		tgui::Button::Ptr btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 0);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Delete");
		btn->connect("MouseReleased", rmPanelClicked, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 30);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Cancel");
		btn->connect("MouseReleased", rmPanelClicked, id);
	}
}

void rmPanelClicked(const int id, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (widget->cast<tgui::Button>()->getText() == L"Cancel")
	{
		gEnv->globalGui.remove(gEnv->globalGui.get<tgui::Panel>("tempRightPanel"));
		gEnv->game.ui.rmWasClicked = false;
	}
	else if (widget->cast<tgui::Button>()->getText() == L"Delete")
	{
		gEnv->globalGui.remove(gEnv->globalGui.get<tgui::Panel>("tempRightPanel"));

		// need to delete module correctly
		gEnv->game.player.ship->modules[id] = nullptr;
		
		tgui::Panel::Ptr panel = gEnv->globalGui.get<tgui::Panel>("ShipSchemeModulesPanel");
		panel->get<tgui::Button>("ShipSchemeModule" + std::to_string(id))->setText("");
		gEnv->game.ui.rmWasClicked = false;
	}
}

void BuildShipSchemeUI(int moduleSizeUI)
{

	tgui::Panel::Ptr mainShipPanel = tgui::Panel::create();
	mainShipPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
	mainShipPanel->setSize(600, 400);
	mainShipPanel->setPosition("65%", "50%");
	gEnv->globalGui.add(mainShipPanel, "ShipSchemeModulesPanel");

	for (int i(0); i < gEnv->game.player.ship->modules.size(); i++)
	{
		tgui::Button::Ptr btn = tgui::Button::create();
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setSize(moduleSizeUI, moduleSizeUI);
		btn->setPosition((rand() % 550) + 25, (rand() % 200) + 50);
		if (gEnv->game.player.ship->modules[i] != NULL)
			btn->setText(gEnv->game.player.ship->modules[i]->name);
		mainShipPanel->add(btn, "ShipSchemeModule" + std::to_string(i));
		const int id = i;
		btn->connect("RightMouseReleased", UIbuttonWasClicked, id);
	}


}
