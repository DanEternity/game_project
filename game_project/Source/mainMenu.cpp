#include "mainMenu.h"
#include "ShipModulesUI.h"
#include "tableInventory.h"
#include "personEquipmentUI.h"
#include "envUtils.h"
#include "scriptCompiler.h"
#include <fstream>
#include <sstream>
#include <codecvt>

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
			gEnv->globalGui.get<tgui::Button>(L"startButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>(L"startButton")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>(L"exitButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>(L"exitButton")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>(L"optionsButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>(L"optionsButton")->setVisible(true);
			break;
		case menuState::optionsActive:
			gEnv->globalGui.get<tgui::Label>(L"soundLabel")->setEnabled(true);
			gEnv->globalGui.get<tgui::Label>(L"soundLabel")->setVisible(true);
			gEnv->globalGui.get<tgui::Slider>(L"soundSlider")->setEnabled(true);
			gEnv->globalGui.get<tgui::Slider>(L"soundSlider")->setVisible(true);
			gEnv->globalGui.get<tgui::Label>(L"videoLabel")->setEnabled(true);
			gEnv->globalGui.get<tgui::Label>(L"videoLabel")->setVisible(true);
			gEnv->globalGui.get<tgui::ComboBox>(L"videoComboBox")->setEnabled(true);
			gEnv->globalGui.get<tgui::ComboBox>(L"videoComboBox")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>(L"optionsBack")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>(L"optionsBack")->setVisible(true);
			break;
		case menuState::exitActive:
			gEnv->globalGui.get<tgui::Button>(L"startButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>(L"startButton")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>(L"exitButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>(L"exitButton")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>(L"exitButtonYes")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>(L"exitButtonYes")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>(L"exitButtonNo")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>(L"exitButtonNo")->setVisible(true);
			gEnv->globalGui.get<tgui::Button>(L"optionsButton")->setEnabled(true);
			gEnv->globalGui.get<tgui::Button>(L"optionsButton")->setVisible(true);
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
	startButton->setText(L"Start");
	startButton->connect("MouseReleased", startClick);
	exitButton->setText(L"Exit");
	exitButton->connect("MouseReleased", exitClick);
	optionsButton->setText(L"Options");
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
	exitButtonYes->setText(L"Yes");
	exitButtonYes->setEnabled(false);
	exitButtonYes->setVisible(false);
	exitButtonYes->connect("MouseReleased", exitButtonsYes);

	gEnv->game.mainMenu.mainMenuWidgets.push_back(exitButtonNo);
	exitButtonNo->setSize(150, 150);
	exitButtonNo->setPosition("exitButton.right + 50", "exitButton.top");
	exitButtonNo->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	exitButtonNo->setText(L"No");
	exitButtonNo->setEnabled(false);
	exitButtonNo->setVisible(false);
	exitButtonNo->connect("MouseReleased", exitClick);
	
	
	//WIDGETS FOR OPTIONS

	tgui::Label::Ptr soundLabel = tgui::Label::create();
	gEnv->globalGui.add(soundLabel, "soundLabel");
	gEnv->game.mainMenu.mainMenuWidgets.push_back(soundLabel);
	soundLabel->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	soundLabel->setText(L"Sound: ");
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
	videoLabel->setText(L"Graphics: ");
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
	videoComboBox->addItem(L"Low");
	videoComboBox->addItem(L"Medium");
	videoComboBox->addItem(L"High");
	videoComboBox->addItem(L"Ultra");
	videoComboBox->setSelectedItem(L"Ultra");
	videoComboBox->setEnabled(false);
	videoComboBox->setVisible(false);

	tgui::Button::Ptr optionsBack = tgui::Button::create();
	gEnv->globalGui.add(optionsBack, "optionsBack");
	gEnv->game.mainMenu.mainMenuWidgets.push_back(optionsBack);
	optionsBack->setSize(200, 150);
	optionsBack->setPosition("45%", "60%");
	optionsBack->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	optionsBack->setText(L"Back");
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
	edb->setDefaultText(L"Click to edit text...");

	tgui::Label::Ptr label0 = tgui::Label::create();
	gEnv->globalGui.add(label0, "label");
	label0->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label0->setText(L"This is a label.");
	label0->setPosition(10, 90);
	label0->setTextSize(18);

	tgui::ListBox::Ptr lb = tgui::ListBox::create();
	gEnv->globalGui.add(lb);
	lb->setRenderer(gEnv->globalTheme.getRenderer("ListBox"));
	lb->setSize(250, 120);
	lb->setItemHeight(24);
	lb->setPosition(10, 340);
	lb->addItem(L"Item 1");
	lb->addItem(L"Item 2");
	lb->addItem(L"Item 3");

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
	comboBox->addItem(L"Item 1");
	comboBox->addItem(L"Item 2");
	comboBox->addItem(L"Item 3");
	comboBox->setSelectedItem(L"Item 2");
	gEnv->globalGui.add(comboBox);

	auto child = tgui::ChildWindow::create();
	child->setRenderer(gEnv->globalTheme.getRenderer("ChildWindow"));
	child->setSize(250, 120);
	child->setPosition(420, 80);
	child->setTitle(L"Child window");
	gEnv->globalGui.add(child);

	auto label = tgui::Label::create();
	label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label->setText(L"Hi! I'm a child window.");
	label->setPosition(30, 30);
	label->setTextSize(15);
	child->add(label);

	auto button = tgui::Button::create();
	button->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	button->setPosition(75, 70);
	button->setText(L"OK");
	button->setSize(100, 30);
	button->connect("pressed", [=]() { child->setVisible(false); });
	child->add(button);

	auto checkbox = tgui::CheckBox::create();
	checkbox->setRenderer(gEnv->globalTheme.getRenderer("CheckBox"));
	checkbox->setPosition(420, 240);
	checkbox->setText(L"Ok, I got it");
	checkbox->setSize(25, 25);
	gEnv->globalGui.add(checkbox);

	auto chatbox = tgui::ChatBox::create();
	chatbox->setRenderer(gEnv->globalTheme.getRenderer("ChatBox"));
	chatbox->setSize(300, 100);
	chatbox->setTextSize(18);
	chatbox->setPosition(420, 310);
	chatbox->setLinesStartFromTop();
	chatbox->addLine(L"texus: Hey, this is TGUI!", sf::Color::Green);
	chatbox->addLine(L"Me: Looks awesome! ;)", sf::Color::Yellow);
	chatbox->addLine(L"texus: Thanks! :)", sf::Color::Green);
	chatbox->addLine(L"Me: The widgets rock ^^", sf::Color::Yellow);
	gEnv->globalGui.add(chatbox);
	
	sf::Sprite sprite;

	sprite.setTexture(getModelDescriptor(L"blankTexture")->tex);
	sprite.setScale(200.f / getModelDescriptor(L"blankTexture")->tex.getSize().x, 140.f / getModelDescriptor(L"blankTexture")->tex.getSize().y);

	sf::Text text{ "SFML Canvas", *gEnv->globalGui.getFont(), 24 };
	text.setPosition(200, 200);
	text.setFillColor({ 255, 0, 0 });

	auto canvas = tgui::Canvas::create({ 200, 140 });
	canvas->setPosition(10, 10);
	canvas->clear();
	canvas->draw(sprite);
	canvas->draw(text);
	canvas->display();
	gEnv->globalGui.add(canvas);*/

	auto testbox = tgui::TextBox::create();
	testbox->setRenderer(gEnv->globalTheme.getRenderer("TextBox"));
	testbox->setText(L"ROFLAN EBALO WWWW");
	testbox->setPosition({ 50,50 });
	testbox->setReadOnly();
	testbox->setVisible(false);
	gEnv->scripts.scriptGui.add(testbox, "scriptTextMessage");
//	gEnv->globalGui.add(testbox);

	/* Do not delete */
	auto testButton = tgui::Button::create();
	testButton->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	testButton->setPosition({ "90%", "10%" });
	testButton->setText(L"TEST SCRIPT");
	testButton->connect("MouseReleased", testFunctionExecScript);
	//testButton->connect("MouseReleased", testFunctionCreateScript);
	gEnv->globalGui.add(testButton);
	/* Do not delete endregion */

	/*do not delete*/
	auto testButton2 = tgui::Button::create();
	testButton2->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	testButton2->setPosition({ "15%-40", "15%+50" });
	testButton2->setSize({"80", "40"});
	testButton2->setText(L"Next");
	testButton2->setEnabled(false);
	testButton2->setVisible(false);
	testButton2->connect("MouseReleased", btnNextPressed);	
	gEnv->scripts.scriptGui.add(testButton2, "ScriptButtonNext");
	/*endregion*/
	/*
	TableInventory* tblinv = new TableInventory();
	Item* it1 = new Item();
	it1->name = L"Item1";
	tblinv->addItem(it1);
	UIShipModules *uism = new UIShipModules(UIShipModules::shipType::eagle, 2);
	Module* md1 = new Module();
	md1->slot = moduleSlot::core;
	md1->name = L"supercore";
	uism->changeModule(md1, 0);
	*/

	gEnv->game.player.inventory.resize(50, nullptr);

	gEnv->game.player.inventory[2] = new Module();
	gEnv->game.player.inventory[2]->name = L"roflanEbalo";
	gEnv->game.player.inventory[2]->itemType = itemType::module;
	static_cast<Module*>(gEnv->game.player.inventory[2])->slot = moduleSlot::engine;

	gEnv->game.player.inventory[7] = new Module(); 
	static_cast<Module*>(gEnv->game.player.inventory[7])->slot = moduleSlot::hyperdrive;
	gEnv->game.player.inventory[7]->name = L"roflanContent";
	gEnv->game.player.inventory[5] = new Module();
	static_cast<Module*>(gEnv->game.player.inventory[5])->slot = moduleSlot::engine;
	gEnv->game.player.inventory[5]->name = L"roflanGorit";

	gEnv->game.player.inventory[0] = new Equipment();
	gEnv->game.player.inventory[0]->name = L"roflanTelo";
	static_cast<Equipment*>(gEnv->game.player.inventory[0])->equipmentSlotType = equipmentSlot::body;

	gEnv->game.player.inventory[11] = new Equipment();
	gEnv->game.player.inventory[11]->name = L"roflanBody";
	static_cast<Equipment*>(gEnv->game.player.inventory[11])->equipmentSlotType = equipmentSlot::body;

	BuildInventoryUI(10);

	gEnv->game.player.ship = new Ship();

	/* INITIALIZE SHIP SLOTS */
	gEnv->game.player.ship->slots.resize(5, moduleSlot::ModuleSlot());
	gEnv->game.player.ship->slots[0].type = moduleSlot::core;
	gEnv->game.player.ship->slots[1].type = moduleSlot::hyperdrive;
	gEnv->game.player.ship->slots[2].type = moduleSlot::engine;
	gEnv->game.player.ship->slots[3].type = moduleSlot::system;
	gEnv->game.player.ship->slots[4].type = moduleSlot::primaryWeapon;

	/* INITIALIZE SHIP BASE MODULES */
	gEnv->game.player.ship->modules.resize(5, nullptr);
	gEnv->game.player.ship->modules[0] = new Module();
	gEnv->game.player.ship->modules[0]->name = L"roflanPomoika";
	gEnv->game.player.ship->modules[0]->slot = moduleSlot::core;
	gEnv->game.player.ship->modules[0]->itemType = itemType::module;

	gEnv->game.player.ship->modules[1] = new Module();
	gEnv->game.player.ship->modules[1]->name = L"roflanVebenya";
	gEnv->game.player.ship->modules[1]->slot = moduleSlot::hyperdrive;
	gEnv->game.player.ship->modules[1]->itemType = itemType::module;

	gEnv->game.player.ship->modules[2] = new Module();
	gEnv->game.player.ship->modules[2]->name = L"roflanGorim";
	gEnv->game.player.ship->modules[2]->slot = moduleSlot::engine;
	gEnv->game.player.ship->modules[2]->itemType = itemType::module;

	gEnv->game.player.ship->modules[3] = new Module();
	gEnv->game.player.ship->modules[3]->name = L"roflanCompukter";
	gEnv->game.player.ship->modules[3]->slot = moduleSlot::system;
	gEnv->game.player.ship->modules[3]->itemType = itemType::module;

	gEnv->game.player.ship->modules[4] = new Module();
	gEnv->game.player.ship->modules[4]->name = L"roflanStrelyai";
	gEnv->game.player.ship->modules[4]->slot = moduleSlot::primaryWeapon;
	gEnv->game.player.ship->modules[4]->itemType = itemType::module;

	BuildShipSchemeUI(50);

	//gEnv->game.player.crew = new Crew();

	//gEnv->game.player.crew->shipCrew.resize(5, nullptr);
	//gEnv->game.player.crew->shipCrew[0] = new Person();
	//gEnv->game.player.crew->shipCrew[0]->personEquipment.resize(7, nullptr);

	gEnv->game.player.crew.characters.push_back(new Character());
	gEnv->game.player.crew.characters[0]->name = L"roflanDaun";
	gEnv->game.player.crew.characters[0]->slot.resize(7, equipmentSlot::head);
	gEnv->game.player.crew.characters[0]->slot[0] = equipmentSlot::head;
	gEnv->game.player.crew.characters[0]->slot[1] = equipmentSlot::body;
	gEnv->game.player.crew.characters[0]->slot[2] = equipmentSlot::arms;
	gEnv->game.player.crew.characters[0]->slot[3] = equipmentSlot::legs;
	gEnv->game.player.crew.characters[0]->slot[4] = equipmentSlot::universal;
	gEnv->game.player.crew.characters[0]->slot[5] = equipmentSlot::universal;
	gEnv->game.player.crew.characters[0]->slot[6] = equipmentSlot::universal;
	gEnv->game.player.crew.characters[0]->equipment.resize(7, nullptr);
	gEnv->game.player.crew.characters[0]->equipment[0] = new Equipment();
	gEnv->game.player.crew.characters[0]->equipment[0]->name = L"roflanBoshka";
	gEnv->game.player.crew.characters[0]->equipment[0]->equipmentSlotType = equipmentSlot::head;

	BuildPersonSchemeUI(50, 0);

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



}

void testFunctionExecScript()
{

	std::vector<std::wstring> t;

	//t.push_back(L"Put """"25"""" to """"$_abc"""" ");

	//t.push_back(L"Text ""Value abc = $_abc \n Sybmols: #%@%Y^H%&EIK*OO:"" ");

	std::string filename;
	filename = gEnv->game.workDir;
	filename += "\\resources\\scripts\\test\\test.txt";
	/*std::wifstream fin(filename);

	while (!fin.eof())
	{
		std::wstring line;
		std::getline(fin, line);
		t.push_back(line);
	}
	fin.close();*/
	std::wifstream wif(filename);
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstringstream wss;
	//while (!wif.eof())
	//{
	//	wss << wif.rdbuf();
	//	t.push_back(std::wstring(wss.str()));
	//	wss.clear();
	//}
	wss << wif.rdbuf();
	t.push_back(std::wstring(wss.str()));
	wss.clear();
	ScriptCompiler * c = new ScriptCompiler();

	c->compileScriptText(t);

	addScriptToQueue(c->getScriptDescriptor());

}

void btnNextPressed()
{
	gEnv->scripts.buttonPressed = true;
}
