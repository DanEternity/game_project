#pragma once


#include "ShipHandlers.h"
/*
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
*/

void BuildShipSchemeUI(int moduleSizeUI = 45);


// handlers


//stats field
void buildShipStats();
void updateShipSchemeUI();

void createShipModulePriorityPanel();
void changeShipModulePriority(int id, bool isUp);

void applyModuleTooltipShipUI(int id);
