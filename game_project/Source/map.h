#pragma once

#include "enviroment.h"
#include "adventureUI.h"
#include "UIExtensions.h"

void BuildMapUI();
void clickSector(const std::string str, const int id, tgui::Widget::Ptr widget, const std::string& signalName);
void jumpSector(const std::string str, tgui::Widget::Ptr widget, const std::string& signalName);
void UpdateMapUI();


void openMap();