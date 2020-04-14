#include "mainMenu.h"


void optionsClick();
void optionsBackButton();
void changeLanguage(tgui::Widget::Ptr widget, const std::string& signalName);

void updateMainMenu()
{
	if (gEnv->game.mainMenu.menuDrawRequired)
	{
		gEnv->globalGui.draw();

		//gEnv->scripts.scriptGui.draw();
		
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
			gEnv->globalGui.get<tgui::ComboBox>(L"languageComboBox")->setEnabled(true);
			gEnv->globalGui.get<tgui::ComboBox>(L"languageComboBox")->setVisible(true);
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

	tgui::ComboBox::Ptr languageComboBox = tgui::ComboBox::create();
	gEnv->globalGui.add(languageComboBox, "languageComboBox");
	gEnv->game.mainMenu.mainMenuWidgets.push_back(languageComboBox);
	languageComboBox->setRenderer(gEnv->globalTheme.getRenderer("ComboBox"));
	languageComboBox->setSize(100, 30);
	languageComboBox->setPosition("70%", "32%");
	languageComboBox->addItem(L"English");
	languageComboBox->addItem(L"Russian");
	languageComboBox->setSelectedItem("English");
	languageComboBox->setEnabled(false);
	languageComboBox->setVisible(false);
	languageComboBox->connect("ItemSelected", changeLanguage);

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

}

void startClick()
{

	gEnv->game.gameAdventureGUIRequiresUpdate = true;
	gEnv->game.adventureUI.adventureUIDrawRequired = true;
	disableAllMainMenuWidgets();
	gEnv->game.activeGameMode = gameMode::adventureMode;

	startWorldGeneration();

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
	/*
	std::vector<std::wstring> t;


	std::string filename;
	filename = gEnv->game.workDir;
	filename += "\\resources\\scripts\\test\\test.txt";

	std::wifstream wif(filename);
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstringstream wss;

	wss << wif.rdbuf();
	t.push_back(std::wstring(wss.str()));
	wss.clear();
	ScriptCompiler * c = new ScriptCompiler();
	c->setFamilyId(L"testMod");
	c->compileScriptText(t);

	addScriptToQueue(c->getScriptDescriptor());*/

	ScriptCompiler * c;
	ScriptDescriptor * q;
	std::string filename;
		
	//filename = gEnv->game.workDir;
	//filename += "\\resources\\scripts\\test\\ESL_CORE.esl";
	//c = new ScriptCompiler();
	//q = c->compileFile(filename, L"testMod");
	//delete(c);

	filename = gEnv->game.workDir;
	filename += "\\resources\\scripts\\test\\test.esl";
	c = new ScriptCompiler();
	q = c->compileFile(filename, L"testMod");
	delete(c);
	/*
	filename = gEnv->game.workDir;
	filename += "\\resources\\scripts\\test\\testCoreItem.esl";
	c = new ScriptCompiler();
	q = c->compileFile(filename, L"testMod");
	delete(c);
	
	filename = gEnv->game.workDir;
	filename += "\\resources\\scripts\\test\\test.esl";
	c = new ScriptCompiler();
	q = c->compileFile(filename, L"testMod");
	*/
	if (q != NULL)
		addScriptToQueue(q);

}

void btnNextPressed()
{ 
	gEnv->scripts.buttonPressed = true;
}

void changeLanguage(tgui::Widget::Ptr widget, const std::string& signalName)
{
	gEnv->game.locale.gameLanguage = widget->cast<tgui::ComboBox>()->getSelectedItem();
}
