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
		//���� �� �������� � ���� ��� ���� ������ ���� �����
		if (gEnv->game.player.inventory[id] != NULL)
		{
			//���� ��� ������ ���� �� ����
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
			// ���� ��� ������ ������ ��� ������� � �� �� ����� ������� � �����
			if (gEnv->game.player.pickedItemInvId != -1 && !gEnv->game.ui.shiftedItem)
				gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.inventory[id];
			// ���� �� ����� ������� � ����� � �������� �������� � ������� ������� ����
			else if (gEnv->game.player.pickedItemInvId != -1 && gEnv->game.ui.shiftedItem)
			{
				flagCantPlace = true;
				break;
			}
		}
		// ���� � ����� ���� ������ ������ ���
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