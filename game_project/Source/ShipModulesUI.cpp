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
	

	for (int i = 0; i < subModulesCount; i++)
	{
		tgui::Button::Ptr temp = tgui::Button::create();
		subModules.push_back(temp);
		mainShipPanel->add(temp);
		temp->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		temp->setSize(moduleSizeUI, moduleSizeUI);
		temp->setText("submodule#" + std::to_string(i));
		temp->connect("RightMouseReleased", UIbuttonWasClicked, temp->getText());
	}

	reactor->connect("MouseReleased", UIbuttonWasClicked, reactor->getText());
	engine->connect("MouseReleased", UIbuttonWasClicked, engine->getText());
	compCore->connect("MouseReleased", UIbuttonWasClicked, compCore->getText());
	hyperDrive->connect("MouseReleased", UIbuttonWasClicked, hyperDrive->getText());
	primWeap->connect("MouseReleased", UIbuttonWasClicked, primWeap->getText());
	secWeap->connect("MouseReleased", UIbuttonWasClicked, secWeap->getText());
	
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

void UIbuttonWasClicked(std::string buttonName, tgui::Widget::Ptr widget, const std::string& signalName)
{
		gEnv->scripts.scriptGui.get<tgui::TextBox>("scriptTextMessage")->setText(buttonName);
}
