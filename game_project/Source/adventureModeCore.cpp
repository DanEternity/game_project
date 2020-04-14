#include "adventureModeCore.h"

void updateAdventureGameMode(double delteTime)
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

		// debug
		gEnv->game.gameCanPlayerMoveWASD = true;
		gEnv->game.gameCanPlayerTriggerMarkers = true;
		gEnv->game.player.cameraSpeed = 500;
		// testing markers

		gEnv->game.adventureData.sectors["TEST"]->markers.push_back(new MapMarker({ 900,900 }));
		buildMarker(gEnv->game.adventureData.sectors["TEST"]->markers[0]);

		ScriptCompiler * c;
		ScriptDescriptor * q;
		std::string filename;
		filename = gEnv->game.workDir;
		filename += "\\resources\\scripts\\test\\test.esl";
		c = new ScriptCompiler();
		q = c->compileFile(filename, L"testMod");
		delete(c);

		gEnv->game.adventureData.sectors["TEST"]->markers[0]->sd = q;

		gEnv->game.adventureData.sectors["TEST"]->markers.push_back(new MapMarker({0 , 0 }));
		buildMarker(gEnv->game.adventureData.sectors["TEST"]->markers[1]);

	}

	auto trg = gEnv->game.adventureData.sectors[gEnv->game.adventureData.currentSectorId];
	/*
	// Decorations

	for (int i(0); i < trg->objects.size(); i++)
	{
		updateDecoration(trg->objects[i]);
		gEnv->globalWindow.draw(*(trg->objects[i]->sprite));
	}

	// Markers

	for (int i(0); i < trg->markers.size(); i++)
	{
		updateMarker(trg->markers[i]);
		gEnv->globalWindow.draw(*(trg->markers[i]->sprite));
	}*/
	
	// update

	if (gEnv->game.gameCanPlayerMoveWASD)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			gEnv->game.player.cameraPosition.x -= delteTime * gEnv->game.player.cameraSpeed / gEnv->game.adventureData.settingMapScale;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			gEnv->game.player.cameraPosition.x += delteTime * gEnv->game.player.cameraSpeed / gEnv->game.adventureData.settingMapScale;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			gEnv->game.player.cameraPosition.y -= delteTime * gEnv->game.player.cameraSpeed / gEnv->game.adventureData.settingMapScale;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			gEnv->game.player.cameraPosition.y += delteTime * gEnv->game.player.cameraSpeed / gEnv->game.adventureData.settingMapScale;

	}

	if (gEnv->game.gameCanPlayerTriggerMarkers)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			gEnv->game.gameSpaceBarPressed = true;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gEnv->game.gameSpaceBarPressed)
		{

 			gEnv->game.gameSpaceBarPressed = false;

			float dist2 = 99999;

			int id = -1;

			float x, y;
			x = gEnv->game.player.cameraPosition.x + gEnv->graphics.windowSizeX * gEnv->game.adventureData.settingMapScale / 2;
			y = gEnv->game.player.cameraPosition.y + gEnv->graphics.windowSizeY * gEnv->game.adventureData.settingMapScale / 2;
			
	
			for (int i(0); i < trg->markers.size(); i++)
			{


				float dist = 
					(x - trg->markers[i]->pos.x) *
					(x - trg->markers[i]->pos.x) +
					(y - trg->markers[i]->pos.y) *
					(y - trg->markers[i]->pos.y);

				if (dist < dist2)
				{
					dist2 = dist;
					id = i;
				}



			}

			if (dist2 < 100 * 100)
			{
				if (debugMode)
					printf("Debug: Trigger marker event %i \n", id);

				auto t = trg->markers[id]->sd;
				if (t != NULL)
					addScriptToQueue(t);
			}

		}
	}

}

void drawAdventureGameMode(double deltaTime)
{
	auto trg = gEnv->game.adventureData.sectors[gEnv->game.adventureData.currentSectorId];
	
	if (trg == NULL)
		return;

	// Decorations

	for (int i(0); i < trg->objects.size(); i++)
	{
		updateDecoration(trg->objects[i]);
		gEnv->globalWindow.draw(*(trg->objects[i]->sprite));
	}

	// Markers

	for (int i(0); i < trg->markers.size(); i++)
	{
		updateMarker(trg->markers[i]);
		gEnv->globalWindow.draw(*(trg->markers[i]->sprite));
	}
}
