#include "adventureModeCore.h"

void updateAdventureGameMode(double delteTime)
{

	//gEnv->game.adventureData.

	// draw 
	/*
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
		gEnv->game.adventureData.sectors["TEST"]->backgroundImage = L"testBackgroundSpace";
		gEnv->game.adventureData.sectors["TEST"]->objects.push_back(new MapDecoration());
		gEnv->game.adventureData.sectors["TEST"]->objects[0]->model = L"decorationSpaceDebris";
		gEnv->game.adventureData.sectors["TEST"]->objects[0]->scale = { 1,1 };
		gEnv->game.adventureData.sectors["TEST"]->objects[0]->rotation = 45;
		gEnv->game.adventureData.sectors["TEST"]->objects[0]->pos = { 300, 300 };
		buildDecoration(gEnv->game.adventureData.sectors["TEST"]->objects[0]);

		gEnv->game.adventureData.sectors["TEST"]->objects.push_back(new MapDecoration());
		gEnv->game.adventureData.sectors["TEST"]->objects[1]->model = L"decorationSpaceDebris";
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

		gEnv->game.adventureData.sectors["TEST"]->objects.push_back(new MapDecoration());
		gEnv->game.adventureData.sectors["TEST"]->objects[3]->model = L"decorationSpaceBeacon";
		gEnv->game.adventureData.sectors["TEST"]->objects[3]->scale = { 1,1 };
		gEnv->game.adventureData.sectors["TEST"]->objects[3]->rotation = 0;
		gEnv->game.adventureData.sectors["TEST"]->objects[3]->pos = { 0, 1100 };
		buildDecoration(gEnv->game.adventureData.sectors["TEST"]->objects[3]);

		// debug
		gEnv->game.gameCanPlayerMoveWASD = true;
		gEnv->game.gameCanPlayerTriggerMarkers = true;
		gEnv->game.player.cameraSpeed = 500;
		
		// testing markers

		gEnv->game.adventureData.sectors["TEST"]->markers.push_back(new MapMarker({ 400,400 }));
		buildMarker(gEnv->game.adventureData.sectors["TEST"]->markers[0]);
		gEnv->game.adventureData.sectors["TEST"]->markers[0]->name = L"Космические обломки";
		ScriptCompiler * c;
		ScriptDescriptor * q;
		std::string filename;
		filename = gEnv->game.workDir;
		filename += "\\resources\\scripts\\test\\test.esl";
		c = new ScriptCompiler();
		q = c->compileFile(filename, L"testMod");
		delete(c);

		gEnv->game.adventureData.sectors["TEST"]->markers[0]->sd = q;

		gEnv->game.adventureData.sectors["TEST"]->markers.push_back(new MapMarker({0 , -350 }));
		
		buildMarker(gEnv->game.adventureData.sectors["TEST"]->markers[1]);
		gEnv->game.adventureData.sectors["TEST"]->markers[1]->name = L"Небольшой гражданский корабль";
		filename = gEnv->game.workDir;
		filename += "\\resources\\scripts\\test\\shadowy_business_test.esl";
		c = new ScriptCompiler();
		q = c->compileFile(filename, L"testMod");
		delete(c);

		gEnv->game.adventureData.sectors["TEST"]->markers[1]->sd = q;

		gEnv->game.adventureData.sectors["TEST"]->markers.push_back(new MapMarker({ 0 , 1100 }));
		buildMarker(gEnv->game.adventureData.sectors["TEST"]->markers[2]);
		gEnv->game.adventureData.sectors["TEST"]->markers[2]->name = L"Неопознанный сигнал";
		filename = gEnv->game.workDir;
		filename += "\\resources\\scripts\\test\\demoEvent01.esl";
		c = new ScriptCompiler();
		q = c->compileFile(filename, L"testMod");
		delete(c);

		gEnv->game.adventureData.sectors["TEST"]->markers[2]->sd = q;

		gEnv->game.adventureData.sectors["TEST"]->markers.push_back(new MapMarker({ 2700 , 500 }));
		buildMarker(gEnv->game.adventureData.sectors["TEST"]->markers[3]);
		gEnv->game.adventureData.sectors["TEST"]->markers[3]->name = L"Обломки транспортного корабля";
		filename = gEnv->game.workDir;
		filename += "\\resources\\scripts\\test\\demoEvent02.esl";
		c = new ScriptCompiler();
		q = c->compileFile(filename, L"testMod");
		delete(c);

		gEnv->game.adventureData.sectors["TEST"]->markers[3]->sd = q;


		gEnv->game.adventureData.sectors["TEST"]->markers.push_back(new MapMarker({ 1500 , -100 }));
		buildMarker(gEnv->game.adventureData.sectors["TEST"]->markers[4]);
		gEnv->game.adventureData.sectors["TEST"]->markers[4]->name = L"Поле астероидов";
		filename = gEnv->game.workDir;
		filename += "\\resources\\scripts\\test\\demoEvent04.esl";
		c = new ScriptCompiler();
		q = c->compileFile(filename, L"testMod");
		delete(c);

		gEnv->game.adventureData.sectors["TEST"]->markers[4]->sd = q;

		
	//	buildSprite(&gEnv->game.player.shipModel, L"shipBase");
		buildSprite(&gEnv->game.player.shipModelIdle, L"shipBase");
		buildSprite(&gEnv->game.player.shipModelMove, L"shipBaseMove");
		gEnv->game.player.shipModel = gEnv->game.player.shipModelIdle;

		buildBackground(&gEnv->game.adventureData.bgImage, gEnv->game.adventureData.sectors["TEST"]->backgroundImage);

		filename = gEnv->game.workDir;
		filename += "\\resources\\scripts\\test\\demoEventIntro.esl";
		c = new ScriptCompiler();
		q = c->compileFile(filename, L"testMod");
		delete(c);

		//addScriptToQueue(q);
		
	}
	*/

	if (gEnv->game.adventureData.currentSectorId == "null")
	{
		gEnv->game.adventureData.currentSectorId = gEnv->game.adventureData.sectors.begin()->first;
		gEnv->game.adventureData.isSectorLoaded = false;
		// debug
		gEnv->game.gameCanPlayerMoveWASD = true;
		gEnv->game.gameCanPlayerTriggerMarkers = true;
		gEnv->game.player.cameraSpeed = 500;
		buildSprite(&gEnv->game.player.shipModelIdle, L"shipBase");
		buildSprite(&gEnv->game.player.shipModelMove, L"shipBaseMove");
		gEnv->game.player.shipModel = gEnv->game.player.shipModelIdle;
		//loadSector()

		// init ship and inventory
		ScriptCompiler * c;
		ScriptDescriptor * q;
		std::string filename;
		filename = gEnv->game.workDir;
		filename += "\\resources\\scripts\\test\\playerShipInit.esl";
		c = new ScriptCompiler();
		q = c->compileFile(filename, L"testMod");
		delete(c);

		addScriptToQueue(q);

	}

	if (!gEnv->game.adventureData.isSectorLoaded)
	{
		loadSector();
		gEnv->game.adventureData.isSectorLoaded = true;
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

	if (gEnv->game.gameCanPlayerMoveWASD && gEnv->game.player.shipMenu == shipMenu::null)
	{
		sf::Vector2f qMove = sf::Vector2f(0, 0);
		gEnv->game.player.PlayerShipMoving = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			//gEnv->game.player.cameraPosition.x -= delteTime * gEnv->game.player.cameraSpeed / gEnv->game.adventureData.settingMapScale;
			qMove.x -= 1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			//gEnv->game.player.cameraPosition.x += delteTime * gEnv->game.player.cameraSpeed / gEnv->game.adventureData.settingMapScale;
			qMove.x += 1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			//gEnv->game.player.cameraPosition.y -= delteTime * gEnv->game.player.cameraSpeed / gEnv->game.adventureData.settingMapScale;
			qMove.y -= 1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			//gEnv->game.player.cameraPosition.y += delteTime * gEnv->game.player.cameraSpeed / gEnv->game.adventureData.settingMapScale;
			qMove.y += 1;
		}

		if (qMove.x != 0 || qMove.y != 0)
		{
			gEnv->game.player.PlayerShipMoving = true;
			gEnv->game.player.shipModel = gEnv->game.player.shipModelMove;
			float angle = 0;
			if (qMove.x == 1)
			{
				if (qMove.y == 1)
				{
					angle = 45;
				}
				else
				{
					if (qMove.y == 0)
					{
						angle = 0;
					}
					else
					{
						angle = -45;
						// = -1
					}
				}
			}

			if (qMove.x == 0)
			{
				if (qMove.y == 1)
				{
					angle = 90;
				}
				else
				{

					angle = -90;
					// = -1
					
				}
			}

			if (qMove.x == -1)
			{
				if (qMove.y == 1)
				{
					angle = 45+90;
				}
				else
				{
					if (qMove.y == 0)
					{
						angle = 180;
					}
					else
					{
						angle = -90-45;
						// = -1
					}
				}
			}
			gEnv->game.player.shipAngle = angle;
			gEnv->game.player.shipModel->setRotation(angle);
		}
		else
		{
			gEnv->game.player.PlayerShipMoving = false;
			gEnv->game.player.shipModel = gEnv->game.player.shipModelIdle;
			gEnv->game.player.shipModel->setRotation(gEnv->game.player.shipAngle);
		}

		if (qMove.x != 0 && qMove.y != 0)
		{
			qMove.x /= 1.41;
			qMove.y /= 1.41;
		}
		gEnv->game.player.cameraPosition.x += qMove.x * delteTime * gEnv->game.player.cameraSpeed / gEnv->game.adventureData.settingMapScale;
		gEnv->game.player.cameraPosition.y += qMove.y * delteTime * gEnv->game.player.cameraSpeed / gEnv->game.adventureData.settingMapScale;
	}

	else if (gEnv->game.player.shipMenu == shipMenu::map)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			gEnv->game.ui.mapBiasX += 2;
			gEnv->game.ui.mapUpdateRequired = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			gEnv->game.ui.mapBiasX -= 2;
			gEnv->game.ui.mapUpdateRequired = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			gEnv->game.ui.mapBiasY += 2;
			gEnv->game.ui.mapUpdateRequired = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			gEnv->game.ui.mapBiasY -= 2;
			gEnv->game.ui.mapUpdateRequired = true;
		}
		if (gEnv->game.player.mouseWheelDelta != 0)
		{
			if (gEnv->game.player.mouseWheelDelta < 0)
			{
				if (gEnv->game.ui.mapScale < 20)
					gEnv->game.ui.mapScale -= gEnv->game.player.mouseWheelDelta;
			}
			else if (gEnv->game.player.mouseWheelDelta > 0)
			{
				if (gEnv->game.ui.mapScale > 2)
					gEnv->game.ui.mapScale -= gEnv->game.player.mouseWheelDelta;
			}
			gEnv->game.ui.mapUpdateRequired = true;
		}
		UpdateMapUI();
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
	if (gEnv->game.player.pickedItem != NULL)
	{
		gEnv->game.adventureGUI.get<tgui::BitmapButton>("pickedItemMouse")->setPosition(std::to_string(sf::Mouse::getPosition(gEnv->globalWindow).x + 10), std::to_string(sf::Mouse().getPosition(gEnv->globalWindow).y - 5));
	}
}

void drawAdventureGameMode(double deltaTime)
{
	// cannot draw if not loaded
	if (!gEnv->game.adventureData.isSectorLoaded)
		return;

	auto trg = gEnv->game.adventureData.sectors[gEnv->game.adventureData.currentSectorId];

	if (trg == NULL)
		return;

	// bg
	if (gEnv->game.adventureData.bgImage != NULL)
		gEnv->globalWindow.draw(*(gEnv->game.adventureData.bgImage));


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

	gEnv->game.player.shipPosition.x = gEnv->game.player.cameraPosition.x + gEnv->graphics.windowSizeX * gEnv->game.adventureData.settingMapScale / 2;
	gEnv->game.player.shipPosition.y = gEnv->game.player.cameraPosition.y + gEnv->graphics.windowSizeY * gEnv->game.adventureData.settingMapScale / 2;

	if (gEnv->game.player.shipModel != NULL)
	{
		updateSprite(gEnv->game.player.shipModel, gEnv->game.player.shipPosition);
		gEnv->globalWindow.draw(*gEnv->game.player.shipModel);
	}

	gEnv->game.player.HeavyUpdateTime += deltaTime;

	if (gEnv->game.player.HeavyUpdateTime > 0.250)
	{

		gEnv->game.player.HeavyUpdateTime = 0;

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
			// draw marker panel

			if (!gEnv->game.ui.markerDraw)
			{
				int x = gEnv->game.player.shipPosition.x;
				int y = gEnv->game.player.shipPosition.y;
				x /= gEnv->game.adventureData.settingMapScale;
				y /= gEnv->game.adventureData.settingMapScale;
				x -= (gEnv->game.player.cameraPosition.x / gEnv->game.adventureData.settingMapScale);
				y -= (gEnv->game.player.cameraPosition.y / gEnv->game.adventureData.settingMapScale);

				tgui::Panel::Ptr marker = tgui::Panel::create();
				marker->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
				marker->setSize(400, 100);
				marker->setPosition(x + 20, y + 20);
				gEnv->game.adventureGUI.add(marker, "eventMarker");

				tgui::Label::Ptr label = tgui::Label::create();
				label->setRenderer(gEnv->globalTheme.getRenderer("Label"));
				label->setText(trg->markers[id]->name);
				label->setTextSize(18);
				label->setPosition("(&.width - width) / 2", "5%");
				marker->add(label);


				tgui::Label::Ptr label2 = tgui::Label::create();
				label2->setRenderer(gEnv->globalTheme.getRenderer("Label"));
				label2->setText("Press Space to start event");
				label2->setTextSize(18);
				label2->setPosition("(&.width - width) / 2", "75%");
				marker->add(label2);
			}

			gEnv->game.ui.markerDraw = true;
			// trg->markers[id]



		}
		else
		{
			if (gEnv->game.ui.markerDraw)
			{
				gEnv->game.adventureGUI.remove(gEnv->game.adventureGUI.get<tgui::Panel>("eventMarker"));
				gEnv->game.ui.markerDraw = false;
			}
			//	printf("TEST\n");

				// no need to draw marker panel (markers too far)
		}

	}

	gEnv->game.adventureGUI.get<tgui::Panel>("minimap")->removeAllWidgets();
	tgui::Button::Ptr but = tgui::Button::create();
	but->setRenderer(gEnv->globalTheme.getRenderer("Button2"));
	gEnv->game.adventureGUI.get<tgui::Panel>("minimap")->add(but);
	but->setSize(15, 15);
	but->setPosition("(&.width - width) / 2", "(&.height - height) / 2");

	for (auto marker : trg->markers)
	{
		but = tgui::Button::create();
		but->setRenderer(gEnv->globalTheme.getRenderer("Button"));
		but->setSize(15, 15);

		tgui::Panel::Ptr lab = gEnv->game.adventureGUI.get<tgui::Panel>("minimap")->cast<tgui::Panel>();
		but->setPosition(((marker->pos.x - gEnv->game.player.shipPosition.x) / 15) + lab->getSize().x / 2 - 7.5, ((marker->pos.y - gEnv->game.player.shipPosition.y) / 10) + lab->getSize().y / 2 - 7.5);
		gEnv->game.adventureGUI.get<tgui::Panel>("minimap")->add(but);
	}

}

void loadSector()
{
	printf("info: Loading sector data...\n");

	//gEnv->game.adventureData.sectors[gEnv->game.adventureData.currentSectorId];
	auto p = gEnv->game.adventureData.sectors[gEnv->game.adventureData.currentSectorId];
	
	for (int i(0); i < p->objects.size(); i++)
	{
		buildDecoration(p->objects[i]);
	}

	for (int i(0); i < p->markers.size(); i++)
	{
		buildMarker(p->markers[i]);
	}

	if (p->backgroundImage != L"")
		buildBackground(&gEnv->game.adventureData.bgImage, p->backgroundImage);
	
	gEnv->game.player.cameraPosition.x = 0;
	gEnv->game.player.cameraPosition.y = 0;
}
