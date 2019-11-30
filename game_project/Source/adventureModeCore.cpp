#include "adventureModeCore.h"

void updateAdventureGameMode()
{

	//gEnv->game.adventureData.

	// draw 
	if (gEnv->game.adventureData.currentSectorId == "null")
	{
		if (!debugMode)
		{
			printf("Error! Incorrect Sector reference\n");
			return;
		}
		// testing sectors

		gEnv->game.adventureData.currentSectorId = "TEST";
		gEnv->game.adventureData.sectors["TEST"] = new MapSector();

		gEnv->game.adventureData.sectors["TEST"]->objects.push_back(new MapDecoration());
		gEnv->game.adventureData.sectors["TEST"]->objects[0]->model = L"blankTexture2";
		gEnv->game.adventureData.sectors["TEST"]->objects[0]->scale = { 1,1 };
		gEnv->game.adventureData.sectors["TEST"]->objects[0]->rotation = 45;
		gEnv->game.adventureData.sectors["TEST"]->objects[0]->pos = { 300, 300 };
		buildDecoration(gEnv->game.adventureData.sectors["TEST"]->objects[0]);

		gEnv->game.adventureData.sectors["TEST"]->objects.push_back(new MapDecoration());
		gEnv->game.adventureData.sectors["TEST"]->objects[1]->model = L"blankTexture2";
		gEnv->game.adventureData.sectors["TEST"]->objects[1]->scale = { 1,1 };
		gEnv->game.adventureData.sectors["TEST"]->objects[1]->rotation = 70;
		gEnv->game.adventureData.sectors["TEST"]->objects[1]->pos = { 2700, 300 };
		buildDecoration(gEnv->game.adventureData.sectors["TEST"]->objects[1]);

		gEnv->game.adventureData.sectors["TEST"]->objects.push_back(new MapDecoration());
		gEnv->game.adventureData.sectors["TEST"]->objects[2]->model = L"asteroidsSample";
		gEnv->game.adventureData.sectors["TEST"]->objects[2]->scale = { 2,2 };
		gEnv->game.adventureData.sectors["TEST"]->objects[2]->rotation = 70;
		gEnv->game.adventureData.sectors["TEST"]->objects[2]->pos = { 1700, 0 };
		buildDecoration(gEnv->game.adventureData.sectors["TEST"]->objects[2]);

	}

	auto trg = gEnv->game.adventureData.sectors[gEnv->game.adventureData.currentSectorId];
	
	for (int i(0); i < trg->objects.size(); i++)
	{
		updateDecoration(trg->objects[i]);
		gEnv->globalWindow.draw(*(trg->objects[i]->sprite));
	}

	
	// update



}
