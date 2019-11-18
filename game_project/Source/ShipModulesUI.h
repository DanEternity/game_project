#pragma once

#include "enviroment.h"
#include "item.h"

class UIShipModules
{
public:
	bool rmWasClicked;
	std::wstring activermModule;
	int moduleSizeUI = 45;
	tgui::Panel::Ptr mainShipPanel;
	tgui::Button::Ptr reactor, engine, compCore, hyperDrive, primWeap, secWeap;
	std::vector<tgui::Button::Ptr> subModules;
	enum shipType{
		viper,
		adder,
		eagle
	} shiptype;

	UIShipModules(shipType st, int subModulesCount);
	void changeModule(Module * module, const int id);

	int countBaseShipModules = 6;
	std::vector<Module*> modulesItem;
};


void UIbuttonWasClicked(UIShipModules * ui, int id, tgui::Widget::Ptr widget, const std::string& signalName);
void rmPanelClicked(UIShipModules * ui, int id, tgui::Widget::Ptr widget, const std::string& signalName);
