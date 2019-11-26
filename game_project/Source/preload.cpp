#include "preload.h"
#include "envUtils.h"
#include "scriptSystem.h"

void preloadResources()
{

	scriptSystem = new ScriptSystem();
	gEnv->game.scriptSystemRequiresUpdate = true;
	// Create table for loading textures
	

	preloadModels();

	// Construction goes here...


}

void preloadModels()
{

	createModelDescriptor(L"blankTexture", "\\resources\\textures\\blankTexture.png");
	createModelDescriptor(L"blankTexture2", "\\resources\\textures\\blankTexture.png");
	createModelDescriptor(L"asteroidsSample", "\\resources\\textures\\world_decorations\\asteroids_sample.png");
	//createModelDescriptor(L"fsfa", "fsaf", true);
}

void postLoad()
{
	
}