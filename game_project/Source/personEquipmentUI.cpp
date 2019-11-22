#include "personEquipmentUI.h"

void BuildPersonSchemeUI(int equipSizeUI, int crewPersonNumber)
{
	tgui::Panel::Ptr mainPersonPanel = tgui::Panel::create();
	mainPersonPanel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
	mainPersonPanel->setSize(350, 600);
	mainPersonPanel->setPosition("5%", "10%");
	gEnv->globalGui.add(mainPersonPanel, "PersonSchemeEquipPanel");

	tgui::Label::Ptr characterName = tgui::Label::create();
	characterName->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	characterName->setText(gEnv->game.player.crew.characters[crewPersonNumber]->name);
	characterName->setPosition("(&.size - size)/2", "2%");
	characterName->setTextSize(18);
	mainPersonPanel->add(characterName, "PersonSchemeName");

	for (int i(0); i < gEnv->game.player.crew.characters[crewPersonNumber]->equipment.size(); i++)
	{
		tgui::Button::Ptr btn = tgui::Button::create();
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setSize(equipSizeUI, equipSizeUI);
		btn->setPosition(30,40+80*i);
		if (gEnv->game.player.crew.characters[crewPersonNumber]->equipment[i] != NULL)
			btn->setText(gEnv->game.player.crew.characters[i]->equipment[i]->name);
		mainPersonPanel->add(btn, "Person" + std::to_string(crewPersonNumber) + "Equip" + std::to_string(i));
		const int id = i;
		btn->connect("RightMouseReleased", personUIElementWasClicked, id);
	}
}

void personUIElementWasClicked(const int id, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (signalName == "RightMouseReleased" && !gEnv->game.ui.rmWasClicked)
	{
		//ui->activermModule = widget->cast<tgui::Button>()->getText();
		tgui::Panel::Ptr temp = tgui::Panel::create();
		temp->setSize(100, 90);
		int x = sf::Mouse::getPosition(gEnv->globalWindow).x;
		int y = sf::Mouse::getPosition(gEnv->globalWindow).y - 5;
		temp->setPosition(x, y);
		temp->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
		gEnv->globalGui.add(temp, "tempRightPanel");
		gEnv->game.ui.rmWasClicked = true;

		tgui::Button::Ptr btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 0);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Add");
		btn->connect("MouseReleased", rmPanelClickedPerson, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 30);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Delete");
		btn->connect("MouseReleased", rmPanelClickedPerson, id);

		btn = tgui::Button::create();
		temp->add(btn);
		btn->setSize(107, 31);
		btn->setPosition(0, 60);
		btn->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		btn->setText(L"Cancel");
		btn->connect("MouseReleased", rmPanelClickedPerson, id);
	}
}

void rmPanelClickedPerson(const int id, tgui::Widget::Ptr widget, const std::string& signalName)
{
	if (widget->cast<tgui::Button>()->getText() == L"Cancel")
	{
		gEnv->globalGui.remove(gEnv->globalGui.get<tgui::Panel>("tempRightPanel"));
		gEnv->game.ui.rmWasClicked = false;
	}
}