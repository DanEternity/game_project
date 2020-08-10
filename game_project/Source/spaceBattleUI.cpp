#include "spaceBattleUI.h"

void createSpaceBattleUI()
{

	auto sb = &gEnv->game.spaceBattle;

	tgui::Button::Ptr btn = createWidget(WidgetType::Button, "Button", "200", "200", "100% - 200", "100% - 200")->cast<tgui::Button>();
	btn->setText("Next Turn");
	btn->setTextSize(20);
	sb->GUI.add(btn, "EndTurnButton");

	btn->connect("clicked", clickEndTurnButton);

	tgui::Label::Ptr text1 = createWidget(WidgetType::Label, "Label", "100", "20", "100% - 200", "100% - 300")->cast<tgui::Label>();
	sb->GUI.add(text1, "ActionPointsLabel");

	text1->setVisible(false);

}

void clickEndTurnButton()
{

	auto sb = &gEnv->game.spaceBattle;

	sb->EndTurnPressed = true;

}

void displayShipInfo()
{

	auto sb = &gEnv->game.spaceBattle;
	auto q = sb->GUI.get("ActionPointsLabel");
	q->cast<tgui::Label>()->setVisible(true);

	Ship * s = sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId];
	// Action Points
	q->cast<tgui::Label>()->setText("Energy: " + std::to_string(s->actionPoints.current) + "/" + std::to_string(s->actionPoints.total));

}

void hideShipInfo()
{

	auto sb = &gEnv->game.spaceBattle;

	auto q = sb->GUI.get("ActionPointsLabel");

	q->cast<tgui::Label>()->setVisible(false);
}
