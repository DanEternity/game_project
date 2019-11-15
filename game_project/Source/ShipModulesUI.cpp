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
	gEnv->globalGui.add(mainShipPanel, "mainShipPanel");
	mainShipPanel->add(reactor, "reactor");
	mainShipPanel->add(engine, "engine");
	mainShipPanel->add(compCore, "computer core");
	mainShipPanel->add(hyperDrive, "hyperdrive");
	mainShipPanel->add(primWeap, "weapon");
	mainShipPanel->add(secWeap, "sec weapon");
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
	reactor->setText(L"reactor");
	engine->setText(L"engine");
	compCore->setText(L"computer core");
	hyperDrive->setText(L"hyperdrive");
	primWeap->setText(L"weapon");
	secWeap->setText(L"sec weapon");
	rmWasClicked = false;

	for (int i = 0; i < subModulesCount; i++)
	{
		tgui::Button::Ptr temp = tgui::Button::create();
		subModules.push_back(temp);
		mainShipPanel->add(temp, L"submodule#" + std::to_wstring(i));
		temp->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		temp->setSize(moduleSizeUI, moduleSizeUI);
		temp->setText(L"submodule#" + std::to_wstring(i));
		temp->connect("MouseReleased", UIbuttonWasClicked, this);
		temp->connect("RightMouseReleased", UIbuttonWasClicked, this);
	}

	reactor->connect("MouseReleased", UIbuttonWasClicked, this);
	engine->connect("MouseReleased", UIbuttonWasClicked, this);
	compCore->connect("MouseReleased", UIbuttonWasClicked, this);
	hyperDrive->connect("MouseReleased", UIbuttonWasClicked, this);
	primWeap->connect("MouseReleased", UIbuttonWasClicked, this);
	secWeap->connect("MouseReleased", UIbuttonWasClicked, this);

	reactor->connect("RightMouseReleased", UIbuttonWasClicked, this);
	engine->connect("RightMouseReleased", UIbuttonWasClicked, this);
	compCore->connect("RightMouseReleased", UIbuttonWasClicked, this);
	hyperDrive->connect("RightMouseReleased", UIbuttonWasClicked, this);
	primWeap->connect("RightMouseReleased", UIbuttonWasClicked, this);
	secWeap->connect("RightMouseReleased", UIbuttonWasClicked, this);
	
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
		ui->activermModule = widget->cast<tgui::Button>()->getText();
		tgui::Panel::Ptr temp = tgui::Panel::create();
		temp->setSize(100, 60);
		int x = sf::Mouse::getPosition(gEnv->globalWindow).x;
		int y = sf::Mouse::getPosition(gEnv->globalWindow).y - 5;
		temp->setPosition(x, y);
		temp->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
		gEnv->globalGui.add(temp, "tempRightPanel");
		ui->rmWasClicked = true;

		tgui::Button::Ptr btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 0);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Delete");
		btn->connect("MouseReleased", rmPanelClicked, &(*ui));

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 30);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Cancel");
		btn->connect("MouseReleased", rmPanelClicked, &(*ui));
	}
}

void rmPanelClicked(UIShipModules * ui, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (widget->cast<tgui::Button>()->getText() == L"Cancel")
	{
		gEnv->globalGui.remove(gEnv->globalGui.get<tgui::Panel>("tempRightPanel"));
		ui->rmWasClicked = false;
	}
	else if (widget->cast<tgui::Button>()->getText() == L"Delete")
	{
		gEnv->globalGui.remove(gEnv->globalGui.get<tgui::Panel>("tempRightPanel"));
		ui->mainShipPanel->cast<tgui::Panel>()->remove(ui->mainShipPanel->cast<tgui::Panel>()->get<tgui::Button>(ui->activermModule));
		ui->rmWasClicked = false;
	}
}