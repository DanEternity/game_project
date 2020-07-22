#include "spaceBattleTgui.h"

void buildMiniWindowShipStats(int x, int y, Ship * s)
{
	std::string render = "Label";
	tgui::Panel::Ptr pan = createWidget(WidgetType::Panel, "Panel", "400", "500", std::to_string(x), std::to_string(y))->cast<tgui::Panel>();
	//Hull
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Hull") + L": " + std::to_wstring((int)s->hull.current) + L"/" + std::to_wstring((int)s->hull.total))));
	y += 20;
	//Shield
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Shield") + L": " + std::to_wstring((int)s->shield.current) + L"/" + std::to_wstring((int)s->shield.total))));
	y += 20;
	//Power Supply
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Energy used") + L": " + std::to_wstring((int)s->powerSupply.current) + L"/" + std::to_wstring((int)s->powerSupply.total))));
	y += 20;
	//High Power Supply
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("High energy limit used") + L": " + std::to_wstring((int)s->highPowerSupply.current) + L"/" + std::to_wstring((int)s->highPowerSupply.total))));
	y += 20;
	//Battle Action Points
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Action points in battle") + L": " + std::to_wstring((int)s->actionPoints.total))));
	y += 20;
	//Hull resist to damgage
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Hull resistance") + L": "
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
	y += 20;
	//Shield resist to damage
	pan->add(createWidgetLabel(render, "5", std::to_string(y), 18, (GetString("Shield resistance") + L": "
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
	y += 20;

	gEnv->game.spaceBattle.GUI.add(pan, "MiniWindowShipStats");
}

void hideMiniWindowShipStats()
{
	gEnv->game.spaceBattle.GUI.remove(gEnv->game.spaceBattle.GUI.get<tgui::Panel>("MiniWindowShipStats"));
}
