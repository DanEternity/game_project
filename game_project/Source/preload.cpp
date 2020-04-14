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
	//createModelDescriptor(L"fsfa", "fsaf", true);
}

void preloadScripts()
{
	//gEnv->game.loader.scriptFilenames.push_back("\\resources\\scripts\\ESL_CORE.esl");
	addScriptToPreloadQueue("\\resources\\scripts\\ESL_CORE.esl", L"core");

//	gEnv->game.loader.scriptFilenames.push_back("\\resources\\scripts\\Items\\Resources\\101_Iron.esl");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Resources\\101_Iron.esl", L"core");
//	gEnv->game.loader.scriptFilenames.push_back("\\resources\\scripts\\Items\\Resources\\102_Titan.esl");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Resources\\102_Titan.esl", L"core");


	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Resources\\111_Copper.esl", L"core");
	addScriptToPreloadQueue("\\resources\\scripts\\Items\\Resources\\112_Bismut.esl", L"core");
}

void postLoad()
{
	
}