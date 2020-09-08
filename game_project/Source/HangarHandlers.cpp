#include "HangarHandlers.h"

void handleFighterModulesPanelEvent(int fighterId, int moduleId, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (signalName == "MouseReleased")
	{
		if (gEnv->game.player.pickedItem != NULL)
		{
			Module* p_module = static_cast<Module*>(gEnv->game.player.pickedItem);
			if (p_module->slot == gEnv->game.player.fighterPlanes[fighterId]->slots[moduleId].type)
			{
				if (gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId] != NULL)
				{
					gEnv->game.player.inventory[gEnv->game.player.pickedLocalInventory] = gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId];
					RebuildInventoryGridPanel();
				}
				if (gEnv->game.player.pickedLocalInventory != -1)
					gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId];
				gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId] = p_module;

				gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse"));
				gEnv->game.player.pickedItem = NULL;
				gEnv->game.player.pickedItemInvId = -1;
				gEnv->game.player.pickedLocalInventory = -1;

				buildFigtherModules(fighterId);
			}
		}
		else
		{
			if (gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId] != NULL)
			{
				gEnv->game.adventureGUI.add(createWidget(WidgetType::BitmapButton, "Button", std::to_string(45), std::to_string(45), std::to_string(sf::Mouse::getPosition(gEnv->globalWindow).x), std::to_string(sf::Mouse().getPosition(gEnv->globalWindow).y - 5)), "pickedItemMouse");
				gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse")->setImage(*gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId]->icon);
				gEnv->game.player.pickedItem = gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId];
				gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId] = NULL;
				buildFigtherModules(fighterId);
			}
		}
	}
}