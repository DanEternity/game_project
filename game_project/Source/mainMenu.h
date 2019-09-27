#pragma once

#include <TGUI/Gui.hpp>

//This file contains logic for main menu

void updateMainMenu();
void exitButtons(tgui::Widget::Ptr widget, const std::string& signalName);
void createMenuButtons();