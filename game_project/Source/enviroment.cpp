#include "enviroment.h"
#include <windows.h>

GlobalEnviroment * globalEnviroment = nullptr;

void initEnviroment()
{

	// Firstly need to create globalEnviroment

	globalEnviroment = new GlobalEnviroment();

	// setup some variables

	char buffer[512];
	GetModuleFileName(NULL, buffer, 512);
	std::wstring::size_type pos = std::string(buffer).find_last_of("\\/");
	globalEnviroment->game.execDir = std::string(buffer).substr(0, pos);
	
	int length = GetCurrentDirectory(512, buffer);

	gEnv->game.workDir = std::string(buffer).substr(0, length);

	globalEnviroment->game.menuOverlayRequiresUpdate = true;

	gEnv->globalTheme.load(gEnv->game.workDir + "\\Resources\\Themes\\Black.txt");

	gEnv->game.activeGameMode = gameMode::loadingMode;

	gEnv->game.gameModesRequiredUpdate = true;

	gEnv->game.globalGUIeventsRequiresUpdate = true;

}
