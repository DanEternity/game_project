#pragma once

#include "enviroment.h"

void gamemodeSystemLoader()
{

	if (gEnv->game.loader.pointer == gEnv->modelDB.end())
	{

		// Loading completed

		return;
	}

	// Load current texture

	if (gEnv->game.loader.pointer->second->status == modelStatus::notLoaded)
	{
		gEnv->game.loader.pointer->second->tex.loadFromFile(gEnv->game.loader.pointer->second->pathToFile);
	}

	// Move to next

	gEnv->game.loader.pointer++;

}