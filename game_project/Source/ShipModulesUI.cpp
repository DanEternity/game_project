#include "ShipModulesUI.h"



UIShipModules::UIShipModules(shipType st, int subModulesCount)
{
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
	gEnv->globalGui.add(mainShipPanel);
	mainShipPanel->add(reactor);
	mainShipPanel->add(engine);
	mainShipPanel->add(compCore);
	mainShipPanel->add(hyperDrive);
	mainShipPanel->add(primWeap);
	mainShipPanel->add(secWeap);
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
	reactor->setText("reactor");
	engine->setText("engine");
	compCore->setText("computer core");
	hyperDrive->setText("hyperdrive");
	primWeap->setText("weapon");
	secWeap->setText("sec weapon");
	rmWasClicked = false;

	for (int i = 0; i < subModulesCount; i++)
	{
		tgui::Button::Ptr temp = tgui::Button::create();
		subModules.push_back(temp);
		mainShipPanel->add(temp);
		temp->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		temp->setSize(moduleSizeUI, moduleSizeUI);
		temp->setText("submodule#" + std::to_string(i));
		temp->connect("MouseReleased", UIbuttonWasClicked, this);
		temp->connect("RightMouseReleased", UIbuttonWasClicked, this);
	}

	reactor->connect("MouseReleased", UIbuttonWasClicked, this);
	engine->connect("MouseReleased", UIbuttonWasClicked, this);
	compCore->connect("MouseReleased", UIbuttonWasClicked, this);
	hyperDrive->connect("MouseReleased", UIbuttonWasClicked, this);
	primWeap->connect("MouseReleased", UIbuttonWasClicked, this);
	secWeap->connect("MouseReleased", UIbuttonWasClicked, this);
	
	switch (st)
	{
		case shipType::eagle:
			reactor->setPosition(300, "(&.height - height) / 2");
			engine->setPosition(50, "(&.height - height) / 2");
			compCore->setPosition(500, "(&.height - height) / 2");
			hyperDrive->setPosition(150, "(&.height - height) / 2");
			primWeap->setPosition("(&.width - width) / 2", "25%");
			secWeap->setPosition("(&.width - width) / 2", "75%");

			for (int i = 0; i < subModulesCount; i++)
			{
				subModules[i]->setPosition(50 + 100 * i, "90%");
			}

			break;
	}
}

void UIbuttonWasClicked(UIShipModules * ui, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (signalName == "MouseReleased")
		gEnv->scripts.scriptGui.get<tgui::TextBox>("scriptTextMessage")->setText(gEnv->scripts.scriptGui.get<tgui::TextBox>("scriptTextMessage")->getText());
	else if (signalName == "RightMouseReleased" && !ui->rmWasClicked)
	{
		tgui::Panel::Ptr temp = tgui::Panel::create();
		temp->setSize(100, 30);
		int x = sf::Mouse::getPosition().x;
		int y = sf::Mouse::getPosition().y - 5;
		temp->setPosition(x, y);
		temp->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
		gEnv->globalGui.add(temp, "tempRightPanel");
		ui->rmWasClicked = true;

		tgui::Button::Ptr btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(100, 20);
		btn->setPosition(0, 0);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText("Delete");
		btn->connect("MouseReleased", rmPanelClicked, ui);
	}
}

void rmPanelClicked(const UIShipModules * ui,tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (widget->cast<tgui::Button>()->getText() == "Delete")
	{
		gEnv->globalGui.remove(gEnv->globalGui.get<tgui::Panel>("tempRightPanel"));
		//(*ui)->rmWasClicked = false;
	}
}