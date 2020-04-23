#pragma once

#include "enviroment.h"
#include "item.h"
#include "tableInventory.h"
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
void rmPanelClickedShip(const int id, tgui::Widget::Ptr widget, const std::string& signalName);
void rmPanelChoosenAdded(const int id, const int module_id, tgui::Widget::Ptr widget, const std::string& signalName);

// handlers
void handleShipModulesPanelEvent(const int id, tgui::Widget::Ptr widget, const std::string& signalName);

//stats field
void buildShipStats();
void updateShipStatsScreen();
void updateShipSchemeUI();

void createShipModulePriorityPanel();
void updateShipModulePriorityPanel();
void changeShipModulePriority(int id, bool isUp);

void applyModuleTooltipShipUI(int id);
void createModuleTooltipShipUI(Module * m);
void deleteAllTooltipsShipUI();
