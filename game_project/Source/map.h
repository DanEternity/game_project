#pragma once

#include "enviroment.h"

void BuildMapUI();
void clickSector(const std::string str, const int id, tgui::Widget::Ptr widget, const std::string& signalName);
void jumpSector(const std::string str, tgui::Widget::Ptr widget, const std::string& signalName);
void UpdateMapUI();

