#include "preload.h"
#include "envUtils.h"
#include "scriptSystem.h"
#include "GameLogicCore.h"

void preloadResources()
{

	scriptSystem = new ScriptSystem();
	gEnv->game.scriptSystemRequiresUpdate = true;
	// Create table for loading textures
	

	preloadModels();

	LoadScriptTemplates();

	preloadScripts();

	// Construction goes here...


}

void preloadModels()
{

	createModelDescriptor(L"blankTexture", "\\resources\\textures\\blankTexture.png");
	createModelDescriptor(L"blankTexture2", "\\resources\\textures\\blankTexture.png");
	createModelDescriptor(L"asteroidsSample", "\\resources\\textures\\world_decorations\\asteroids_sample.png");
	createModelDescriptor(L"butText", "\\resources\\textures\\buttonTextureTest.png");
	createModelDescriptor(L"markerBase", "\\resources\\textures\\System\\Marker_Base.png");
	createModelDescriptor(L"shipBase", "\\resources\\textures\\Ships\\PlayerBase.png");
	createModelDescriptor(L"shipBaseMove", "\\resources\\textures\\Ships\\PlayerBaseMove.png");
	createModelDescriptor(L"testBackgroundSpace", "\\resources\\textures\\World_Decorations\\spaceBG.jpg");
	createModelDescriptor(L"decorationSpaceDebris", "\\resources\\textures\\World_Decorations\\spaceDebris01.png");
	createModelDescriptor(L"decorationSpaceBeacon", "\\resources\\textures\\World_Decorations\\spaceBeacon01.png");


	//Item textures
	createModelDescriptor(L"itemEngine", "\\resources\\textures\\Items\\Engine.png");
	createModelDescriptor(L"itemCore", "\\resources\\textures\\Items\\Core.png");
	createModelDescriptor(L"itemHyperdrive", "\\resources\\textures\\Items\\Hyperdrive.png");
	createModelDescriptor(L"itemSystem", "\\resources\\textures\\Items\\System.png");
	createModelDescriptor(L"itemDefault", "\\resources\\textures\\Items\\Standart.png");
	createModelDescriptor(L"itemEmpty", "\\resources\\textures\\Items\\Empty.png");
	//createModelDescriptor(L"fsfa", "fsaf", true);
}

void preloadScripts()
{
	//gEnv->game.loader.scriptFilenames.push_back("\\resources\\scripts\\ESL_CORE.esl");
	addScriptToPreloadQueue("\\resources\\scripts\\ESL_CORE.esl", L"core");

	// resources templaetes
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Resources\\101_Iron.esl", L"core");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Resources\\102_Titan.esl", L"core");


	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Resources\\111_Copper.esl", L"core");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Resources\\112_Bismut.esl", L"core");

	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Resources\\121_Uranium.esl", L"core");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Resources\\122_Plutonium.esl", L"core");


	// modules template
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Modules\\PropertiesCollection\\1001_BasicReactor_PC.esl", L"core");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Modules\\1001_BasicReactor.esl", L"core");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Modules\\PropertiesCollection\\1011_BasicEngine_PC.esl", L"core");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Modules\\1011_BasicEngine.esl", L"core");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Modules\\PropertiesCollection\\1021_BasicSystem_PC.esl", L"core");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Modules\\1021_BasicSystem.esl", L"core");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Modules\\PropertiesCollection\\1031_BasicHyperdrive_PC.esl", L"core");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Modules\\1031_BasicHyperdrive.esl", L"core");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Modules\\PropertiesCollection\\1041_BasicSensor_PC.esl", L"core");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Modules\\1041_BasicSensor.esl", L"core");
	// sector templates
	// addScriptToPreloadQueue("\\resources\\scripts\\\World\\SectorTemplates\\Test2.esl", L"core");

	// collections

	addScriptToPreloadQueue("\\resources\\scripts\\World\\Collections\\level1-5CommonModule.esl", L"core");
	addScriptToPreloadQueue("\\resources\\scripts\\World\\Collections\\level1-5CommonResource.esl", L"core");
}

void postLoad()
{
	
}