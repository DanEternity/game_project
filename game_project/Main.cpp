#include <SFML/Graphics.hpp>
#include <TGUI/tGui.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	tgui::Gui gui(window);

	tgui::Theme theme{ "G:/Projects/_project/TGUI/themes/Black.txt" };

	tgui::TextBox::Ptr textbox = tgui::TextBox::create();
	textbox->setPosition(100, 50);
	textbox->setSize(300, 200);
	textbox->setTextSize(16);
	textbox->setText("fdsfgsfdgdfgd\nfgdfgdfgdfgdfg");
	gui.add(textbox);

	auto tabs = tgui::Tabs::create();
	tabs->setRenderer(theme.getRenderer("Tabs"));
	tabs->setTabHeight(30);
	tabs->setPosition(570, 540);
	tabs->add("Tab - 1");
	tabs->add("Tab - 2");
	tabs->add("Tab - 3");
	gui.add(tabs);

	auto menu = tgui::MenuBar::create();
	menu->setRenderer(theme.getRenderer("MenuBar"));
	menu->setSize(static_cast<float>(window.getSize().x), 22.f);
	menu->addMenu("File");
	menu->addMenuItem("Load");
	menu->addMenuItem("Save");
	menu->addMenuItem("Exit");
	menu->addMenu("Edit");
	menu->addMenuItem("Copy");
	menu->addMenuItem("Paste");
	menu->addMenu("Help");
	menu->addMenuItem("About");
	gui.add(menu);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		gui.draw();
		window.display();
	}

	return 0;
}