#include "mainMenu.h"
#include "enviroment.h"
#include "envUtils.h"

void optionsClick();
void optionsBackButton();

void updateMainMenu()
{
	if (gEnv->game.mainMenu.menuDrawRequired)
	{
		gEnv->globalGui.draw();

		gEnv->scripts.scriptGui.draw();

		
	}

	if (gEnv->game.mainMenu.widgetDisable)
	{
		disableAllMainMenuWidgets();
		gEnv->game.mainMenu.widgetDisable = false;
	}
}

void disableAllMainMenuWidgets()
{
	for (const auto& widget : gEnv->game.mainMenu.mainMenuWidgets)
	{
		widget->setVisible(false);
		widget->setEnabled(false);
	}
}


void mainMenuChangeState()
{
	disableAllMainMenuWidgets();
	switch (gEnv->game.mainMenu.active)
	{
		case menuState::mainMenu:
			gEnv->globalGui.get<tgui::Button>("startButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("startButton")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>("exitButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("exitButton")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>("optionsButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("optionsButton")->setVisible(true);
			break;
		case menuState::optionsActive:
			gEnv->globalGui.get<tgui::Label>("soundLabel")->setEnabled(true);
			gEnv->globalGui.get<tgui::Label>("soundLabel")->setVisible(true);
			gEnv->globalGui.get<tgui::Slider>("soundSlider")->setEnabled(true);
			gEnv->globalGui.get<tgui::Slider>("soundSlider")->setVisible(true);
			gEnv->globalGui.get<tgui::Label>("videoLabel")->setEnabled(true);
			gEnv->globalGui.get<tgui::Label>("videoLabel")->setVisible(true);
			gEnv->globalGui.get<tgui::ComboBox>("videoComboBox")->setEnabled(true);
			gEnv->globalGui.get<tgui::ComboBox>("videoComboBox")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>("optionsBack")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("optionsBack")->setVisible(true);
			break;
		case menuState::exitActive:
			gEnv->globalGui.get<tgui::Button>("startButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("startButton")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>("exitButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("exitButton")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>("exitButtonYes")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("exitButtonYes")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>("exitButtonNo")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("exitButtonNo")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>("optionsButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>("optionsButton")->setVisible(true);
			break;
		default:
			break;
	}
	
}

void createMenuButtons()
{
	tgui::Button::Ptr startButton = tgui::Button::create();
	tgui::Button::Ptr optionsButton = tgui::Button::create();
	tgui::Button::Ptr exitButton = tgui::Button::create();
	tgui::Button::Ptr exitButtonYes = tgui::Button::create();
	tgui::Button::Ptr exitButtonNo = tgui::Button::create();
	gEnv->globalGui.add(startButton, "startButton");
	gEnv->globalGui.add(exitButton, "exitButton");
	gEnv->globalGui.add(optionsButton, "optionsButton");
	gEnv->globalGui.add(exitButtonYes, "exitButtonYes");
	gEnv->globalGui.add(exitButtonNo, "exitButtonNo");
	startButton->setText("Start");
	startButton->connect("MouseReleased", startClick);
	exitButton->setText("Exit");
	exitButton->connect("MouseReleased", exitClick);
	optionsButton->setText("Options");
	optionsButton->connect("MouseReleased", optionsClick);
	gEnv->game.mainMenu.mainMenuWidgets.push_back(startButton);
	gEnv->game.mainMenu.mainMenuWidgets.push_back(optionsButton);
	gEnv->game.mainMenu.mainMenuWidgets.push_back(exitButton);
	int i = 0;
	for (const auto& widget : gEnv->game.mainMenu.mainMenuWidgets)
	{
		widget->setSize(300, 150);
		widget->setPosition("(&.size - size) / 2", 200 + i * 200);
		widget->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		i++;
	}

	gEnv->game.mainMenu.mainMenuWidgets.push_back(exitButtonYes);
	exitButtonYes->setSize(150, 150);
	exitButtonYes->setPosition("exitButton.left - 200", "exitButton.top");
	exitButtonYes->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	exitButtonYes->setText("Yes");
	exitButtonYes->setEnabled(false);
	exitButtonYes->setVisible(false);
	exitButtonYes->connect("MouseReleased", exitButtonsYes);

	gEnv->game.mainMenu.mainMenuWidgets.push_back(exitButtonNo);
	exitButtonNo->setSize(150, 150);
	exitButtonNo->setPosition("exitButton.right + 50", "exitButton.top");
	exitButtonNo->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	exitButtonNo->setText("No");
	exitButtonNo->setEnabled(false);
	exitButtonNo->setVisible(false);
	exitButtonNo->connect("MouseReleased", exitClick);
	
	
	//WIDGETS FOR OPTIONS

	tgui::Label::Ptr soundLabel = tgui::Label::create();
	gEnv->globalGui.add(soundLabel, "soundLabel");
	gEnv->game.mainMenu.mainMenuWidgets.push_back(soundLabel);
	soundLabel->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	soundLabel->setText("Sound: ");
	soundLabel->setTextSize(48);
	soundLabel->setPosition("30%", "20%");
	soundLabel->setEnabled(false);
	soundLabel->setVisible(false);

	tgui::Slider::Ptr soundSlider = tgui::Slider::create();
	gEnv->globalGui.add(soundSlider, "soundSlider");
	gEnv->game.mainMenu.mainMenuWidgets.push_back(soundSlider);
	soundSlider->setRenderer(gEnv->globalTheme.getRenderer("Slider"));
	soundSlider->setPosition("45%", "22%");
	soundSlider->setSize(220, 20);
	soundSlider->setValue(10);
	soundSlider->setVisible(false);
	soundSlider->setEnabled(false);

	tgui::Label::Ptr videoLabel = tgui::Label::create();
	gEnv->globalGui.add(videoLabel, "videoLabel");
	gEnv->game.mainMenu.mainMenuWidgets.push_back(videoLabel);
	videoLabel->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	videoLabel->setText("Graphics: ");
	videoLabel->setTextSize(48);
	videoLabel->setPosition("30%", "30%");
	videoLabel->setEnabled(false);
	videoLabel->setVisible(false);

	tgui::ComboBox::Ptr videoComboBox = tgui::ComboBox::create();
	gEnv->globalGui.add(videoComboBox, "videoComboBox");
	gEnv->game.mainMenu.mainMenuWidgets.push_back(videoComboBox);
	videoComboBox->setRenderer(gEnv->globalTheme.getRenderer("ComboBox"));
	videoComboBox->setSize(100, 30);
	videoComboBox->setPosition("50%", "32%");
	videoComboBox->addItem("Low");
	videoComboBox->addItem("Medium");
	videoComboBox->addItem("High");
	videoComboBox->addItem("Ultra");
	videoComboBox->setSelectedItem("Ultra");
	videoComboBox->setEnabled(false);
	videoComboBox->setVisible(false);

	tgui::Button::Ptr optionsBack = tgui::Button::create();
	gEnv->globalGui.add(optionsBack, "optionsBack");
	gEnv->game.mainMenu.mainMenuWidgets.push_back(optionsBack);
	optionsBack->setSize(200, 150);
	optionsBack->setPosition("45%", "60%");
	optionsBack->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	optionsBack->setText("Back");
	optionsBack->setEnabled(false);
	optionsBack->setVisible(false);
	optionsBack->connect("MouseReleased", optionsBackButton);


	//TESTS TESTS TESTS

	/*tgui::EditBox::Ptr edb = tgui::EditBox::create();
	gEnv->globalGui.add(edb, "editBox");
	edb->setRenderer(gEnv->globalTheme.getRenderer("EditBox"));
	edb->setSize(200, 50);
	edb->setTextSize(18);
	edb->setPosition(10, 270);
	edb->setDefaultText("Click to edit text...");

	tgui::Label::Ptr label0 = tgui::Label::create();
	gEnv->globalGui.add(label0, "label");
	label0->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label0->setText("This is a label.");
	label0->setPosition(10, 90);
	label0->setTextSize(18);

	tgui::ListBox::Ptr lb = tgui::ListBox::create();
	gEnv->globalGui.add(lb);
	lb->setRenderer(gEnv->globalTheme.getRenderer("ListBox"));
	lb->setSize(250, 120);
	lb->setItemHeight(24);
	lb->setPosition(10, 340);
	lb->addItem("Item 1");
	lb->addItem("Item 2");
	lb->addItem("Item 3");

	tgui::ProgressBar::Ptr pb = tgui::ProgressBar::create();
	gEnv->globalGui.add(pb);
	pb->setRenderer(gEnv->globalTheme.getRenderer("ProgressBar"));
	pb->setPosition(10, 500);
	pb->setSize(200, 20);
	pb->setValue(50);

	tgui::Slider::Ptr sl = tgui::Slider::create();
	gEnv->globalGui.add(sl);
	sl->setRenderer(gEnv->globalTheme.getRenderer("Slider"));
	sl->setPosition(10, 560);
	sl->setSize(200, 18);
	sl->setValue(4);

	auto scrollbar = tgui::Scrollbar::create();
	scrollbar->setRenderer(gEnv->globalTheme.getRenderer("Scrollbar"));
	scrollbar->setPosition(380, 40);
	scrollbar->setSize(18, 540);
	scrollbar->setMaximum(100);
	scrollbar->setViewportSize(70);
	gEnv->globalGui.add(scrollbar);

	auto comboBox = tgui::ComboBox::create();
	comboBox->setRenderer(gEnv->globalTheme.getRenderer("ComboBox"));
	comboBox->setSize(120, 21);
	comboBox->setPosition(420, 40);
	comboBox->addItem("Item 1");
	comboBox->addItem("Item 2");
	comboBox->addItem("Item 3");
	comboBox->setSelectedItem("Item 2");
	gEnv->globalGui.add(comboBox);

	auto child = tgui::ChildWindow::create();
	child->setRenderer(gEnv->globalTheme.getRenderer("ChildWindow"));
	child->setSize(250, 120);
	child->setPosition(420, 80);
	child->setTitle("Child window");
	gEnv->globalGui.add(child);

	auto label = tgui::Label::create();
	label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label->setText("Hi! I'm a child window.");
	label->setPosition(30, 30);
	label->setTextSize(15);
	child->add(label);

	auto button = tgui::Button::create();
	button->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	button->setPosition(75, 70);
	button->setText("OK");
	button->setSize(100, 30);
	button->connect("pressed", [=]() { child->setVisible(false); });
	child->add(button);

	auto checkbox = tgui::CheckBox::create();
	checkbox->setRenderer(gEnv->globalTheme.getRenderer("CheckBox"));
	checkbox->setPosition(420, 240);
	checkbox->setText("Ok, I got it");
	checkbox->setSize(25, 25);
	gEnv->globalGui.add(checkbox);

	auto chatbox = tgui::ChatBox::create();
	chatbox->setRenderer(gEnv->globalTheme.getRenderer("ChatBox"));
	chatbox->setSize(300, 100);
	chatbox->setTextSize(18);
	chatbox->setPosition(420, 310);
	chatbox->setLinesStartFromTop();
	chatbox->addLine("texus: Hey, this is TGUI!", sf::Color::Green);
	chatbox->addLine("Me: Looks awesome! ;)", sf::Color::Yellow);
	chatbox->addLine("texus: Thanks! :)", sf::Color::Green);
	chatbox->addLine("Me: The widgets rock ^^", sf::Color::Yellow);
	gEnv->globalGui.add(chatbox);
	*/
	sf::Sprite sprite;

	sprite.setTexture(getModelDescriptor("blankTexture")->tex);
	sprite.setScale(200.f / getModelDescriptor("blankTexture")->tex.getSize().x, 140.f / getModelDescriptor("blankTexture")->tex.getSize().y);

	sf::Text text{ "SFML Canvas", *gEnv->globalGui.getFont(), 24 };
	text.setPosition(200, 200);
	text.setFillColor({ 255, 0, 0 });

	auto canvas = tgui::Canvas::create({ 200, 140 });
	canvas->setPosition(10, 10);
	canvas->clear();
	canvas->draw(sprite);
	canvas->draw(text);
	canvas->display();
	gEnv->globalGui.add(canvas);

	auto testbox = tgui::TextBox::create();
	testbox->setRenderer(gEnv->globalTheme.getRenderer("TextBox"));
	testbox->setText("ROFLAN EBALO WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
	testbox->setPosition({ 50,50 });
	testbox->setReadOnly();
	gEnv->scripts.scriptGui.add(testbox, "scriptTextMessage");
//	gEnv->globalGui.add(testbox);

	/* Do not delete */
	auto testButton = tgui::Button::create();
	testButton->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	testButton->setPosition({ "90%", "10%" });
	testButton->setText("TEST SCRIPT");
	testButton->connect("MouseReleased", testFunctionCreateScript);
	gEnv->globalGui.add(testButton);
	/* Do not delete endregion */

}

void startClick()
{
	
}

void exitClick()
{
	gEnv->game.mainMenu.sureExit = !gEnv->game.mainMenu.sureExit;
	if (gEnv->game.mainMenu.sureExit)
	{
		gEnv->game.mainMenu.active = menuState::exitActive;
	}
	else
	{
		gEnv->game.mainMenu.active = menuState::mainMenu;
	}
	mainMenuChangeState();
}

void optionsClick()
{
	gEnv->game.mainMenu.active = menuState::optionsActive;
	mainMenuChangeState();
}

void exitButtonsYes()
{
	gEnv->globalWindow.close();
}

void optionsBackButton()
{
	gEnv->game.mainMenu.active = menuState::mainMenu;
	mainMenuChangeState();
}

void testFunctionCreateScript()
{

	ScriptDescriptor * s = createScriptDescriptor();

	PutScript * ptr;
	TextScript * ptr2;

	// Put "25" to "$_1"
	ptr = static_cast<PutScript*>(createScriptCommand(scriptType::put));
	ptr->scr = "12 iq";
	ptr->dest = "$_1";
	s->scriptLines.push_back(ptr);

	// Put "$_1" to "$_2"
	ptr = static_cast<PutScript*>(createScriptCommand(scriptType::put));
	ptr->scr = "$_1";
	ptr->dest = "$_2";
	s->scriptLines.push_back(ptr);

	// Put "35" to "$_2"
	ptr = static_cast<PutScript*>(createScriptCommand(scriptType::put));
	ptr->scr = "35";
	ptr->dest = "$_2";
	s->scriptLines.push_back(ptr);

	// Text "Fisrt = $_1 ; Second = $_2"
	ptr2 = static_cast<TextScript*>(createScriptCommand(scriptType::text));
	ptr2->text = "Fisrt = $_1 ; Second = $_2";
	s->scriptLines.push_back(ptr2);

	//
	// Put "QWERT" to ""
	// $ - variable
	// _ - local variable
	// $_
	// $EXT - external table
	// $EXT:FFFFF:1234 FFFFF - tableID , 1234 - value name
	// $fgdgdfgdfgdfg - game enviroment
	// "123"
	// "123.1"
	// "12 iq"
	//

	addScriptToQueue(s);

}

void testFunctionExecScript()
{
}
