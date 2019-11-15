#pragma once

#include "enviroment.h"

class UIShipModules
{
public:
	bool rmWasClicked;
	std::wstring activermModule;
	int moduleSizeUI = 30;
	tgui::Panel::Ptr mainShipPanel;
	tgui::Button::Ptr reactor, engine, compCore, hyperDrive, primWeap, secWeap;
	std::vector<tgui::Button::Ptr> subModules;
	enum shipType{
		viper,
		adder,
		eagle
	} shiptype;

	UIShipModules(shipType st, int subModulesCount);
	
};


void UIbuttonWasClicked(UIShipModules * ui, tgui::Widget::Ptr widget, const std::string& signalName);
void rmPanelClicked(UIShipModules * ui, tgui::Widget::Ptr widget, const std::string& signalName);
