#include "CraftUI.h"

void BuildPlanPanel()
{
	gEnv->game.adventureGUI.get<tgui::Panel>("playerUISubPanel")->add(createWidget(WidgetType::ScrollablePanel, "Panel3", "600", "370", "1%", "1%", false), "PlanPanel");
}
