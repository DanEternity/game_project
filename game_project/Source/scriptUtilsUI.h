#pragma once
#include "enviroment.h"
#include <TGUI\TGUI.hpp>
#include <string>

void buttonWasClicked(int i);

class ChooseUI
{
public:
	std::vector<tgui::Button::Ptr> chooseButtons;
	tgui::ScrollablePanel::Ptr scrollablePanel;

	ChooseUI()
	{
		scrollablePanel = tgui::ScrollablePanel::create();
		gEnv->scripts.scriptGui.add(scrollablePanel);
		scrollablePanel->setRenderer(gEnv->globalTheme.getRenderer("ScrollablePanel"));
		scrollablePanel->setPosition("40%", "60%");
		scrollablePanel->setSize(500, 200);
	}

	void initButtons(int count)
	{
		tgui::Button::Ptr chooseButton;
		for (int i = 0; i < count; i++)
		{
			chooseButton = tgui::Button::create();
			chooseButtons.push_back(chooseButton);
			scrollablePanel->add(chooseButton);
			chooseButton->setPosition(10, i*100 + 10);
			chooseButton->setSize(90, 30);
			chooseButton->setRenderer(gEnv->globalTheme.getRenderer("Button"));
			chooseButton->connect("MouseReleased", buttonWasClicked, i);
		}
	}

	void setButton(int id, std::string text, bool active)
	{
		chooseButtons[id]->setText(text);
		chooseButtons[id]->setEnabled(active);
		chooseButtons[id]->setVisible(active);
	}

	void deleteButtons()
	{
		for (const auto& widget : chooseButtons)
		{
			gEnv->scripts.scriptGui.remove(widget);
		}
	}

	void setVisible(bool vis)
	{
		scrollablePanel->setVisible(vis);
		scrollablePanel->setEnabled(vis);
	}
};
