#include "scriptUtilsUI.h"

void buttonWasClicked(int id)
{
	gEnv->scripts.buttonId = id;
	gEnv->scripts.buttonPressed = true;
}
