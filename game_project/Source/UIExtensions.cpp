#include "UIExtensions.h"

tgui::Widget::Ptr createWidget(WidgetType::widgetType type, std::string render, std::string sizeX, std::string sizeY, std::string posX, std::string posY, bool enabled)
{
	tgui::Widget::Ptr widget;
	switch (type)
	{
	case WidgetType::Panel:
		widget = tgui::Panel::create();
		break;
	case WidgetType::Button:
		widget = tgui::Button::create();
		break;
	case WidgetType::BitmapButton:
		widget = tgui::BitmapButton::create();
		break;
	case WidgetType::ScrollablePanel:
		widget = tgui::ScrollablePanel::create();
		break;
	case WidgetType::ProgressBar:
		widget = tgui::ProgressBar::create();
		break;
	case WidgetType::Label:
		widget = tgui::Label::create();
	}
	widget->setRenderer(gEnv->globalTheme.getRenderer(render));
	if (type != WidgetType::Label)
		widget->setSize(sizeX, sizeY);
	widget->setPosition(posX, posY);
	widget->setEnabled(enabled);
	widget->setVisible(enabled);
	return widget;
}

tgui::Label::Ptr createWidgetLabel(std::string render, std::string posX, std::string posY, int textSize, std::wstring text, bool enabled)
{
	tgui::Label::Ptr label = tgui::Label::create();
	label->setRenderer(gEnv->globalTheme.getRenderer(render));
	label->setPosition(posX, posY);
	label->setText(text);
	label->setTextSize(textSize);
	label->setEnabled(enabled);
	label->setVisible(enabled);
	return label;
}

void createShipStatPanel(Ship* s, tgui::Panel::Ptr panel)
{
	panel->removeAllWidgets();
	std::string render = "Label";
	int y = 5;
	int yDif = 23;
	//Hull
	panel->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Hull") + L": " + std::to_wstring((int)s->hull.current) + L"/" + std::to_wstring((int)s->hull.total) + L" (+" + std::to_wstring((int)s->hullReg.total) + L" / round; NONE / day)")), "shipStatHull");
	tgui::Label::Ptr lab = tgui::Label::create();
	lab->setTextSize(18);
	lab->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	lab->setText("The strength of the ship's hull plating.\nIf the durability drops to 0, the core will be destroyed and the ship will explode.");
	lab->setToolTip(lab);
	y += yDif;
	//Shield
	panel->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Shield") + L": " + std::to_wstring((int)s->shield.current) + L"/" + std::to_wstring((int)s->shield.total) + L" (+" + std::to_wstring((int)s->shieldReg.total) + L" / round; NONE / day)")), "shipStatShield");
	y += yDif;
	//Power Supply
	panel->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Energy used") + L": " + std::to_wstring((int)s->powerSupply.current) + L"/" + std::to_wstring((int)s->powerSupply.total))), "shipStatPowerSupply");
	y += yDif;
	//High Power Supply
	panel->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("High energy limit used") + L": " + std::to_wstring((int)s->highPowerSupply.current) + L"/" + std::to_wstring((int)s->highPowerSupply.total))), "shipStatHighPowerSupply");
	y += yDif;
	//Battle Action Points
	panel->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Action points in battle") + L": " + std::to_wstring((int)s->actionPoints.total))), "shipStatActionPoints");
	y += yDif;
	//Hull resist to damgage
	panel->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Hull resistance") + L": "
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
	y += yDif;
	//Shield resist to damage
	panel->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Shield resistance") + L": "
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
	y += yDif;
	//Stealth, evasion, sensors and missileDefence
	panel->add(createWidgetLabel(render, "5", std::to_string(y), 18, GetString("Sensor power: ") + std::to_wstring((int)s->sensorPower.total) + L";"), "shipStatSensors");
	panel->add(createWidgetLabel(render, "250", std::to_string(y), 18, GetString("Sensor tier: ") + std::to_wstring((int)s->sensorTier.total), "shipStatSensorsTier"));
	y += yDif;
	panel->add(createWidgetLabel(render, "5", std::to_string(y), 18, GetString("Stealth power: ") + std::to_wstring((int)s->stealth.total) + L";"));
	panel->add(createWidgetLabel(render, "250", std::to_string(y), 18, GetString("Stealth tier: ") + std::to_wstring((int)s->stealthTier.total), "shipStatStealthTier"));
	y += yDif;
	panel->add(createWidgetLabel(render, "5", std::to_string(y), 18, GetString("Evasion: ") + std::to_wstring((int)s->evasion.total) + L";"), "shipStatEvasion");
	panel->add(createWidgetLabel(render, "250", std::to_string(y), 18, GetString("Mobility: ") + std::to_wstring((int)s->mobility.total), "shipStatMobility"));
	y += yDif;
	panel->add(createWidgetLabel(render, "5", std::to_string(y), 18, GetString("Missile defence power: ") + std::to_wstring((int)s->missileDefense.total) + L";"), "shipStatMissileDefence");
	panel->add(createWidgetLabel(render, "250", std::to_string(y), 18, GetString("Missile defence tier: ") + std::to_wstring((int)s->missileDefenseTier.total), "shipStatMissileDefenceTier"));

}

void enableWidget(tgui::Widget::Ptr widget, bool enable)
{
	if (widget != NULL)
	{
		widget->setEnabled(enable);
		widget->setVisible(enable);
	}
}

void swapElements(TargetInventory::targetInventory target, int id)
{
	Module* p_module;
	Equipment* e_equip;
	bool flagCantPlace = false;
	switch (target)
	{
	case TargetInventory::tableInventory:
		//Если мы помещаем в слот где есть другой итем место
		if (gEnv->game.player.inventory[id] != NULL)
		{
			//Если это ресурс того же типа
			if ((gEnv->game.player.inventory[id]->itemType == itemType::resource && gEnv->game.player.pickedItem->itemType == itemType::resource)
				&& (gEnv->game.player.inventory[id]->itemId == gEnv->game.player.pickedItem->itemId))
			{
				if (static_cast<ItemResource*>(gEnv->game.player.inventory[id])->count + static_cast<ItemResource*>(gEnv->game.player.pickedItem)->count <= 64)
				{
					static_cast<ItemResource*>(gEnv->game.player.inventory[id])->count += static_cast<ItemResource*>(gEnv->game.player.pickedItem)->count;
				}
				else if (gEnv->game.ui.shiftedItem && !gEnv->game.ui.shiftedItemTakedAll)
				{
					static_cast<ItemResource*>(gEnv->game.player.pickedItem)->count -= (64 - static_cast<ItemResource*>(gEnv->game.player.inventory[id])->count);
					static_cast<ItemResource*>(gEnv->game.player.inventory[gEnv->game.ui.shiftedItemStartId])->count += static_cast<ItemResource*>(gEnv->game.player.pickedItem)->count;
					static_cast<ItemResource*>(gEnv->game.player.inventory[id])->count = 64;
				}
				else if (gEnv->game.ui.shiftedItem && gEnv->game.ui.shiftedItemTakedAll)
				{
					flagCantPlace = true;
					break;
				}
				else {
					gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.pickedItem;
					static_cast<ItemResource*>(gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId])->count -= (64 - static_cast<ItemResource*>(gEnv->game.player.inventory[id])->count);
					static_cast<ItemResource*>(gEnv->game.player.inventory[id])->count = 64;
				}
				break;
			}
			// Если там другой ресурс или предмет и мы не брали предмет с шифта
			if (gEnv->game.player.pickedItemInvId != -1 && !gEnv->game.ui.shiftedItem)
				gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.inventory[id];
			// Если мы взяли предмет с шифта и пытаемся положить в предмет другого типа
			else if (gEnv->game.player.pickedItemInvId != -1 && gEnv->game.ui.shiftedItem)
			{
				flagCantPlace = true;
				break;
			}
		}
		// Если в слоте куда кладем ничего нет
		if (gEnv->game.player.pickedItemInvId != -1)
		{
			gEnv->game.player.inventory[id] = gEnv->game.player.pickedItem;
		}
		updateInventoryCell(id);
		break;
	case TargetInventory::gridPanel:
		if (gEnv->game.player.pickedLocalInventory != -1)
		{
			gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.inventory[id];
			gEnv->game.player.inventory[id] = gEnv->game.player.pickedItem;
		}
		else
		{
			gEnv->game.player.inventory[id] = gEnv->game.player.pickedItem;
		}
		break;
	case TargetInventory::shipPanel:
		p_module = static_cast<Module*>(gEnv->game.player.pickedItem);
		if (p_module->slot == gEnv->game.player.ship->slots[id].type)
		{
			gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.ship->modules[id];
			gEnv->game.player.ship->modules[id] = p_module;
		}
		else gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.pickedItem;
		break;
	case TargetInventory::personPanel:
		e_equip = static_cast<Equipment*>(gEnv->game.player.pickedItem);
		if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->slot[id] == e_equip->equipmentSlotType && gEnv->game.player.pickedLocalInventory != -1)
		{
			gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id];
			gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id] = e_equip;
		}
		else if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->slot[id] == e_equip->equipmentSlotType && gEnv->game.player.pickedLocalInventory == -1)
		{
			gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id] = e_equip;
		}
		else if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->slot[id] != e_equip->equipmentSlotType && gEnv->game.player.pickedLocalInventory == -1)
		{
			for (int i = 0; i < gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment.size(); i++)
			{
				if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->slot[i] == e_equip->equipmentSlotType)
				{
					gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[i] = e_equip;
				}
			}
		}
		else gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.pickedItem;
		break;
	}

	if (!flagCantPlace)
	{
		gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse"));
		gEnv->game.player.pickedItem = NULL;
		gEnv->game.player.pickedItemInvId = -1;
		gEnv->game.player.pickedLocalInventory = -1;
		gEnv->game.ui.shiftedItem = false;
		gEnv->game.ui.shiftedItemStartId = -1;
		gEnv->game.ui.shiftedItemTakedAll = false;
		rebuildAll();
	}
}

void rebuildAll()
{
	BuildInventoryUI(9); //145 ms
	RebuildInventoryGridPanel(); //53 ms
	updateShipSchemeUI();  // 9 ms
	updateShipValues(gEnv->game.player.ship); // 1 ms
	buildShipStats(); // 27 ms
	BuildPersonSchemeUI(50, gEnv->game.ui.activeOpenPersonWindow); // 14 ms
	UpdateStatPersonScreen(); // 14 ms
}

std::wstring createFloatString(float number)
{
	int l = (int)(number * 10);
	std::wstring str = std::to_wstring(l);
	if (str[str.size() - 1] == '0')
	{
		return std::to_wstring((int)number);
	}
	else
	{
		str.insert(str.end() - 1, '.');
		return str;
	}
}

std::wstring createStringByStatName(statNames::StatName stat)
{
	std::wstring str = L"";

	switch (stat)
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
	case statNames::hullResistPhysical:
		str += GetString("Hull physical resist") + L" ";
		break;
	case statNames::hullResistEnergy:
		str += GetString("Hull energy resist") + L" ";
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
	case statNames::shieldResistPhysical:
		str += GetString("Shield physical resist") + L" ";
		break;
	case statNames::shieldResistEnergy:
		str += GetString("Shield energy resist") + L" ";
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

	return str;
}
