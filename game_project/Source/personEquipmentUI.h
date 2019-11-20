#pragma once
//
// PersonUI functions
//

#include "enviroment.h"
#include "item.h"

void BuildPersonSchemeUI(int moduleSizeUI, int crewPersonNumber);
void personUIElementWasClicked(const int id, tgui::Widget::Ptr widget, const std::string& signalName);
void rmPanelClickedPerson(const int id, tgui::Widget::Ptr widget, const std::string& signalName);