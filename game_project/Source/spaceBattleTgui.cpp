#include "spaceBattleTgui.h"

void buildMiniWindowShipStats(int x, int y, Ship * s)
{
	if (gEnv->game.spaceBattle.GUI.get<tgui::Panel>("shipInfoPanel") != nullptr) return;
	std::string render = "Label";
	int laby = 5;
	tgui::Panel::Ptr pan = createWidget(WidgetType::Panel, "Panel", "500", "300", std::to_string(x), std::to_string(y))->cast<tgui::Panel>();
	//Hull
	pan->add(createWidgetLabel(render, "5", std::to_string(laby), 18, (GetString("Hull") + L": " + std::to_wstring((int)s->hull.current) + L"/" + std::to_wstring((int)s->hull.total))));
	laby += 20;
	//Shield
	pan->add(createWidgetLabel(render, "5", std::to_string(laby), 18, (GetString("Shield") + L": " + std::to_wstring((int)s->shield.current) + L"/" + std::to_wstring((int)s->shield.total))));
	laby += 20;
	//Power Supply
	pan->add(createWidgetLabel(render, "5", std::to_string(laby), 18, (GetString("Energy used") + L": " + std::to_wstring((int)s->powerSupply.current) + L"/" + std::to_wstring((int)s->powerSupply.total))));
	laby += 20;
	//High Power Supply
	pan->add(createWidgetLabel(render, "5", std::to_string(laby), 18, (GetString("High energy limit used") + L": " + std::to_wstring((int)s->highPowerSupply.current) + L"/" + std::to_wstring((int)s->highPowerSupply.total))));
	laby += 20;
	//Battle Action Points
	pan->add(createWidgetLabel(render, "5", std::to_string(laby), 18, (GetString("Action points in battle") + L": " + std::to_wstring((int)s->actionPoints.total))));
	laby += 20;
	//Hull resist to damgage
	pan->add(createWidgetLabel(render, "5", std::to_string(laby), 18, (GetString("Hull resistance") + L": "
		+ std::to_wstring((int)s->hullResistPhysical.total)
		+ L"/" + std::to_wstring((int)s->hullResistEnergy.total)
		+ L"/" + std::to_wstring((int)s->hullStructureStability.total)
		+ L" (Physical: "
		+ std::to_wstring((int)s->hullResistPhysical.total != 0 ? (int)((s->hullResistPhysical.total / (s->hullResistPhysical.total + 100)) * 100) : 0)
		+ L"%; Energy: "
		+ std::to_wstring((int)s->hullResistEnergy.total != 0 ? (int)((s->hullResistEnergy.total / (s->hullResistEnergy.total + 100)) * 100) : 0)
		+ L"%; Crit: "
		+ std::to_wstring((int)s->hullStructureStability.total != 0 ? (int)((s->hullStructureStability.total / (s->hullStructureStability.total + 100)) * 100) : 0)
		+ L"%)")), "shipStatHullResist");
	laby += 20;
	//Shield resist to damage
	pan->add(createWidgetLabel(render, "5", std::to_string(laby), 18, (GetString("Shield resistance") + L": "
		+ std::to_wstring((int)s->shieldResistPhysical.total)
		+ L"/" + std::to_wstring((int)s->shieldResistEnergy.total)
		+ L"/" + std::to_wstring((int)s->shieldStructureStability.total)
		+ L" (Physical: "
		+ std::to_wstring((int)s->shieldResistPhysical.total != 0 ? (int)((s->shieldResistPhysical.total / (s->shieldResistPhysical.total + 100)) * 100) : 0)
		+ L"%; Energy: "
		+ std::to_wstring((int)s->shieldResistEnergy.total != 0 ? (int)((s->shieldResistEnergy.total / (s->shieldResistEnergy.total + 100)) * 100) : 0)
		+ L"%; Crit: "
		+ std::to_wstring((int)s->shieldStructureStability.total != 0 ? (int)((s->shieldStructureStability.total / (s->shieldStructureStability.total + 100)) * 100) : 0)
		+ L"%)")), "shipStatShieldResistPhysical");
	laby += 20;

	gEnv->game.spaceBattle.GUI.add(pan, "MiniWindowShipStats" + std::to_string(gEnv->game.ui.spaceBattleShipMiniWindowCount++));
}

void hideMiniWindowShipStats()
{
	for (int i = 0; i < gEnv->game.ui.spaceBattleShipMiniWindowCount; i++)
		gEnv->game.spaceBattle.GUI.remove(gEnv->game.spaceBattle.GUI.get<tgui::Panel>("MiniWindowShipStats" + std::to_string(i)));
	gEnv->game.ui.spaceBattleShipMiniWindowCount = 0;
}

void buildMiniWindowHex(std::wstring name, bool full, float distance, float moveCost, std::wstring text, int x, int y)
{
	if (gEnv->game.spaceBattle.GUI.get<tgui::Panel>("shipInfoPanel") != nullptr) return;
	std::string render = "Label";
	int laby = 5;
	tgui::Panel::Ptr pan = createWidget(WidgetType::Panel, "Panel", "300", "150", std::to_string(x), std::to_string(y))->cast<tgui::Panel>();
	pan->add(createWidgetLabel(render, "5", std::to_string(laby), 18, name));
	laby += 25;
	if (full)
	{
		pan->add(createWidgetLabel(render, "5", std::to_string(laby), 18, L"Distance: " + createFloatString(distance)));
		laby += 20;
		pan->add(createWidgetLabel(render, "5", std::to_string(laby), 18, L"Move cost: " + createFloatString(moveCost) + L" action points"));
		laby += 20;
	}
	pan->add(createWidgetLabel(render, "5", std::to_string(laby), 18, L"Effects:\n" + text));

	gEnv->game.spaceBattle.GUI.add(pan, "MiniWindowHex" + std::to_string(gEnv->game.ui.spaceBattleHexMiniWindowCount));
	gEnv->game.ui.spaceBattleHexMiniWindowCount++;
}

void hideMiniWindowHex()
{
	for (int i = 0; i < gEnv->game.ui.spaceBattleHexMiniWindowCount; i++)
		gEnv->game.spaceBattle.GUI.remove(gEnv->game.spaceBattle.GUI.get<tgui::Panel>("MiniWindowHex" + std::to_string(i)));
	gEnv->game.ui.spaceBattleHexMiniWindowCount = 0;
}

void showBars()
{
	if (gEnv->game.spaceBattle.GUI.get<tgui::ProgressBar>("spaceBattleHullBar") != NULL)
	{
		gEnv->game.spaceBattle.GUI.remove(gEnv->game.spaceBattle.GUI.get<tgui::ProgressBar>("spaceBattleHullBar"));
		gEnv->game.spaceBattle.GUI.remove(gEnv->game.spaceBattle.GUI.get<tgui::ProgressBar>("spaceBattleShieldBar"));
		gEnv->game.spaceBattle.GUI.remove(gEnv->game.spaceBattle.GUI.get<tgui::ProgressBar>("spaceBattleActionPointsBar"));
	}
	auto ship = getCurrentPickShip();

	tgui::ProgressBar::Ptr bar = createWidget(WidgetType::ProgressBar, "ProgressBar2", "300", "30", "2%", "85%")->cast<tgui::ProgressBar>();
	bar->setMinimum(0);
	bar->setMaximum(ship->hull.total);
	bar->setValue(ship->hull.current);
	bar->setText("Hull: "
		+ std::to_string((int)ship->hull.current)
		+ "/"
		+ std::to_string((int)ship->hull.total));

	gEnv->game.spaceBattle.GUI.add(bar, "spaceBattleHullBar");

	bar = createWidget(WidgetType::ProgressBar, "ProgressBar", "300", "30", "2%", "90%")->cast<tgui::ProgressBar>();
	bar->setMinimum(0);
	bar->setMaximum(ship->shield.total);
	bar->setValue(ship->shield.current);
	bar->setText("Shield: "
		+ std::to_string((int)ship->shield.current)
		+ "/"
		+ std::to_string((int)ship->shield.total));

	gEnv->game.spaceBattle.GUI.add(bar, "spaceBattleShieldBar");

	bar = createWidget(WidgetType::ProgressBar, "ProgressBar", "300", "30", "2%", "95%")->cast<tgui::ProgressBar>();
	bar->setMinimum(0);
	bar->setMaximum(ship->actionPoints.total);
	bar->setValue(ship->actionPoints.current);
	bar->setText("Action points: "
		+ std::to_string((int)ship->actionPoints.current)
		+ "/"
		+ std::to_string((int)ship->actionPoints.total));

	gEnv->game.spaceBattle.GUI.add(bar, "spaceBattleActionPointsBar");

}

void hideBars()
{
	if (gEnv->game.spaceBattle.GUI.get<tgui::ProgressBar>("spaceBattleHullBar") != NULL)
	{
		gEnv->game.spaceBattle.GUI.remove(gEnv->game.spaceBattle.GUI.get<tgui::ProgressBar>("spaceBattleHullBar"));
		gEnv->game.spaceBattle.GUI.remove(gEnv->game.spaceBattle.GUI.get<tgui::ProgressBar>("spaceBattleShieldBar"));
		gEnv->game.spaceBattle.GUI.remove(gEnv->game.spaceBattle.GUI.get<tgui::ProgressBar>("spaceBattleActionPointsBar"));
	}
}

void createActiveModulesButtons()
{
	for (int i = 0; i < gEnv->game.ui.activeWeaponModulesCount; i++)
	{
		gEnv->game.spaceBattle.GUI.remove(gEnv->game.spaceBattle.GUI.get<tgui::BitmapButton>("activeModuleButton" + std::to_string(i)));
		gEnv->game.spaceBattle.GUI.remove(gEnv->game.spaceBattle.GUI.get<tgui::Label>("activeModuleStateText" + std::to_string(i)));
	}
	gEnv->game.ui.activeWeaponModulesCount = 0;

	auto ship = getCurrentPickShip();
	if (ship == NULL) return;
	for (int i = 0, j = 0; i < ship->modules.size(); i++)
	{
		if (ship->modules[i] != NULL)
		{
			if (ship->modules[i]->moduleType == moduleType::weapon)
			{
				
				tgui::BitmapButton::Ptr but = tgui::BitmapButton::create();
				gEnv->game.spaceBattle.GUI.add(but, "activeModuleButton" + std::to_string(j));
				but->setSize("10%", "&.height * 0.1");
				but->setText(ship->modules[i]->name);
				int shift = but->getParent()->getSize().x * 0.3;
				but->setPosition(shift + but->getSize().x * j, "90%");
				but->setRenderer(gEnv->globalTheme.getRenderer("Button"));

				std::wstring text = L"";
				switch (static_cast<WeaponModule*>(ship->modules[i])->weaponState)
				{
				case weaponModuleState::normal:
					text = L"Ready to use";
					break;
				case weaponModuleState::partialCooldown:
					text = L"Partial cooldown";
					break;
				case weaponModuleState::fullCooldown:
					text = L"Full cooldown";
					break;
				default:
					text = L"Unknown state";
				}

				gEnv->game.spaceBattle.GUI.add(createWidgetLabel("Label", std::to_string(shift + but->getSize().x * j), "85%", 18, text), "activeModuleStateText" + std::to_string(j));

				but->connect("MouseReleased", selectWeaponModule, ++j);
				gEnv->game.ui.activeWeaponModulesCount++;

				
			}
		}
	}
}

void selectWeaponModule(int id)
{
	auto sb = &gEnv->game.spaceBattle;
	if (sb->weaponId != id)
	{
		int wepId = id;
		auto w = spaceBattle::getShipWeaponModule(sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId], wepId);
		if (w != NULL)
		{
			if (spaceBattle::canUseWeapon(sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId], w))
			{
				wprintf(L"Info: Weapon selected: %ws \n", w->name.c_str());
				sb->selectedWeaponModule = w;
				sb->weaponModuleSelected = true;
				sb->weaponId = wepId;
			}
		}
	}
}

void buttonShipInfo()
{
	if (gEnv->game.spaceBattle.GUI.get<tgui::BitmapButton>("buttonShipInfo") == nullptr)
	{
		gEnv->game.spaceBattle.GUI.add(createWidget(WidgetType::BitmapButton, "Button", "10%", "10%", "90%", "70%"), "buttonShipInfo");
		gEnv->game.spaceBattle.GUI.get<tgui::BitmapButton>("buttonShipInfo")->setText(L"Detailed ship info");
		gEnv->game.spaceBattle.GUI.get<tgui::BitmapButton>("buttonShipInfo")->setTextSize(20);
		gEnv->game.spaceBattle.GUI.get<tgui::BitmapButton>("buttonShipInfo")->connect("MouseReleased", clickShipInfo);
	}
}

void clickShipInfo()
{
	if (gEnv->game.spaceBattle.GUI.get<tgui::Panel>("shipInfoPanel") != nullptr) return;
	auto ship = getCurrentPickShip();
	if (ship != NULL)
	{
		tgui::Panel::Ptr pan = createWidget(WidgetType::Panel, "Panel", "60%", "60%", "20%", "20%")->cast<tgui::Panel>();
		gEnv->game.spaceBattle.GUI.add(pan, "shipInfoPanel");

		tgui::Panel::Ptr modPan = createWidget(WidgetType::Panel, "Panel2", "48%", "94%", "2%", "3%")->cast<tgui::Panel>();
		pan->add(modPan);

		tgui::Panel::Ptr statPan = createWidget(WidgetType::Panel, "Panel3", "46%", "89%", "52%", "8%")->cast<tgui::Panel>();
		pan->add(statPan);

		tgui::BitmapButton::Ptr exBut = createWidget(WidgetType::BitmapButton, "Button", "5%", "6%", "93%", "1%")->cast<tgui::BitmapButton>();
		exBut->setText("X");
		exBut->setTextSize(20);
		exBut->connect("MouseReleased", shipInfoExButton);
		pan->add(exBut);

		for (int i = 0; i < ship->modules.size(); i++)
		{
			tgui::BitmapButton::Ptr modBut = createWidget(WidgetType::BitmapButton, "Button", "50", "50", std::to_string(50 + i * 60), "200")->cast<tgui::BitmapButton>();
			modPan->add(modBut);
			if (ship->modules[i] != NULL)
			{
				if (ship->modules[i]->icon == NULL)
					giveIconToItem(ship->modules[i]);
				modBut->setImage(*ship->modules[i]->icon);
				modBut->setToolTip(gEnv->game.ui.tooltipDescription);
				modBut->connect("MouseEntered", applyShipInfoTooltip, i);
			}
		}

		createShipStatPanel(ship, statPan);
	}
}

void shipInfoExButton()
{
	gEnv->game.spaceBattle.GUI.get<tgui::Panel>("shipInfoPanel")->removeAllWidgets();
	gEnv->game.spaceBattle.GUI.remove(gEnv->game.spaceBattle.GUI.get<tgui::Panel>("shipInfoPanel"));
}

void applyShipInfoTooltip(int id)
{
	auto ship = getCurrentPickShip();
	if (ship != NULL)
	{
		if (ship->modules[id] != NULL)
		{
			switch (ship->modules[id]->moduleType)
			{
			case moduleType::system:
				createModuleTooltip(ship->modules[id]);
				break;
			case moduleType::weapon:
				createWeaponModuleTooltip(static_cast<WeaponModule*>(ship->modules[id]));
				break;
			}
			gEnv->game.ui.tooltipDescription->setVisible(true);
		}
		else gEnv->game.ui.tooltipDescription->setVisible(false);
	}
}

void createLogsWindow()
{
	if (gEnv->game.spaceBattle.GUI.get<tgui::Panel>("spaceBattleLogsPanel") != nullptr)
	{
		gEnv->game.spaceBattle.GUI.get<tgui::Panel>("spaceBattleLogsPanel")->removeAllWidgets();
		gEnv->game.spaceBattle.GUI.remove(gEnv->game.spaceBattle.GUI.get<tgui::Panel>("spaceBattleLogsPanel"));
	}
	else {
		tgui::ScrollablePanel::Ptr pan = createWidget(WidgetType::ScrollablePanel, "Panel2", "15%", "40%", "170", "30")->cast<tgui::ScrollablePanel>();
		tgui::Label::Ptr lab = createWidgetLabel("Label", "8", "10", 18, gEnv->game.ui.spaceBattleLogs);
		pan->add(lab);
		gEnv->game.spaceBattle.GUI.add(pan, "spaceBattleLogsPanel");
	}
}

void addNoteToLogs(std::wstring stroke)
{
	stroke += L"\n";
	gEnv->game.ui.spaceBattleLogs += stroke;
}

void clearLogs()
{
	gEnv->game.ui.spaceBattleLogs = L"";
}