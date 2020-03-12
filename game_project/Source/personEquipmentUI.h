#pragma once
//
// PersonUI functions
//

#include "enviroment.h"
#include "item.h"

void BuildSchemeChooseCharacter();
void BuildPersonSchemeUI(int moduleSizeUI, int crewPersonNumber);
void personUIElementWasClicked(const int id, tgui::Widget::Ptr widget, const std::string& signalName);
void rmPanelClickedPerson(const int id, tgui::Widget::Ptr widget, const std::string& signalName);
void rmPanelChoosenAddedPerson(const int id, const int module_id, tgui::Widget::Ptr widget, const std::string& signalName);
void ChangeActiveCharacter(int id);