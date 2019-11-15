#pragma once
#include "enviroment.h"
#include <TGUI\TGUI.hpp>
#include <string>

void buttonWasClicked(int i);

class ChooseUI
{
public:
	std::vector<tgui::BitmapButton::Ptr> chooseButtons;
	tgui::ScrollablePanel::Ptr scrollablePanel;

	ChooseUI(int x, int y)
	{
		scrollablePanel = tgui::ScrollablePanel::create();
		gEnv->scripts.scriptGui.add(scrollablePanel);
		scrollablePanel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
		scrollablePanel->setPosition(x, y);
		scrollablePanel->setSize(250, 200);
	}

	void initButtons(int count)
	{
		tgui::BitmapButton::Ptr chooseButton;
		for (int i = 0; i < count; i++)
		{
			chooseButton = tgui::BitmapButton::create();
			chooseButtons.push_back(chooseButton);
			scrollablePanel->add(chooseButton);
			chooseButton->setPosition(0, i*35 + 10);
			chooseButton->setSize(250, 30);
			chooseButton->setRenderer(gEnv->globalTheme.getRenderer("Button"));
			chooseButton->connect("MouseReleased", buttonWasClicked, i);
		}
	}

	void setButton(int id, std::wstring text, bool active)
	{
		chooseButtons[id]->setText(text);
		chooseButtons[id]->setEnabled(active);
		chooseButtons[id]->setVisible(active);
	}

	void deleteButtons()
	{

		for (int i(0); i < chooseButtons.size(); i++)
		{
			auto p = chooseButtons[i];
			scrollablePanel->remove(p);
			p.reset();
		}
		chooseButtons.clear();
	}

	void setVisible(bool vis)
	{
		scrollablePanel->setVisible(vis);
		scrollablePanel->setEnabled(vis);
	}
};
