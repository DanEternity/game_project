#include "CraftUI.h"

void BuildPlanPanel()
{
	tgui::ScrollablePanel::Ptr panel = tgui::ScrollablePanel::create();
	panel->setRenderer(gEnv->globalTheme.getRenderer("Panel3"));
	panel->setPosition("1%", "1%");
	panel->setSize(600, 370);
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(panel, "PlanPanel");
	panel->setVisible(false);
	panel->setEnabled(false);
}
