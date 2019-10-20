#pragma once

#include "enviroment.h"

void UIbuttonWasClicked(std::string buttonName, tgui::Widget::Ptr widget, const std::string& signalName);

class UIShipModules
{
public:
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