#include "HangarHandlers.h"

void handleFighterModulesPanelEvent(int fighterId, int moduleId, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (signalName == "MouseReleased")
	{
		if (gEnv->game.player.pickedItem != NULL)
		{
			Module* p_module = static_cast<Module*>(gEnv->game.player.pickedItem);
			if (p_module->slot == gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId]->slot)
			{
				gEnv->game.player.inventory[gEnv->game.player.pickedItemInvId] = gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId];
				gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId] = p_module;

				gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse"));
				gEnv->game.player.pickedItem = NULL;
				gEnv->game.player.pickedItemInvId = -1;
				gEnv->game.player.pickedLocalInventory = -1;
			}
		}
	}
}