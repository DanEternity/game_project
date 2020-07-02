#include "tableInventory.h"

void BuildInventoryUI(int cellSize)
{
	if (gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("inventoryPanel") != nullptr)
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("inventoryPanel")->removeAllWidgets();
	else gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::ScrollablePanel, "Panel3", "520", "200", "5%", "15%", false), "inventoryPanel");

	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{

		int positionX = i % cellSize;
		int positionY = i / cellSize;
		const int number = i;
		tgui::BitmapButton::Ptr button = createWidget(WidgetType::BitmapButton, "Button", "50", "50", std::to_string(5+ positionX * 50), std::to_string(10 + positionY * 50))->cast<tgui::BitmapButton>();
		gEnv->game.adventureGUI.get<tgui::ScrollablePanel>("inventoryPanel")->add(button, "InventoryCell"+ std::to_string(i));

		if (gEnv->game.player.inventory[i] != NULL)
		{
			if (gEnv->game.player.inventory[i]->icon != nullptr)
				button->setImage(*gEnv->game.player.inventory[i]->icon);
			else button->setImage(gEnv->modelDB[L"itemDefault"]->tex);
		}
		else button->setImage(gEnv->modelDB[L"itemEmpty"]->tex);

		button->connect("MouseReleased", InventoryResponseSignal, number, std::string("ShipInventory"));
		button->connect("RightMouseReleased", InventoryResponseSignal, number, std::string("ShipInventory"));
		button->connect("MouseEntered", applyStorageTooltip, i);
	}
}


void CreateInventoryGridPanel(int length)
{
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUIGridSubPanel")->add(createWidget(WidgetType::ScrollablePanel, "Panel2", "520", "140", "3%", "25%"), "inventoryGridPanel");
	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{
		int positionX = i % length;
		int positionY = i / length;
		const int number = i;
		tgui::BitmapButton::Ptr button = createWidget(WidgetType::BitmapButton, "Button", "45", "40", std::to_string(5 + positionX * 50), std::to_string(10 + positionY * 50))->cast<tgui::BitmapButton>();
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryGridPanel")->add(button, "InventoryItem" + std::to_string(i));
		button->setText(L"");
		button->connect("MouseReleased", InventoryGridPanelEventHandler, number);
		button->connect("RightMouseReleased", InventoryGridPanelEventHandler, number);
	}
}

void RebuildInventoryGridPanel()
{
	gEnv->game.player.localInventory.clear();
	// apply category filter
	//gEnv->game.player.inventoryFilter.searchString = L"Ebalo";
	//
	for (int id(0); id < gEnv->game.player.inventory.size(); id++)
	{
		if (gEnv->game.player.inventory[id] != NULL)
		{
			// compare to filter
			auto p = gEnv->game.player.inventory[id];
			//if (p->itemType in filter.itemTypes && p->name in filter.nameSeacrh)
			bool filter_ok = true;
			IntventoryFilter* filter = &gEnv->game.player.inventoryFilter;
			
			if (filter->searchString != L"")
			{
				if (p->name.find(filter->searchString) == std::wstring::npos)
				{
					filter_ok = false;
				}
			}

			if (filter->itemType.size() > 0)
			{
				if (filter->itemType.find(p->itemType) == filter->itemType.end())
				{
					filter_ok = false;
				}
			}

			if (p->itemType == itemType::module)
			{
				if (filter->moduleSlotType.size() > 0)
				{
					if (filter->moduleSlotType.find(static_cast<Module*>(p)->slot) == filter->moduleSlotType.end())
					{
						filter_ok = false;
					}
				}
			}

			if (p->itemType == itemType::equipment)
			{
				if (filter->equipmentType.size() > 0)
				{
					if (filter->equipmentType.find(static_cast<Equipment*>(p)->equipmentType) == filter->equipmentType.end())
					{
						filter_ok = false;
					}
				}
			}
			if (p->itemType == itemType::resource)
			{
				if (filter->equipmentType.size() > 0)
				{
						filter_ok = false;
				}
			}

			if (!filter_ok)
				continue;
			gEnv->game.player.localInventory.push_back(id);

		}
	}

	BuildInventoryUI(9);
	deleteAllGridTooltips();
	for (int id(0); id < gEnv->game.player.inventory.size(); id++)
	{	
		if (id < gEnv->game.player.localInventory.size() && gEnv->game.player.localInventory[id] != -1)
		{
			if (gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->icon != nullptr)
				gEnv->game.adventureGUI.get<tgui::BitmapButton>("InventoryItem" + std::to_string(id))->
				setImage(*gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->icon);
			else
				gEnv->game.adventureGUI.get<tgui::BitmapButton>("InventoryItem" + std::to_string(id))->
				setImage(gEnv->modelDB[L"itemDefault"]->tex);
		}
		else
			gEnv->game.adventureGUI.get<tgui::BitmapButton>("InventoryItem" + std::to_string(id))->
			setImage(gEnv->modelDB[L"itemEmpty"]->tex);

		if (gEnv->game.player.localInventory.size() > id) {
			if (gEnv->game.player.inventory[gEnv->game.player.localInventory[id]] != NULL)
			{
				switch (gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->itemType)
				{
				case itemType::module:
					gEnv->game.adventureGUI.get<tgui::BitmapButton>("InventoryItem" + std::to_string(id))->connect("MouseEntered", applyGridModuleTooltip, id);
					break;
				case itemType::equipment:
					gEnv->game.adventureGUI.get<tgui::BitmapButton>("InventoryItem" + std::to_string(id))->connect("MouseEntered", applyGridEquipmentTooltip, id);
					break;
				}
			}
		}
	}
}

void ApplyDefaultFilterToInventoryPanel()
{

	// current menu
	auto q = gEnv->game.player.shipMenu;
	
	if (q == shipMenu::ship)
	{
		gEnv->game.player.inventoryFilter.itemType.insert(itemType::module);
	}

	if (q == shipMenu::crew)
	{
		gEnv->game.player.inventoryFilter.itemType.insert(itemType::equipment);
	}
	if (q == shipMenu::craft)
	{
		gEnv->game.player.inventoryFilter.itemType.insert(itemType::resource);
	}
}

void filterSearchFieldChanged(tgui::Widget::Ptr widget, const std::string & signalName)
{

	gEnv->game.player.inventoryFilter.searchString = widget->cast<tgui::EditBox>()->getText();

	RebuildInventoryGridPanel();

}

void filterCategoryFieldChanged(tgui::Widget::Ptr widget, const std::string & signalName)
{

	auto p = widget->cast<tgui::ComboBox>();
	std::string s = p->getSelectedItemId();

	printf("Filter set: %s \n", s.c_str());

	gEnv->game.player.inventoryFilter.itemType.clear();
	gEnv->game.player.inventoryFilter.equipmentType.clear();
	gEnv->game.player.inventoryFilter.moduleSlotType.clear();

	if (s == "Primary weapon")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::primaryWeapon);
	}
	if (s == "Secondary weapon")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::secondaryWeapon);
	}
	if (s == "Engine")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::engine);
	}
	if (s == "Hyperdrive")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::hyperdrive);
	}
	if (s == "Core")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::core);
	}
	if (s == "System")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::system);
	}
	if (s == "Universal")
	{
		gEnv->game.player.inventoryFilter.moduleSlotType.insert(moduleSlot::universal);
	}

	// currently do nothing because not all windows are completed
	ApplyDefaultFilterToInventoryPanel();
	RebuildInventoryGridPanel();
}

void createModuleTooltip(Module * m)
{
	m->tooltipDescription->setSize(300, 250 + m->effects.size() * 30);
	m->tooltipDescription->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));

	tgui::Button::Ptr button = createWidget(WidgetType::Button, "Button", "300", "30", "0", "0")->cast<tgui::Button>();
	button->setText(m->name);
	m->tooltipDescription->add(button, "nameButtonTooltip");

	std::string render = "Label";
	m->tooltipDescription->add(createWidgetLabel(render, "(&.width - width) / 2", std::to_string(30), 18, L"Module"));
	m->tooltipDescription->add(createWidgetLabel(render, "(&.width - width) / 4 - 20", std::to_string(60), 18, L"Level: " + std::to_wstring(m->level)));
	m->tooltipDescription->add(createWidgetLabel(render, "(&.width - width) / 4 * 3", std::to_string(60), 18, L"Rarity: " + std::to_wstring(m->rarity)));

	tgui::Label::Ptr label4 = tgui::Label::create();
	label4->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label4->setPosition("(&.width - width) / 2", 90);
	std::wstring text = L"";
	switch (m->slot)
	{
	case moduleSlot::core:
		text = L"Slot type: Core";
		break;
	case moduleSlot::hyperdrive:
		text = L"Slot type: Hyperdrive";
		break;
	case moduleSlot::engine:
		text = L"Slot type: Engine";
		break;
	case moduleSlot::system:
		text = L"Slot type: System";
		break;
	case moduleSlot::primaryWeapon:
		text = L"Slot type: Primary Weapon";
		break;
	case moduleSlot::secondaryWeapon:
		text = L"Slot type: Secondary Weapon";
		break;
	case moduleSlot::universal:
		text = L"Slot type: Universal";
		break;
	}
	label4->setTextSize(18);
	m->tooltipDescription->add(createWidgetLabel(render, "(&.width - width) / 2", std::to_string(90), 18, text));


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

		if (!first) label5->setText(label5->getText() + str + L"\n");
		else label5->setText(str + L"\n");
		first = false;
		str = L"";
	}
}

void createResourseTooltip(ItemResource * r)
{
	r->tooltipDescription->setSize(300, 100);
	r->tooltipDescription->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));

	tgui::Button::Ptr button = createWidget(WidgetType::Button, "Button", "300", "30", "0", "0")->cast<tgui::Button>();
	button->setText(r->name);
	r->tooltipDescription->add(button, "nameButtonTooltip");

	r->tooltipDescription->add(createWidgetLabel("Label", "(&.width - width) / 2", std::to_string(30), 18, L"Level " + std::to_wstring(r->level)));
	r->tooltipDescription->add(createWidgetLabel("Label", "(&.width - width) / 2", std::to_string(60), 18, L"Count: " + std::to_wstring(r->count) + L"/" + std::to_wstring(r->maxCount)));
}

void createEquipmentTooltip(Equipment* e)
{
	e->tooltipDescription->setSize(300, 250 + e->effects.size() * 30);
	e->tooltipDescription->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));

	tgui::Button::Ptr button = createWidget(WidgetType::Button, "Button", "300", "30", "0", "0")->cast<tgui::Button>();
	button->setText(e->name);
	e->tooltipDescription->add(button, "nameButtonTooltip");

	std::string render = "Label";
	e->tooltipDescription->add(createWidgetLabel(render, "(&.width - width) / 2", std::to_string(30), 18, L"Equipment"));
	e->tooltipDescription->add(createWidgetLabel(render, "(&.width - width) / 4 - 20", std::to_string(60), 18, L"Level: " + std::to_wstring(e->level)));
	e->tooltipDescription->add(createWidgetLabel(render, "(&.width - width) / 4 * 3", std::to_string(60), 18, L"Rarity: " + std::to_wstring(e->rarity)));

	std::wstring text = L"";
	switch (e->equipmentSlotType)
	{
	case equipmentSlot::head:
		text = L"Slot type: Helmet";
		break;
	case equipmentSlot::arms:
		text = L"Slot type: Arms";
		break;
	case equipmentSlot::body:
		text = L"Slot type: Body";
		break;
	case equipmentSlot::legs:
		text = L"Slot type: Legs";
		break;
	case equipmentSlot::universal:
		text = L"Slot type: Universal";
	}
	e->tooltipDescription->add(createWidgetLabel(render, "(&.width - width) / 2", std::to_string(90), 18, text));


	tgui::Label::Ptr label5 = tgui::Label::create();
	label5->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label5->setPosition(10, 120);
	label5->setTextSize(18);
	e->tooltipDescription->add(label5);

	std::wstring str = L"";
	bool first = true;
	for (auto i : static_cast<Equipment*>(e)->effects)
	{
		switch (static_cast<StatModEffect*>(i)->statName)
		{
		case statNames::characterHealth:
			str += GetString("Health") + L" ";
			break;
		case statNames::characterArmor:
			str += GetString("Armor") + L" ";
			break;
		case statNames::characterShield:
			str += GetString("Shield") + L" ";
			break;
		case statNames::characterBlock:
			str += GetString("Block") + L" ";
			break;
		case statNames::characterResist:
			str += GetString("Resist") + L" ";
			break;
		case statNames::characterShieldReg:
			str += GetString("Shield Regeneration") + L" ";
			break;
		case statNames::characterActionPoints:
			str += GetString("Action Points") + L" ";
			break;
		case statNames::characterEnergy:
			str += GetString("Energy") + L" ";
			break;
		case statNames::characterEnergyReg:
			str += GetString("Energy Regeneration") + L" ";
			break;
		case statNames::characterInitiative:
			str += GetString("Initiative") + L" ";
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

void deleteAllInventoryTooltips()
{
	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{
		gEnv->game.adventureGUI.get<tgui::Button>("InventoryCell" + std::to_string(i))->setToolTip(NULL);
	}
}

void deleteAllGridTooltips()
{
	for (int i = 0; i < gEnv->game.player.inventory.size(); i++)
	{
		gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(i))->setToolTip(NULL);
	}
}


void applyStorageTooltip(int id)
{
	if (gEnv->game.player.inventory[id] != NULL)
	{
		switch (gEnv->game.player.inventory[id]->itemType)
		{
		case itemType::module:
			if (!gEnv->game.player.inventory[id]->tooltipWasCreated)
			{
				createModuleTooltip(static_cast<Module*>(gEnv->game.player.inventory[id]));
				gEnv->game.player.inventory[id]->tooltipWasCreated = true;
			}
			gEnv->game.adventureGUI.get<tgui::Button>("InventoryCell" + std::to_string(id))->setToolTip(gEnv->game.player.inventory[id]->tooltipDescription);
			tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
			break;
		case itemType::resource:
			if (!gEnv->game.player.inventory[id]->tooltipWasCreated)
			{
				createResourseTooltip(static_cast<ItemResource*>(gEnv->game.player.inventory[id]));
				gEnv->game.player.inventory[id]->tooltipWasCreated = true;
			}
			gEnv->game.adventureGUI.get<tgui::Button>("InventoryCell" + std::to_string(id))->setToolTip(gEnv->game.player.inventory[id]->tooltipDescription);
			tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
			break;
		case itemType::equipment:
			if (!gEnv->game.player.inventory[id]->tooltipWasCreated)
			{
				createEquipmentTooltip(static_cast<Equipment*>(gEnv->game.player.inventory[id]));
				gEnv->game.player.inventory[id]->tooltipWasCreated = true;
			}
			gEnv->game.adventureGUI.get<tgui::Button>("InventoryCell" + std::to_string(id))->setToolTip(gEnv->game.player.inventory[id]->tooltipDescription);
			tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
			break;
		}
	}
}

void applyGridModuleTooltip(int id)
{
	if (id < gEnv->game.player.localInventory.size())
	{
		if (!gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->tooltipWasCreated)
		{
			gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->tooltipWasCreated = true;
			createModuleTooltip(static_cast<Module*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]));
		}
		gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(id))->setToolTip(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->tooltipDescription);
		tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
	}
}

void applyGridEquipmentTooltip(int id)
{
	if (id < gEnv->game.player.localInventory.size())
	{
		if (!gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->tooltipWasCreated)
		{
			gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->tooltipWasCreated = true;
			createEquipmentTooltip(static_cast<Equipment*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]));
		}
		gEnv->game.adventureGUI.get<tgui::Button>("InventoryItem" + std::to_string(id))->setToolTip(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->tooltipDescription);
		tgui::ToolTip::setInitialDelay(sf::milliseconds(0));
	}
}