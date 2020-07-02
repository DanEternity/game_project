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

tgui::Label::Ptr createWidgetLabel(std::string render, std::string posX, std::string posY, int textSize, std::wstring text)
{
	tgui::Label::Ptr label = tgui::Label::create();
	label->setRenderer(gEnv->globalTheme.getRenderer(render));
	label->setPosition(posX, posY);
	label->setText(text);
	label->setTextSize(textSize);
	return label;
}

void enableWidget(tgui::Widget::Ptr widget, bool enable)
{
	widget->setEnabled(enable);
	widget->setVisible(enable);
}

void swapElements(TargetInventory::targetInventory target, int id)
{
	Module* p_module;
	Equipment* e_equip;
	switch (target)
	{
	case TargetInventory::tableInventory:
		if (gEnv->game.player.inventory[id] != NULL) gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.inventory[id];
		else gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = NULL;
		gEnv->game.player.inventory[id] = gEnv->game.player.pickedItem;
		break;
	case TargetInventory::gridPanel:
		std::swap(
			gEnv->game.player.inventory[gEnv->game.player.localInventory[id]],
			gEnv->game.player.inventory[gEnv->game.player.localInventory[gEnv->game.player.pickedLocalInventory]]);
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
		if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->slot[id] == e_equip->equipmentSlotType)
		{
			gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id];
			gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id] = e_equip;
		}
		else gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.pickedItem;
		break;
	}

	gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse"));
	gEnv->game.player.pickedItem = NULL;
	gEnv->game.player.pickedItemInvId = NULL;
	gEnv->game.player.pickedLocalInventory = NULL;
	rebuildAll();
}

void rebuildAll()
{
	BuildInventoryUI(9);
	RebuildInventoryGridPanel();
	updateShipSchemeUI(); 
	updateShipValues(gEnv->game.player.ship);
	buildShipStats();
	BuildPersonSchemeUI(50, gEnv->game.ui.activeOpenPersonWindow);
	UpdateStatPersonScreen();
	deleteAllTooltipsPersonUI();
	deleteAllGridTooltips();
	deleteAllTooltipsShipUI();
	deleteAllInventoryTooltips();
}