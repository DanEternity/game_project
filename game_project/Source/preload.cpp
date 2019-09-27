#include "preload.h"
#include "envUtils.h"
#include "scriptSystem.h"

void preloadResources()
{

	scriptSystem = new ScriptSystem();

	// Create table for loading textures

	preloadModels();

	// Construction goes here...


}

void preloadModels()
{

	createModelDescriptor("blankTexture", "\\resources\\textures\\blankTexture.png");
	createModelDescriptor("blankTexture2", "\\resources\\textures\\blankTexture.png");
	//createModelDescriptor("fsfa", "fsaf", true);
}
