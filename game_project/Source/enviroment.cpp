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
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	globalEnviroment->game.execDir = std::string(buffer).substr(0, pos);

}
