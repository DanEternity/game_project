#include "menuOverlay.h"
#include "enviroment.h"

void updateMenuOverlay(double deltaTime)
{

	if (gEnv->menuData.drawRequired)
	{

		// draw menu based on gamemode active

	}

	if (gEnv->menuData.updateRequired)
	{

		// update menu based on current state

	}

	if (gEnv->game.debug)
	{

		//sf::CircleShape f(120.f);
		//gEnv->globalWindow.draw(f);

		//tgui::Theme theme("D:/Projects/_project/TGUI/themes/Black.txt");
		//std::string t = gEnv->game.execDir + "\\themes\\Black.txt";
		tgui::Theme theme(gEnv->game.workDir + "\\Resources\\Themes\\Black.txt");

		auto button = tgui::Button::create();
		button->setRenderer(theme.getRenderer("Button"));
		button->setSize(100, 100);
		button->setPosition("(&.size - size)/2","(&.size - size) / 2");
		button->setText("A");
		button->setTextSize(72);
		gEnv->globalGui.add(button, "TestButton");

		tgui::Button::Ptr button2 = tgui::Button::copy(button);
		gEnv->globalGui.add(button2);
		button2->setPosition("TestButton.x", "TestButton.bottom + 100");
		
		
		
		gEnv->globalGui.draw();

	}

}
