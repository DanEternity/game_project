#include "spaceBattleCore.h"

void updateSpaceBattle(double deltaTime)
{
	
	auto sb = &gEnv->game.spaceBattle;

	// draw battlefield
	if (sb->state == "init")
	{
		createSpaceBattleUI();

		float sizeX, sizeY;
		sizeX = 442;
		sizeY = 512;
		// graphics
		sb->backgroundImage = new sf::Sprite(gEnv->modelDB[L"testBackgroundSpace"]->tex);

		sb->mapSegment = new sf::Sprite(gEnv->modelDB[L"spaceBattleMapSegment"]->tex);
		sb->mapSegment->setOrigin(sizeX / 2, sizeY / 2);
		sb->mapSegmentHover = new sf::Sprite(gEnv->modelDB[L"spaceBattleMapSegmentHover"]->tex);
		sb->mapSegmentHover->setOrigin(sizeX / 2, sizeY / 2);

		sb->mapSegmentPlayer = new sf::Sprite(gEnv->modelDB[L"spaceBattleMapSegmentPlayer"]->tex);
		sb->mapSegmentPlayer->setOrigin(sizeX / 2, sizeY / 2);

		sb->mapSegmentNeutral = new sf::Sprite(gEnv->modelDB[L"spaceBattleMapSegmentNeutral"]->tex);
		sb->mapSegmentNeutral->setOrigin(sizeX / 2, sizeY / 2);

		sb->mapSegmentEnemy = new sf::Sprite(gEnv->modelDB[L"spaceBattleMapSegmentEnemy"]->tex);
		sb->mapSegmentEnemy->setOrigin(sizeX / 2, sizeY / 2);

		sb->mapPathMarker = new sf::Sprite(gEnv->modelDB[L"spaceBattleMapSegmentMovement"]->tex);
		sb->mapPathMarker->setOrigin(sf::Vector2f(sb->mapPathMarker->getTexture()->getSize()) / 2.0f);

	//	sb->mapSegment->setScale
		//sb->mapSegment->setPosition;


		//for (int i(0); i < sb->maxLines; i++)
		//{
		//	sb->map.push_back(std::vector<SpaceBattleSegment * >());
		//	for (int j(0); j < sb->maxLength; j++)
		//	{
		//		sb->map[i].push_back(new SpaceBattleSegment());
		//		if (i % 2 == 0)
		//			sb->map[i][j]->gameX = 0.5f + j;
		//		else
		//			sb->map[i][j]->gameX = 1.f + j;
		//		sb->map[i][j]->gameY = 0.557f + (i * 0.557f * 1.5f);
		//	}
		//}

		//Ship * testShip = new Ship();
		//testShip->model = new sf::Sprite(gEnv->modelDB[L"decorationSpaceBeacon"]->tex);
		//testShip->model->setOrigin(sf::Vector2f(testShip->model->getTexture()->getSize()) / 2.0f);
		//testShip->factionId = 2; // TEST
		//sb->map[8][8]->ships.push_back(testShip);
		//sb->map[8][8]->color = segmentColor::enemy;

		//sb->map[8][4]->color = segmentColor::player;
		//gEnv->game.player.ship->model = new sf::Sprite(gEnv->modelDB[L"shipBase"]->tex);
		//gEnv->game.player.ship->model->setOrigin(sf::Vector2f(gEnv->game.player.ship->model->getTexture()->getSize()) / 2.0f);
		////gEnv->game.player.ship->model->rotate(90);
		//sb->map[8][4]->ships.push_back(gEnv->game.player.ship);
		//gEnv->game.player.ship->factionId = 1;

		//sb->map[7][8]->color = segmentColor::neutral;

		gEnv->game.gameSpaceBattleGUIRequiresUpdate = true;

		// debug
		spaceBattle::initBattle();

		sb->state = "idle";
		sb->turnStatus = spaceBattleState::endTurn; // start new turn
	}

	if (sb->state == "idle")
	{

		sb->actionCooldown = (sb->actionCooldown <= 0) ? 0 : sb->actionCooldown - 1;

		/* Map coordinates, segments, scale and other stuff */

		auto mousePos = sf::Mouse::getPosition(gEnv->globalWindow);
		int pickX = -1, pickY = -1;
		float minDist = 999999999;


		float scale = sb->scale;
		float x, y;

		x = sb->cameraX  - (gEnv->graphics.windowSizeX * scale / 2);
		y = sb->cameraY  - (gEnv->graphics.windowSizeY * scale / 2);

		//x = gEnv->game.player.cameraPosition.x * 2;
		//y = gEnv->game.player.cameraPosition.y * 2;
		float dx, dy;
		dx = 450;
		dy = 390;

		float subLineOffset;
		subLineOffset = 225;

		x = x / scale;
		y = y / scale;
		dx = dx / scale;
		dy = dy / scale;
	//	sizeX /= scale;
	//	sizeY /= scale;

		subLineOffset = subLineOffset / scale;

		sb->mapSegment->setScale(1.f / scale, 1.f / scale);
		sb->mapSegmentHover->setScale(1.f / scale, 1.f / scale);
		sb->mapSegmentPlayer->setScale(1.f / scale, 1.f / scale);
		sb->mapSegmentEnemy->setScale(1.f / scale, 1.f / scale);
		sb->mapSegmentNeutral->setScale(1.f / scale, 1.f / scale);
		sb->mapPathMarker->setScale(1.f / scale, 1.f / scale);

		/* Selecting segment (hover) */

		for (int qy = 0; qy < sb->maxLines; qy++)
		{
			for (int qx = 0; qx < sb->maxLength; qx++)
			{
				int mx, my;

				if (qy % 2 == 1)
				{
					mx = -x + dx * qx + subLineOffset;
					my = -y + dy * qy;
				}
					
				else
				{
					mx = -x + dx * qx;
					my = -y + dy * qy;
				}
				
				sb->map[qy][qx]->screenX = mx;
				sb->map[qy][qx]->screenY = my;

				float dist = ((mx - mousePos.x)*(mx - mousePos.x)) + ((my - mousePos.y)*(my - mousePos.y));
				if (dist < (220 * 220 / scale / scale) && dist < minDist)
				{
					pickX = qx;
					pickY = qy;
					minDist = dist;
				}

			}
		}

		if (sb->turnStatus == spaceBattleState::primary)
		{

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sb->leftMBPressed = true;
			}

			/* Selecting segment (Click) */
			if (pickX != -1)
			{
				// selecting ship action
				if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && sb->leftMBPressed)
				{
					if (sb->map[pickY][pickX]->ships.size() > 0)
					{
						sb->selected = true;
						sb->SelectI = pickY;
						sb->SelectJ = pickX;
						sb->SelectedShipId = 0;
						//hideShipInfo();
						displayShipInfo();
						showBars();
						buttonShipInfo();
						createActiveModulesButtons();
						if (debugMode)
							printf("Info: selected ship in segment: %i, %i \n", pickY, pickX);
					}
				}
			}

			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sb->leftMBPressed = false;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sb->rightMBPressed = true;
			}

			// Move ship to destination
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && sb->rightMBPressed)
			{
				float mobility = sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId]->mobility.total;
				float cost = 40 / (mobility / 100 + 1);
				cost *= sb->currentPath.size();

				if (sb->showPath && sb->currentPath.size() > 0 && pickX != -1 && sb->actionCooldown == 0 && sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId]->actionPoints.current >= cost)
				{
					sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId]->actionPoints.current -= cost;

					// move ship to destination 
					spaceBattle::teleportShip(sb->SelectI, sb->SelectJ, pickY, pickX, sb->SelectedShipId);
					

					//sb->selected = false;
					sb->SelectI = pickY;
					sb->SelectJ = pickX;
					
					//hideShipInfo();
					displayShipInfo();

					sb->showPath = false;

					if (sb->miniWindowEmptyCreated)
					{
						sb->miniWindowEmptyCreated = false;
						// hideWindow
						hideMiniWindowHex();
					}

					if (sb->miniWindowCreated)
						hideMiniWindowShipStats();

					buildMiniWindowShipStats(sb->map[pickY][pickX]->screenX + 25, sb->map[pickY][pickX]->screenY, sb->map[pickY][pickX]->ships[0]);
					sb->miniWindowCreated = true;

					sb->actionCooldown = 5;
					showBars();
				}
			}

			if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sb->rightMBPressed = false;
			}

			drawSpaceBattle(deltaTime);

			if (pickX == -1)
			{

				sb->showPath = false;

				if (sb->miniWindowCreated)
				{
					sb->miniWindowCreated = false;
					hideMiniWindowShipStats();
				}
				if (sb->miniWindowEmptyCreated)
				{
					sb->miniWindowEmptyCreated = false;
					// hideWindow
					hideMiniWindowHex();
				}
			}
			else
				if (sb->pickI != pickY || sb->pickJ != pickX)
				{
					if (sb->map[pickY][pickX]->ships.size() > 0)
					{
						if (sb->miniWindowCreated)
						{
							hideMiniWindowShipStats();
							hideBars();
						}
						buildMiniWindowShipStats(sb->map[pickY][pickX]->screenX + 25, sb->map[pickY][pickX]->screenY, sb->map[pickY][pickX]->ships[0]);
						sb->miniWindowCreated = true;
						sb->showPath = false;
						if (sb->miniWindowEmptyCreated)
						{
							sb->miniWindowEmptyCreated = false;
							// hideWindow
							hideMiniWindowHex();
						}

					}
					else
					{
						sb->showPath = false;
						if (sb->miniWindowCreated)
						{
							sb->miniWindowCreated = false;
							hideMiniWindowShipStats();
						}
						if (!sb->miniWindowEmptyCreated)
						{
							sb->miniWindowEmptyCreated = true;
							// showWindow
							

							if (sb->selected)
							{
								sb->currentPath = spaceBattle::getPath(sb->SelectI, sb->SelectJ, pickY, pickX);
								float mobility = sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId]->mobility.total;
								float cost = 40 / (mobility / 100 + 1);
								cost *= sb->currentPath.size();
								buildMiniWindowHex(L"Empty Hex", true, sb->currentPath.size(), cost, L"No special effects", sb->map[pickY][pickX]->screenX + 25, sb->map[pickY][pickX]->screenY);
								sb->showPath = true;
							}
							else
								buildMiniWindowHex(L"Empty Hex", false, 0, 0, L"No special effects", sb->map[pickY][pickX]->screenX + 25, sb->map[pickY][pickX]->screenY);

						}
						else
						{
							hideMiniWindowHex();
							
							if (sb->selected)
							{
								sb->currentPath = spaceBattle::getPath(sb->SelectI, sb->SelectJ, pickY, pickX);

								//spaceBattle::dist2(sb->map[sb->SelectI][sb->SelectJ]->gameX, sb->map[sb->SelectI][sb->SelectJ]->gameY, sb->map[pickY][pickX]->gameX, sb->map[pickY][pickX]->gameY);

								float mobility = sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId]->mobility.total;
								float cost = 40 / (mobility / 100 + 1);
								cost *= sb->currentPath.size();
								buildMiniWindowHex(L"Empty Hex", true, sb->currentPath.size(), cost, L"No special effects", sb->map[pickY][pickX]->screenX + 25, sb->map[pickY][pickX]->screenY);
								sb->showPath = true;
							}
							else
								buildMiniWindowHex(L"Empty Hex", false, 0, 0, L"No special effects", sb->map[pickY][pickX]->screenX + 25, sb->map[pickY][pickX]->screenY);
							

						}
					}
				}
		
			// ship weapon selection
			if (sb->selected)
			{
			//	sf::Keyboard
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && sb->weaponId != 1)
				{
					int wepId = 1;
					auto w = spaceBattle::getShipWeaponModule(sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId], wepId);
					if (w != NULL)
					{
						if (spaceBattle::canUseWeapon(sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId], w))
						{
							wprintf(L"Info: Weapon selected: %ws \n", w->name.c_str());
							sb->selectedWeaponModule = w;
							sb->weaponModuleSelected = true;
							sb->weaponId = wepId;
						}
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && sb->weaponId != 2)
				{
					int wepId = 2;
					auto w = spaceBattle::getShipWeaponModule(sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId], wepId);
					if (w != NULL)
					{
						if (spaceBattle::canUseWeapon(sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId], w))
						{
							wprintf(L"Info: Weapon selected: %ws \n", w->name.c_str());
							sb->selectedWeaponModule = w;
							sb->weaponModuleSelected = true;
							sb->weaponId = wepId;
						}
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && sb->weaponId != 3)
				{
					int wepId = 3;
					auto w = spaceBattle::getShipWeaponModule(sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId], wepId);
					if (w != NULL)
					{
						if (spaceBattle::canUseWeapon(sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId], w))
						{
							wprintf(L"Info: Weapon selected: %ws \n", w->name.c_str());
							sb->selectedWeaponModule = w;
							sb->weaponModuleSelected = true;
							sb->weaponId = wepId;
						}
					}
				}

				if (sb->weaponModuleSelected)
				{

					// Changing to targeting mode

					sb->turnStatus = spaceBattleState::targetingWeapon;

					sb->showPath = false;
									
					sb->actionCooldown = 3;

					if (sb->miniWindowCreated)
					{
						sb->miniWindowCreated = false;
						hideMiniWindowShipStats();
					}
					
					if (sb->miniWindowEmptyCreated)
					{
						sb->miniWindowEmptyCreated = false;
						hideMiniWindowShipStats();
					}

				}

			}

		}

		if (sb->turnStatus == spaceBattleState::targetingWeapon)
		{

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sb->leftMBPressed = true;
			}

			/* Selecting segment (Click) */
			if (pickX != -1)
			{
				// selecting ship action
				if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && sb->leftMBPressed)
				{
					if (sb->map[pickY][pickX]->ships.size() > 0 && sb->actionCooldown == 0)
					{
						// ATTTACK
						/*sb->selected = true;
						sb->SelectI = pickY;
						sb->SelectJ = pickX;
						sb->SelectedShipId = 0;*/

						if (debugMode)
							printf("Info: Using weapon against ship in: %i, %i \n", pickY, pickX);

						spaceBattleAnimationElement * q = new spaceBattleAnimationElement();
						sb->waitForAnimElement = q;
						sb->animElems.push_back(q);
						q->curPos = {
							(sb->map[sb->SelectI][sb->SelectJ]->screenX + x) * scale ,
							(sb->map[sb->SelectI][sb->SelectJ]->screenY + y) * scale };
						q->speedVector = {sb->map[pickY][pickX]->screenX - sb->map[sb->SelectI][sb->SelectJ]->screenX, sb->map[pickY][pickX]->screenY - sb->map[sb->SelectI][sb->SelectJ]->screenY, };
						
						q->finishPos = {
							(sb->map[pickY][pickX]->screenX + x) * scale ,
							(sb->map[pickY][pickX]->screenY + y) * scale };

						float md = sqrt(q->speedVector.x * q->speedVector.x + q->speedVector.y * q->speedVector.y);
						q->speedVector /= md;
						q->moveSpeed = 1500;
						q->destroyWhenTimeElapsed = false;
						q->destroyWhenFinishPointAchived = true;
						q->lockAtFinish = true;
						q->scale = 1;
						q->sprite = new sf::Sprite(gEnv->modelDB[L"spaceBattleProjectileBase"]->tex);
						q->sprite->setOrigin(sf::Vector2f(q->sprite->getTexture()->getSize()) / 2.f);
						
						float angle = std::acos((q->speedVector.x * 1) / (std::sqrt((double)q->speedVector.x*q->speedVector.x + q->speedVector.y*q->speedVector.y)));
						angle = angle * 180 / 3.1415f;
						

						float tx, ty;
						tx = 1 * cos(angle * 3.1315f / 180) - 0;
						ty = 1 * sin(angle * 3.1315f / 180) + 0;

						if (abs(q->speedVector.x - tx) > 0.01 || abs(q->speedVector.y - ty) > 0.01)
							angle = -angle;

						q->rotationAngle = angle;
						sb->turnStatus = spaceBattleState::waitForWeaponAnim;

						sb->srcI = sb->SelectI;
						sb->srcJ = sb->SelectJ;
						sb->srcK = sb->SelectedShipId;
						sb->dstI = pickY;
						sb->dstJ = pickX;
						sb->dstK = 0;
						 

						/*
						auto res = spaceBattle::weaponAttack(
							sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId],
							sb->selectedWeaponModule,
							sb->map[pickY][pickX]->ships[0],
							std::sqrt(spaceBattle::dist2(sb->map[sb->SelectI][sb->SelectJ]->gameX, sb->map[sb->SelectI][sb->SelectJ]->gameY, sb->map[pickY][pickX]->gameX, sb->map[pickY][pickX]->gameY)),
							rand() % 65535
							);

						displayShipInfo();

						printf("Info: Total hits: %i/%i (%i critical), Total shield damage: %f, Total hull damage: %f \n", res.hits, res.total, res.crits, res.shieldDamage, res.hullDamage);

						if (!spaceBattle::canUseWeapon(sb->map[sb->SelectI][sb->SelectJ]->ships[sb->SelectedShipId], sb->selectedWeaponModule))
						{
							sb->weaponModuleSelected = false;
							sb->weaponId = -1;
							sb->turnStatus = spaceBattleState::primary;
							printf("Info: Weapon no longer selected - cant use it\n");
						}
						createActiveModulesButtons();
						showBars();*/
					}
				}
			}

			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sb->leftMBPressed = false;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sb->rightMBPressed = true;
			}

			
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && sb->rightMBPressed)
			{
				
				sb->weaponModuleSelected = false;
				sb->weaponId = 0;

				sb->actionCooldown = 5;

				sb->turnStatus = spaceBattleState::primary;

			}

			if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sb->rightMBPressed = false;
			}

			drawSpaceBattle(deltaTime);


		}

		if (sb->turnStatus == spaceBattleState::endTurn)
		{
			
			if (sb->currentFactionIndex + 1 > sb->factionOrder.size() - 1)
			{
				sb->currentFactionIndex = -1;
			}
			
			int id = sb->factionOrder[++sb->currentFactionIndex];

			spaceBattle::startTurnUpdate(id);

			if (id == 1)
				sb->turnNumber++;

			printf("Next turn: %i for player %i\n", sb->turnNumber, id);

			sb->turnStatus = spaceBattleState::primary;

			if (getCurrentPickShip() != NULL)
			{
				showBars();
				createActiveModulesButtons();
			}

		}

		if (sb->turnStatus == spaceBattleState::waitForWeaponAnim)
		{
			if (sb->waitForAnimElement == NULL)
			{
				// qq
				printf("Hit!\n");

				//sb->srcI = sb->SelectI;
				//sb->srcJ = sb->SelectJ;
				//sb->srcK = sb->SelectedShipId;
				//sb->dstI = pickY;
				//sb->dstJ = pickX;
				//sb->dstK = 0;

				auto res = spaceBattle::weaponAttack(
					sb->map[sb->srcI][sb->srcJ]->ships[sb->SelectedShipId],
					sb->selectedWeaponModule,
					sb->map[sb->dstI][sb->dstJ]->ships[0],
					std::sqrt(spaceBattle::dist2(sb->map[sb->srcI][sb->srcJ]->gameX, sb->map[sb->srcI][sb->srcJ]->gameY, sb->map[sb->dstI][sb->dstJ]->gameX, sb->map[sb->dstI][sb->dstJ]->gameY)),
					rand() % 65535
				);

				displayShipInfo();

				printf("Info: Total hits: %i/%i (%i critical), Total shield damage: %f, Total hull damage: %f \n", res.hits, res.total, res.crits, res.shieldDamage, res.hullDamage);

				if (!spaceBattle::canUseWeapon(sb->map[sb->srcI][sb->srcJ]->ships[sb->SelectedShipId], sb->selectedWeaponModule))
				{
					sb->weaponModuleSelected = false;
					sb->weaponId = -1;
					sb->turnStatus = spaceBattleState::primary;
					printf("Info: Weapon no longer selected - cant use it\n");
				}
				else
					sb->turnStatus = spaceBattleState::targetingWeapon;

				createActiveModulesButtons();
				showBars();

				// blast animation

				for (int i(0); i < 50; i++)
				{
					spaceBattleAnimationElement * q = new spaceBattleAnimationElement();
					sb->animElems.push_back(q);
					q->curPos = {
						(sb->map[sb->dstI][sb->dstJ]->screenX + x) * scale ,
						(sb->map[sb->dstI][sb->dstJ]->screenY + y) * scale };

					int qx = rand() % 100 - 50;
					int qy = rand() % 100 - 50;
					int qs = rand() % 80 + 20;
					int qt = rand() % 20 + 80;
					
					q->speedVector = { 1 * (qx / 100.f), 1 * (qy / 100.f) };


					float md = sqrt(q->speedVector.x * q->speedVector.x + q->speedVector.y * q->speedVector.y);
					q->speedVector /= md;
					q->curPos = q->speedVector * 4.f + q->curPos;
					q->moveSpeed = 30 + qs;

					q->destroyWhenTimeElapsed = true;
					q->destroyWhenFinishPointAchived = false;
					q->timeRemaining = 5 * (qt / 100.f);
					q->lockAtFinish = false;
					q->scale = 4;
					q->scaleFactorByTime = -0.45 * (100.f / qt);
					q->sprite = new sf::Sprite(gEnv->modelDB[L"spaceBattleParticleBase"]->tex);
					q->sprite->setOrigin(sf::Vector2f(q->sprite->getTexture()->getSize()) / 2.f);

				}


				if (sb->map[sb->dstI][sb->dstJ]->ships[0]->hull.current <= 0)
				{
					if (gEnv->game.player.ship->hull.current <= 0)
					{
						// exit game

						return;
					}

					sb->map[sb->dstI][sb->dstJ]->ships.erase(sb->map[sb->dstI][sb->dstJ]->ships.begin() + 0);

					for (int i(0); i < 40; i++)
					{
						spaceBattleAnimationElement * q = new spaceBattleAnimationElement();
						sb->animElems.push_back(q);
						q->curPos = {
							(sb->map[sb->dstI][sb->dstJ]->screenX + x) * scale ,
							(sb->map[sb->dstI][sb->dstJ]->screenY + y) * scale };

						int qx = rand() % 100 - 50;
						int qy = rand() % 100 - 50;
						int qs = rand() % 20 + 10;
						int qt = rand() % 20 + 80;

						q->speedVector = { 1 * (qx / 100.f), 1 * (qy / 100.f) };


						float md = sqrt(q->speedVector.x * q->speedVector.x + q->speedVector.y * q->speedVector.y);
						q->speedVector /= md;
						q->curPos = q->speedVector * 4.f + q->curPos;
						q->moveSpeed = 30 + qs;

						q->destroyWhenTimeElapsed = true;
						q->destroyWhenFinishPointAchived = false;
						q->timeRemaining = 5 * (qt / 100.f);
						q->lockAtFinish = false;
						q->scale = 3;
						q->scaleFactorByTime = -0.45 * (100.f / qt);
						q->sprite = new sf::Sprite(gEnv->modelDB[L"spaceBattleParticleBaseRed"]->tex);
						q->sprite->setOrigin(sf::Vector2f(q->sprite->getTexture()->getSize()) / 2.f);

					}

					for (int i(0); i < 15; i++)
					{
						spaceBattleAnimationElement * q = new spaceBattleAnimationElement();
						sb->animElems.push_back(q);
						q->curPos = {
							(sb->map[sb->dstI][sb->dstJ]->screenX + x) * scale ,
							(sb->map[sb->dstI][sb->dstJ]->screenY + y) * scale };

						int qx = rand() % 100 - 50;
						int qy = rand() % 100 - 50;
						int qs = rand() % 20 + 10;
						int qt = rand() % 20 + 80;

						q->speedVector = { 1 * (qx / 100.f), 1 * (qy / 100.f) };


						float md = sqrt(q->speedVector.x * q->speedVector.x + q->speedVector.y * q->speedVector.y);
						q->speedVector /= md;
						q->curPos = q->speedVector * 4.f + q->curPos;
						q->moveSpeed = 10 + qs;

						q->destroyWhenTimeElapsed = true;
						q->destroyWhenFinishPointAchived = false;
						q->timeRemaining = 10 * (qt / 100.f);
						q->lockAtFinish = false;
						q->scale = 6;
						q->scaleFactorByTime = -0.45 * (100.f / qt);
						q->sprite = new sf::Sprite(gEnv->modelDB[L"spaceBattleParticleBaseRed"]->tex);
						q->sprite->setOrigin(sf::Vector2f(q->sprite->getTexture()->getSize()) / 2.f);

					}


				}

			}

			drawSpaceBattle(deltaTime);

		}


		sb->pickI = pickY;
		sb->pickJ = pickX;

		// draw gui
		gEnv->game.spaceBattle.GUI.draw();

		/* Camera and scaling (Player camera) */

		// camera movement
		sf::Vector2f qMove = sf::Vector2f(0, 0);
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
		float moveSpeed = 2.5f * scale;
		sb->cameraX += qMove.x * moveSpeed;
		sb->cameraY += qMove.y * moveSpeed;

		sb->scale -= (gEnv->game.player.mouseWheelDelta / 2);

		if (sb->scale < 1)
			sb->scale = 1;
		if (sb->scale > 6)
			sb->scale = 6;

		if (sb->EndTurnPressed)
		{
			sb->EndTurnPressed = false;
			sb->actionCooldown = 5;
			sb->turnStatus = spaceBattleState::endTurn;
		}
	}
}

void drawSpaceBattle(double deltaTime)
{

	auto sb = &gEnv->game.spaceBattle;

	// background
	gEnv->globalWindow.draw(*sb->backgroundImage);

	// segments
	for (int qy = 0; qy < sb->maxLines; qy++)
	{
		for (int qx = 0; qx < sb->maxLength; qx++)
		{
			if (sb->pickJ == qx && sb->pickI == qy)
			{
				sb->mapSegmentHover->setPosition(sb->map[qy][qx]->screenX, sb->map[qy][qx]->screenY);
				gEnv->globalWindow.draw(*sb->mapSegmentHover);
			}
			else
			{
				auto c = sb->map[qy][qx]->color;
				switch (c)
				{
				case segmentColor::base:
					sb->mapSegment->setPosition(sb->map[qy][qx]->screenX, sb->map[qy][qx]->screenY);
					gEnv->globalWindow.draw(*sb->mapSegment);
					break;
				case segmentColor::player:
					sb->mapSegmentPlayer->setPosition(sb->map[qy][qx]->screenX, sb->map[qy][qx]->screenY);
					gEnv->globalWindow.draw(*sb->mapSegmentPlayer);
					break;
				case segmentColor::enemy:
					sb->mapSegmentEnemy->setPosition(sb->map[qy][qx]->screenX, sb->map[qy][qx]->screenY);
					gEnv->globalWindow.draw(*sb->mapSegmentEnemy);
					break;
				case segmentColor::neutral:
					sb->mapSegmentNeutral->setPosition(sb->map[qy][qx]->screenX, sb->map[qy][qx]->screenY);
					gEnv->globalWindow.draw(*sb->mapSegmentNeutral);
					break;
				default: // actually error but we should draw something
					sb->mapSegment->setPosition(sb->map[qy][qx]->screenX, sb->map[qy][qx]->screenY);
					gEnv->globalWindow.draw(*sb->mapSegment);
					break;
				}


			}

			if (sb->map[qy][qx]->ships.size() == 1)
			{
				auto p = sb->map[qy][qx]->ships[0];
				p->model->setPosition(sb->map[qy][qx]->screenX, sb->map[qy][qx]->screenY);
				p->model->setScale(1.f / sb->scale, 1.f / sb->scale);
				gEnv->globalWindow.draw(*p->model);
			}

		}
	}



	int x = sb->cameraX - (gEnv->graphics.windowSizeX * sb->scale / 2);
	int y = sb->cameraY - (gEnv->graphics.windowSizeY * sb->scale / 2);
	x /= sb->scale;
	y /= sb->scale;
	for (int i(0); i < sb->animElems.size(); i++)
	{
		auto p = sb->animElems[i];
		p->update(deltaTime);

		sf::Vector2f nPos = p->curPos / sb->scale;

		p->sprite->setPosition(nPos.x - x, nPos.y - y);
		p->sprite->setScale(p->scale / sb->scale, p->scale / sb->scale);
		p->sprite->setRotation(p->rotationAngle);
		gEnv->globalWindow.draw(*p->sprite);

		if (p->destroy)
		{
			if (p == sb->waitForAnimElement)
			{
				sb->waitForAnimElement = NULL;
			}
			delete (p->sprite);
			delete (p);
			
			sb->animElems.erase(sb->animElems.begin() + i);
			i--;
		}

	
	}

	if (sb->showPath)
	{
		for (int i(0); i < sb->currentPath.size(); i++)
		{
			int x, y;
			x = sb->map[sb->currentPath[i].first][sb->currentPath[i].second]->screenX;
			y = sb->map[sb->currentPath[i].first][sb->currentPath[i].second]->screenY;
			sb->mapPathMarker->setPosition(x, y);
			gEnv->globalWindow.draw(*sb->mapPathMarker);
		}
	}

}

void spaceBattle::initBattle()
{

	initAllShips();

	auto sb = &gEnv->game.spaceBattle;

	sb->factionOrder.clear();
	sb->factionOrder.push_back(1); /// player

	sb->turnNumber = 0; // Next turn will be 1

	sb->currentFactionIndex = -1; // next will be 0 - sb->factionOrder[0] // first faction to move in battle



}

void spaceBattle::initAllShips()
{

	auto sb = &gEnv->game.spaceBattle;

	for (int i(0); i<sb->map.size(); i++)
		for (int j(0); j<sb->map[i].size(); j++)
			for (int k(0); k < sb->map[i][j]->ships.size(); k++)
			{
				initShip(sb->map[i][j]->ships[k]);
			}


}

void spaceBattle::initShip(Ship * s)
{

	updateShipValues(s);

	s->actionPoints.current = s->actionPoints.total;
	// some other field to reset
	// do not know what exctly
	// s->something.current = 0;
	s->actionPointsPenalty = 0;



	for (int i(0); i < s->modules.size(); i++)
	{
		if (s->modules[i] == NULL)
			continue;
		
		if (s->modules[i]->moduleType != moduleType::weapon)
			continue;

		WeaponModule * m = static_cast<WeaponModule*>(s->modules[i]);

		m->CalcStats();

		m->currentCooldown = 0;
		m->activationsRemainingPartial = int(m->activationsPartial.total);
		m->activationsRemainingFull = int(m->activationsLimit.total);
		m->weaponState = weaponModuleState::normal;
		
		if (m->chargeRequired)
			m->chargingRemaining = int(m->chargeRoundsCount.total);
		else
			m->chargingRemaining = 0;

	}


}

void spaceBattle::startTurnUpdate(int factionId)
{
	auto sb = &gEnv->game.spaceBattle;

	for (int i(0); i<sb->map.size(); i++)
		for (int j(0); j<sb->map[i].size(); j++)
			for (int k(0); k < sb->map[i][j]->ships.size(); k++)
			{
				if (sb->map[i][j]->ships[k]->factionId == factionId)
				{
					// update ship
					spaceBattle::updateShip(sb->map[i][j]->ships[k]);
				}
			}

}

void spaceBattle::updateShip(Ship * s)
{

	updateShipValues(s);

	s->actionPoints.current = s->actionPoints.total * (1 - s->actionPointsPenalty);
	s->actionPointsPenalty = 0;

	s->shield.current += s->shieldReg.total;
	s->hull.current += s->hullReg.total;

	s->shield.current = std::min(s->shield.current, s->shield.total);
	s->hull.current = std::min(s->hull.current, s->hull.total);

	for (int i(0); i < s->modules.size(); i++)
	{
		if (s->modules[i] == NULL)
			continue;

		if (s->modules[i]->moduleType != moduleType::weapon)
			continue;

		WeaponModule * m = static_cast<WeaponModule*>(s->modules[i]);

		m->CalcStats();

		if (m->weaponState == weaponModuleState::partialCooldown)
		{
			m->currentCooldown -= 1;
			if (m->currentCooldown == 0)
			{
				m->weaponState = weaponModuleState::normal;
				m->activationsRemainingPartial = int(m->activationsPartial.total);
			}
		}

		if (m->weaponState == weaponModuleState::fullCooldown)
		{
			m->currentCooldown -= 1;
			if (m->currentCooldown == 0)
			{
				m->weaponState = weaponModuleState::normal;
				m->activationsRemainingPartial = int(m->activationsPartial.total);
				m->activationsRemainingFull = int(m->activationsLimit.total);
			}
		}

		if (m->weaponState == weaponModuleState::charging)
		{
			if (m->chargingRemaining == 0)
			{
				m->weaponState = weaponModuleState::fullCharge; // equal to Ready to fire
			}
		}

	}
}

bool spaceBattle::canUseWeapon(Ship * s, WeaponModule * m)
{

	auto state = m->weaponState;

	if (state != weaponModuleState::normal)
	{
		return false;
	}

	if (s->actionPoints.current < m->activationCost.total)
	{
		return false;
	}

	return true;
}

std::vector<std::pair<int, int>> spaceBattle::getPath(int si, int sj, int fi, int fj)
{
	std::vector<std::pair<int, int>> res;
	auto sb = &gEnv->game.spaceBattle;
	
	int n, k;
	n = sb->maxLines;
	k = sb->maxLength;

	std::vector<std::vector<int>> m(n, std::vector<int>(k));

	std::queue<std::pair<int, int>> s;

	m[si][sj] = 1;
	s.push(std::make_pair(si, sj));
	
	std::pair<int, int> evenLines[6] =
	{
		{ 0,-1 },
		{ -1,-1 },
		{ -1,0 },
		{ 0,+1 },
		{ +1,0 },
		{ +1,-1 }
	};
	std::pair<int, int> oddLines[6] =
	{
		{ 0,-1 },
		{ -1,0 },
		{ -1,+1 },
		{ 0,+1 },
		{ +1,+1 },
		{ +1,0 }
	};

	while (!s.empty())
	{
		auto pick = s.front();
		s.pop();

		// select all 6 possible directions
		for (int i(0); i < 6; i++)
		{
			std::pair<int, int> move;
			if (pick.first % 2 == 0)
				move = evenLines[i];
			else
				move = oddLines[i];

			move.first += pick.first;
			move.second += pick.second;

			// out of map
			if (move.first >= n || move.first < 0 || move.second < 0 || move.second >= k)
				continue;
			
			// way blocked
			if (sb->map[move.first][move.second]->ships.size() > 0)
				continue;

			// result found
			if (move.first == fi && move.second == fj)
			{
				// return to start, save way

				res.push_back(move);

				while (move.first != si || move.second != sj)
				{

					int cost = 999999;
					int dist = 1000 * 1000;

					auto q = move;
					std::pair<int, int> best = { 0,0 };
					for (int j(0); j < 6; j++)
					{
						if (q.first % 2 == 0)
							move = evenLines[j];
						else
							move = oddLines[j];

						move.first += q.first;
						move.second += q.second;

						if (move.first >= n || move.first < 0 || move.second < 0 || move.second >= k)
							continue;

						if (m[move.first][move.second] <= cost && m[move.first][move.second] > 0)
						{
							if (m[move.first][move.second] < cost)
							{
								best = move;
								cost = m[move.first][move.second];
								dist = dist2(move.first, move.second, si, sj);
							}
							else
							{
								if (dist2(move.first, move.second, si, sj) < dist)
								{
									best = move;
									cost = m[move.first][move.second];
									dist = dist2(move.first, move.second, si, sj);
								}
							}
						}
					}

					res.push_back(best);

					move = best;

				}
				res.erase(res.begin() + (res.size() - 1));
				std::reverse(res.begin(), res.end());
				return res;

			}

			// already visited
			if (m[move.first][move.second] != 0)
				continue;

			m[move.first][move.second] = 1 + m[pick.first][pick.second];

			s.push(move);

		}

	}
	// path not found. Res is empty
	return res;
}

void spaceBattle::teleportShip(int si, int sj, int fi, int fj, int shipId)
{
	auto sb = &gEnv->game.spaceBattle;

	Ship * s = sb->map[si][sj]->ships[shipId];

	sb->map[si][sj]->ships.erase(sb->map[si][sj]->ships.begin() + shipId);

	sb->map[fi][fj]->ships.push_back(s);
}

int spaceBattle::dist2(int x1, int y1, int x2, int y2)
{
	return ((x1 - x2)*(x1 - x2)) + ((y1 - y2)*(y1 - y2));
}

WeaponModule * spaceBattle::getShipWeaponModule(Ship * s, int id)
{

	if (s == NULL)
		return nullptr;

	if (s->modules.size() - 1 < id)
		return nullptr;

	int cur = 0;

	for (int i(0); i < s->modules.size(); i++)
	{
		if (s->modules[i] == NULL)
			continue;

		auto p = s->modules[i];

		if (p->moduleType == moduleType::weapon)
			cur++;
		else
			continue;
			
		if (cur == id)
			return static_cast<WeaponModule*>(p);
	}



	return nullptr;
}
