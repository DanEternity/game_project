#pragma once

#include "enviroment.h"
#include "UIExtensions.h"
#include "spaceBattleMechanics.h"
#include "spaceBattleCore.h"

void buildMiniWindowShipStats(int x, int y, Ship * s);
void hideMiniWindowShipStats();

void buildMiniWindowHex(std::wstring name, bool full, float distance, float moveCost, std::wstring text, int x, int y);
void hideMiniWindowHex();

void showBars();
void hideBars();

void createActiveModulesButtons();
void selectWeaponModule(int id);

void buttonShipInfo();
void clickShipInfo();
void shipInfoExButton();
void applyShipInfoTooltip(int id);

void createLogsWindow();
void addNoteToLogs(std::wstring stroke);
void clearLogs();