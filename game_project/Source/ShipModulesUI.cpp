#include "shipModulesUI.h"
#include "enviroment.h"
#include "LocaleLoader.h"

void BuildShipSchemeUI(int moduleSizeUI)
{

	tgui::Panel::Ptr mainShipPanel = tgui::Panel::create();
	mainShipPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel3"));
	mainShipPanel->setSize(600, 300);
	mainShipPanel->setPosition("1%", "2%");
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(mainShipPanel, "ShipSchemeModulesPanel");

	tgui::Button::Ptr priorityButton = tgui::Button::create();
	priorityButton->setText(L"Modules priority");
	priorityButton->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	priorityButton->setSize(130, 30);
	priorityButton->setPosition("76%", "2%");
	mainShipPanel->add(priorityButton, "priorityButton");
	priorityButton->connect("MouseReleased", updateShipModulePriorityPanel);

	for (int i(0); i < gEnv->game.player.ship->modules.size(); i++)
	{
		tgui::Button::Ptr btn = tgui::Button::create();
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setSize(moduleSizeUI, moduleSizeUI);
		btn->setPosition(25 + (i % 5) * 90 , 50 + (i / 5) * 80);
		if (gEnv->game.player.ship->modules[i] != NULL)
			btn->setText(gEnv->game.player.ship->modules[i]->name);
		mainShipPanel->add(btn, "ShipSchemeModule" + std::to_string(i));
		const int id = i;

	//	btn->connect("MouseReleased", UIbuttonWasClicked, id);

		btn->connect("MouseReleased", handleShipModulesPanelEvent, id);
		btn->connect("RightMouseReleased", handleShipModulesPanelEvent, id);
		btn->connect("MouseEntered", applyModuleTooltipShipUI, id);
	}

	mainShipPanel->setVisible(false);
	mainShipPanel->setEnabled(false);
}

void handleShipModulesPanelEvent(const int id, tgui::Widget::Ptr widget, const std::string & signalName)
{

	if (signalName == "MouseReleased")
	{
		if (gEnv->game.player.pickedItem != NULL)
		{
			auto p_module = static_cast<Module*>(gEnv->game.player.pickedItem);
			auto type = p_module->slot;

			auto s_slot = gEnv->game.player.ship->slots[id];

			// compare to compability

			if (s_slot.type == type)
			{
				gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(gEnv->game.player.pickedLocalInventory))->setRenderer(gEnv->globalTheme.getRenderer("Button"));
				auto tmp = gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId];

				gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.ship->modules[id];
				gEnv->game.player.ship->modules[id] = static_cast<Module*>(tmp);

				widget->cast<tgui::Button>()->setText(gEnv->game.player.ship->modules[id]->name);

				gEnv->game.player.pickedItemInvId = -1;
				gEnv->game.player.pickedItem = NULL;
				gEnv->game.player.pickedLocalInventory = -1;

				RebuildInventoryGridPanel();
				updateShipValues(gEnv->game.player.ship);
				updateShipStatsScreen();

				UpdateInventoryUI();
				deleteAllTooltipsShipUI();
			}
			else
			{
				// nothing
				return;
			}


		}
	}
	if (signalName == "RightMouseReleased" && !gEnv->game.ui.rmWasClicked)
	{
		//ui->activermModule = widget->cast<tgui::Button>()->getText();
		tgui::Panel::Ptr temp = tgui::Panel::create();
		temp->setSize(100, 90);
		int x = sf::Mouse::getPosition(gEnv->globalWindow).x;
		int y = sf::Mouse::getPosition(gEnv->globalWindow).y - 5;
		temp->setPosition(x, y);
		temp->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
		gEnv->game.adventureGUI.add(temp, "tempRightPanel");
		gEnv->game.ui.rmWasClicked = true;

		tgui::Button::Ptr btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 0);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Add");
		btn->connect("MouseReleased", rmPanelClickedShip, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 30);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Unequip");
		btn->connect("MouseReleased", rmPanelClickedShip, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 60);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Cancel");
		btn->connect("MouseReleased", rmPanelClickedShip, id);
	}

}

void rmPanelClickedShip(const int id, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (widget->cast<tgui::Button>()->getText() == L"Cancel")
	{
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
		gEnv->game.ui.rmWasClicked = false;
		if (gEnv->game.ui.tempAddPanelClicked)
		{
			gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
			gEnv->game.ui.tempAddPanelClicked = false;
		}
	}
	else if (widget->cast<tgui::Button>()->getText() == L"Unequip")
	{
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));

		// need to delete module correctly
		// = nullptr;
		for (int i(0); i < gEnv->game.player.inventory.size(); i++)
		{
			if (gEnv->game.player.inventory[i] == NULL)
			{
				gEnv->game.player.inventory[i] = gEnv->game.player.ship->modules[id];
				gEnv->game.player.ship->modules[id] = NULL;
				break;
			}
		}

		tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel");
		panel->get<tgui::Button>("ShipSchemeModule" + std::to_string(id))->setText("");
		gEnv->game.ui.rmWasClicked = false;

		updateShipValues(gEnv->game.player.ship);
		RebuildInventoryGridPanel();
		updateShipStatsScreen();

		UpdateInventoryUI();
		deleteAllTooltipsShipUI();
	}
	else if (widget->cast<tgui::Button>()->getText() == L"Add")
	{
		if (!gEnv->game.ui.tempAddPanelClicked)
		{
			gEnv->game.ui.tempAddPanelClicked = true;
			int goodItemsCount = 0;
			tgui::Button::Ptr btn;
			tgui::Panel::Ptr panel = tgui::Panel::create();
			for (int i(0); i < gEnv->game.player.inventory.size(); i++)
			{
				if (gEnv->game.player.inventory[i] == nullptr) continue;
				if (gEnv->game.player.inventory[i]->itemType == itemType::module)
				{
					if (static_cast<Module*>(gEnv->game.player.inventory[i])->slot == gEnv->game.player.ship->slots[id].type)
					{
						btn = tgui::Button::create();
						btn->setSize(107, 31);
						btn->setPosition(0, 30 * goodItemsCount);
						btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
						btn->setText(gEnv->game.player.inventory[i]->name);
						const int num = i;
						btn->connect("MouseReleased", rmPanelChoosenAdded, num, id);
						panel->add(btn);
						goodItemsCount++;
					}
				}

			}
			if (goodItemsCount != 0)
			{
				panel->setSize(100, 30 * goodItemsCount);
				auto pos = gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel")->getPosition();
				pos.x += 100;
				panel->setPosition(pos);
				panel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
				gEnv->game.adventureGUI.add(panel, "tempAddPanel");
			}
			else
				gEnv->game.ui.tempAddPanelClicked = false;
		}


	}
}

void rmPanelChoosenAdded(const int id, const int module_id, tgui::Widget::Ptr widget, const std::string& signalName)
{
	
	gEnv->game.ui.tempAddPanelClicked = true;
	Module* temp = static_cast<Module*>(gEnv->game.player.inventory[id]);

	gEnv->game.player.inventory[id] = gEnv->game.player.ship->modules[module_id];
	gEnv->game.player.ship->modules[module_id] = temp;

	tgui::Panel::Ptr panel = gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel");
	tgui::Panel::Ptr panel2 = gEnv->game.adventureGUI.get<tgui::Panel>("ShipSchemeModulesPanel");

	if (gEnv->game.player.inventory[id] != NULL)
		panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(gEnv->game.player.inventory[id]->name);
	else
		panel->get<tgui::Button>("InventoryCell" + std::to_string(id))->setText(L"");

	if (gEnv->game.player.ship->modules[module_id] != NULL)
		panel2->get<tgui::Button>("ShipSchemeModule" + std::to_string(module_id))->setText(gEnv->game.player.ship->modules[module_id]->name);
	else
		panel2->get<tgui::Button>("ShipSchemeModule" + std::to_string(module_id))->setText(L"");

	gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempRightPanel"));
	gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("tempAddPanel"));
	gEnv->game.ui.rmWasClicked = false;
	gEnv->game.ui.tempAddPanelClicked = false;

	updateShipValues(gEnv->game.player.ship);
	RebuildInventoryGridPanel();
	updateShipStatsScreen();

	UpdateInventoryUI();
	deleteAllTooltipsShipUI();

}


void buildShipStats()
{
	int y = 5;
	tgui::Label::Ptr label = tgui::Label::create();
	label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label->setText(GetString("Hull") + L": "
		+ std::to_wstring((int)gEnv->game.player.ship->hull.current)
		+ L"/"
		+ std::to_wstring((int)gEnv->game.player.ship->hull.total));
	label->setPosition(5, y);
	label->setTextSize(18);
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->add(label, "shipStatHull");

	y += 20;

	label = tgui::Label::create();
	label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label->setText(GetString("Shield") + L": "
		+ std::to_wstring((int)gEnv->game.player.ship->shield.current)
		+ L"/"
		+ std::to_wstring((int)gEnv->game.player.ship->shield.total));
	label->setPosition(5, y);
	label->setTextSize(18);
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->add(label, "shipStatShield");

	y += 20;

	label = tgui::Label::create();
	label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label->setText(GetString("Power supply") + L": "
		+ std::to_wstring((int)gEnv->game.player.ship->powerSupply.current)
		+ L"/"
		+ std::to_wstring((int)gEnv->game.player.ship->powerSupply.total));
	label->setPosition(5, y);
	label->setTextSize(18);
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->add(label, "shipStatPowerSupply");

	y += 20;

	label = tgui::Label::create();
	label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label->setText(GetString("High power supply") + L": "
		+ std::to_wstring((int)gEnv->game.player.ship->highPowerSupply.current)
		+ L"/"
		+ std::to_wstring((int)gEnv->game.player.ship->highPowerSupply.total));
	label->setPosition(5, y);
	label->setTextSize(18);
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->add(label, "shipStatHighPowerSupply");

	y += 20;

	label = tgui::Label::create();
	label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label->setText(GetString("Action points in battle") + L": "
		+ std::to_wstring((int)gEnv->game.player.ship->actionPoints.current)
		+ L"/"
		+ std::to_wstring((int)gEnv->game.player.ship->actionPoints.total));
	label->setPosition(5, y);
	label->setTextSize(18);
	gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->add(label, "shipStatActionPoints");
}

void updateShipStatsScreen()
{
	tgui::Label::Ptr label = gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->get("shipStatHull")->cast<tgui::Label>();
	label->setText(GetString("Hull") + L": "
		+ std::to_wstring((int)gEnv->game.player.ship->hull.current)
		+ L"/"
		+ std::to_wstring((int)gEnv->game.player.ship->hull.total));

	label = gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->get("shipStatShield")->cast<tgui::Label>();
	label->setText(GetString("Shield") + L": "
		+ std::to_wstring((int)gEnv->game.player.ship->shield.current)
		+ L"/"
		+ std::to_wstring((int)gEnv->game.player.ship->shield.total));

	label = gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->get("shipStatPowerSupply")->cast<tgui::Label>();
	label->setText(GetString("Power supply") + L": "
		+ std::to_wstring((int)gEnv->game.player.ship->powerSupply.current)
		+ L"/"
		+ std::to_wstring((int)gEnv->game.player.ship->powerSupply.total));

	label = gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->get("shipStatHighPowerSupply")->cast<tgui::Label>();
	label->setText(GetString("High power supply") + L": "
		+ std::to_wstring((int)gEnv->game.player.ship->highPowerSupply.current)
		+ L"/"
		+ std::to_wstring((int)gEnv->game.player.ship->highPowerSupply.total));

	label = gEnv->game.adventureGUI.get<tgui::Panel>("shipStatsPanel")->get("shipStatActionPoints")->cast<tgui::Label>();
	label->setText(GetString("Action points in battle") + L": "
		+ std::to_wstring((int)gEnv->game.player.ship->actionPoints.current)
		+ L"/"
		+ std::to_wstring((int)gEnv->game.player.ship->actionPoints.total));

	for (int i(0); i < gEnv->game.player.ship->modules.size(); i++)
	{
		if (gEnv->game.player.ship->modules[i] != NULL) {
			if (!gEnv->game.player.ship->modules[i]->online)
				gEnv->game.adventureGUI.get<tgui::Button>("ShipSchemeModule" + std::to_string(i))->setRenderer(gEnv->globalTheme.getRenderer("Button2"));
			else
				gEnv->game.adventureGUI.get<tgui::Button>("ShipSchemeModule" + std::to_string(i))->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		}
		else
			gEnv->game.adventureGUI.get<tgui::Button>("ShipSchemeModule" + std::to_string(i))->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	}
}

void createShipModulePriorityPanel()
{
	tgui::ScrollablePanel::Ptr priorityPanel = tgui::ScrollablePanel::create();
	priorityPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
	priorityPanel->setSize(300, 500);
	priorityPanel->setPosition("51%", "5%");
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(priorityPanel, "priorityPanel");
	priorityPanel->setVisible(false);
	priorityPanel->setEnabled(false);

	for (int i = 0; i < gEnv->game.player.ship->modules.size(); i++)
	{
		tgui::Label::Ptr label = tgui::Label::create();
		label->setTextSize(20);
		label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
		switch (i)
		{
		case 0:
			label->setText(GetString("Core") + L" (" + std::to_wstring(gEnv->game.player.ship->modules[i]->powerPriority) + L")");
			break;
		case 1:
			label->setText(GetString("Hyperdrive") + L" (" + std::to_wstring(gEnv->game.player.ship->modules[i]->powerPriority) + L")");
			break;
		case 2:
			label->setText(GetString("Engine") + L" (" + std::to_wstring(gEnv->game.player.ship->modules[i]->powerPriority) + L")");
			break;
		case 3:
			label->setText(GetString("System") + L" (" + std::to_wstring(gEnv->game.player.ship->modules[i]->powerPriority) + L")");
			break;
		case 4:
			label->setText(GetString("Primary weapon") + L" (" + std::to_wstring(gEnv->game.player.ship->modules[i]->powerPriority) + L")");
			break;
		default:
			break;
		};
		label->setPosition("(&.width - width) / 2", 20 + i*60);
		priorityPanel->add(label, "labelModulePriority" + std::to_string(i));
		if (i != 0)
		{
			tgui::Button::Ptr button1 = tgui::Button::create();
			button1->setPosition("1%", 20 + i * 60);
			button1->setSize(30, 30);
			button1->setText("<");
			button1->setRenderer(gEnv->globalTheme.getRenderer("Button"));
			priorityPanel->add(button1);
			button1->connect("MouseReleased", changeShipModulePriority, i, false);

			tgui::Button::Ptr button2 = tgui::Button::create();
			button2->setPosition("89%", 20 + i * 60);
			button2->setSize(30, 30);
			button2->setText(">");
			button2->setRenderer(gEnv->globalTheme.getRenderer("Button"));
			priorityPanel->add(button2);
			button2->connect("MouseReleased", changeShipModulePriority, i, true);
		}
	}
}

void updateShipModulePriorityPanel()
{
	if (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("priorityPanel")->isVisible())
	{
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("priorityPanel")->setVisible(false);
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("priorityPanel")->setEnabled(false);
	}
	else
	{
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("priorityPanel")->setVisible(true);
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("priorityPanel")->setEnabled(true);

		for (int id(0); id < gEnv->game.player.ship->modules.size(); id++)
		{


			if (gEnv->game.player.ship->modules[id] == NULL)
				continue;

			gEnv->game.adventureGUI.get<tgui::Label>("labelModulePriority" + std::to_string(id))
				->setText(gEnv->game.player.ship->modules[id]->name + L" [" + std::to_wstring(gEnv->game.player.ship->modules[id]->powerPriority) + L"]");

		}
	}

	updateShipValues(gEnv->game.player.ship);
	updateShipStatsScreen();

}

void changeShipModulePriority(int id, bool isUp)
{
	if (isUp)
	{
		if (gEnv->game.player.ship->modules[id]->powerPriority < 99)
			gEnv->game.player.ship->modules[id]->powerPriority++;
	}
	else
	{
		if (gEnv->game.player.ship->modules[id]->powerPriority > 1)
			gEnv->game.player.ship->modules[id]->powerPriority--;
	}
	gEnv->game.adventureGUI.get<tgui::Label>("labelModulePriority" + std::to_string(id))
				->setText(gEnv->game.player.ship->modules[id]->name + L" [" + std::to_wstring(gEnv->game.player.ship->modules[id]->powerPriority) + L"]");
}

void applyModuleTooltipShipUI(int id)
{
	if (gEnv->game.player.ship->modules[id] != NULL)
	{
		createModuleTooltip(gEnv->game.player.ship->modules[id]);
		gEnv->game.adventureGUI.get<tgui::Button>("ShipSchemeModule" + std::to_string(id))->setToolTip(gEnv->game.player.ship->modules[id]->tooltipDescription);
		tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
	}
}

void createModuleTooltipShipUI(Module * m)
{
	m->tooltipDescription->setSize(300, 250 + m->effects.size() * 30);
	m->tooltipDescription->setRenderer(globalEnviroment->globalTheme.getRenderer("Panel2"));

	tgui::Button::Ptr button = tgui::Button::create();
	button->setRenderer(globalEnviroment->globalTheme.getRenderer("Button"));
	button->setPosition(0, 0);
	button->setSize(300, 30);
	button->setText(m->name);
	m->tooltipDescription->add(button, "nameButtonTooltip");

	tgui::Label::Ptr label = tgui::Label::create();
	label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label->setPosition("(&.width - width) / 2", 30);
	label->setText("Chto-to");
	label->setTextSize(18);
	m->tooltipDescription->add(label);

	tgui::Label::Ptr label2 = tgui::Label::create();
	label2->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label2->setPosition("(&.width - width) / 4 - 20", 60);
	label2->setText(L"Level: " + std::to_wstring(m->level));
	label2->setTextSize(18);
	m->tooltipDescription->add(label2);

	tgui::Label::Ptr label3 = tgui::Label::create();
	label3->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label3->setPosition("(&.width - width) / 4 * 3", 60);
	label3->setText(L"Rarity: " + std::to_wstring(m->rarity));
	label3->setTextSize(18);
	m->tooltipDescription->add(label3);

	tgui::Label::Ptr label4 = tgui::Label::create();
	label4->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label4->setPosition("(&.width - width) / 2", 90);
	switch (m->slot)
	{
	case moduleSlot::core:
		label4->setText("Slot type: Core");
		break;
	case moduleSlot::hyperdrive:
		label4->setText("Slot type: Hyperdrive");
		break;
	case moduleSlot::engine:
		label4->setText("Slot type: Engine");
		break;
	case moduleSlot::system:
		label4->setText("Slot type: System");
		break;
	case moduleSlot::primaryWeapon:
		label4->setText("Slot type: Primary Weapon");
		break;
	case moduleSlot::secondaryWeapon:
		label4->setText("Slot type: Secondary Weapon");
		break;
	case moduleSlot::universal:
		label4->setText("Slot type: Universal");
		break;
	}
	label4->setTextSize(18);
	m->tooltipDescription->add(label4);


	tgui::Label::Ptr label5 = tgui::Label::create();
	label5->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label5->setPosition(10, 120);
	label5->setTextSize(18);
	m->tooltipDescription->add(label5);

	std::wstring str = L"";
	bool first = true;

	str += L"Usage Power Supply: " + std::to_wstring((int)(static_cast<Module*>(m)->powerSupply)) + L"\n";
	str += L"Usage High Power Supply: " + std::to_wstring((int)(static_cast<Module*>(m)->highPowerSupply)) + L"\n\n";
	for (auto i : static_cast<Module*>(m)->effects)
	{
		switch (static_cast<StatModEffect*>(i)->statName)
		{
		case statNames::hull:
			str += GetString("Hull") + L" ";
			break;
		case statNames::actionPoints:
			str += GetString("Action points in battle") + L" ";
			break;
		case statNames::additionalWeaponAccuracy:
			str += GetString("Additional weapon accuracy") + L" ";
			break;
		case statNames::evasion:
			str += GetString("Evasion rating") + L" ";
			break;
		case statNames::fuel:
			str += GetString("Fuel") + L" ";
			break;
		case statNames::highPowerSupply:
			str += GetString("High power supply") + L" ";
			break;
		case statNames::hullReg:
			str += GetString("Hull regeneration") + L" ";
			break;
		case statNames::hullResist:
			str += GetString("Hull resist") + L" ";
			break;
		case statNames::hullStructureStability:
			str += GetString("Hull structure stability") + L" ";
			break;
		case statNames::hyperDriveFuelEfficiency:
			str += GetString("Hyper drive fuel efficiency") + L" ";
			break;
		case statNames::hyperDrivePower:
			str += GetString("Hyper drive power") + L" ";
			break;
		case statNames::hyperDriveTier:
			str += GetString("Hyper drive tier") + L" ";
			break;
		case statNames::missileDefense:
			str += GetString("Missile defence") + L" ";
			break;
		case statNames::missileDefenseTier:
			str += GetString("Misile defence tier") + L" ";
			break;
		case statNames::mobility:
			str += GetString("Mobility") + L" ";
			break;
		case statNames::powerSupply:
			str += GetString("Power supply") + L" ";
			break;
		case statNames::sensorPower:
			str += GetString("Sensor power") + L" ";
			break;
		case statNames::sensorTier:
			str += GetString("Sensor tier") + L" ";
			break;
		case statNames::shield:
			str += GetString("Shield") + L" ";
			break;
		case statNames::shieldReg:
			str += GetString("Shield regeneration") + L" ";
			break;
		case statNames::shieldResist:
			str += GetString("Shield resist") + L" ";
			break;
		case statNames::shieldStructureStability:
			str += GetString("Shield structure stability") + L" ";
			break;
		case statNames::stealth:
			str += GetString("Stealth") + L" ";
			break;
		case statNames::stealthTier:
			str += GetString("Stealth tier") + L" ";
			break;
		case statNames::totalDamageMultiplier:
			str += GetString("Total damage multiplier") + L" ";
			break;
		}
		if (static_cast<StatModEffect*>(i)->p_add != 0)
			str += L"+" + std::to_wstring((int)static_cast<StatModEffect*>(i)->p_add) + L" ";
		if (static_cast<StatModEffect*>(i)->p_mul != 0)
			str += L"+" + std::to_wstring((int)(static_cast<StatModEffect*>(i)->p_mul * 100)) + L"% ";
		if (static_cast<StatModEffect*>(i)->p_sub != 0)
			str += L"-" + std::to_wstring((int)static_cast<StatModEffect*>(i)->p_sub) + L" ";
		if (static_cast<StatModEffect*>(i)->p_negMul != 0)
			str += L"-" + std::to_wstring((int)(static_cast<StatModEffect*>(i)->p_negMul * 100)) + L"% ";

		if (!first)
			label5->setText(label5->getText() + str + L"\n");
		else
			label5->setText(str + L"\n");
		first = false;
		str = L"";
	}
}

void deleteAllTooltipsShipUI()
{
	for (int i = 0; i < gEnv->game.player.ship->modules.size(); i++)
	{
		gEnv->game.adventureGUI.get<tgui::Button>("ShipSchemeModule" + std::to_string(i))->setToolTip(NULL);
		gEnv->game.adventureGUI.get<tgui::Button>("ShipSchemeModule" + std::to_string(i))->disconnectAll("MouseEntered");
	}
}