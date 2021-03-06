#pragma once
//
// PersonUI functions
//

#include "enviroment.h"
#include "item.h"
#include "LocaleLoader.h"
#include "characterManagement.h"
#include "tableInventory.h"
#include "UIExtensions.h"
#include "PersonHandlers.h"

void BuildSchemeChooseCharacter();
void BuildSchemeRoles();
void BuildPersonSchemeUI(int moduleSizeUI, int crewPersonNumber);
void BuildStatPersonScreen(int crewPersonNumber);
void BuildPersonSkillTree(int crewPersonNumber);
void BuildPanelChangePersonState();

void UpdatePersonSkillTree();
void UpdateStatPersonScreen();

void ChangeActiveCharacter(int id);
void ChangePersonPanelsState(PUIState::personUIstate state);

void skillUp(Character *c, PassiveSkill *p, int treeNumber, tgui::Widget::Ptr widget, const std::string& signalName);

void giveRoleFind(int id, tgui::Widget::Ptr widget, const std::string& signalName);
void giveRole(Character *c, int buttonId, tgui::Widget::Ptr widget, const std::string& signalName);
void giveRoleCaptain(Character *c, int buttonId);

void registerPlayerCharacter(Character *c);
void unregisterPlayerCharacter(int id);

void ShowBonuses();