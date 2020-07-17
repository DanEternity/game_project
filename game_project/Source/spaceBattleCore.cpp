#include "spaceBattleCore.h"

void updateSpaceBattle(double deltaTime)
{
	
	auto sb = &gEnv->game.spaceBattle;

	// draw battlefield
	if (sb->state == "init")
	{

		float sizeX, sizeY;
		sizeX = 442;
		sizeY = 512;

		sb->backgroundImage = new sf::Sprite(gEnv->modelDB[L"testBackgroundSpace"]->tex);

		sb->mapSegment = new sf::Sprite(gEnv->modelDB[L"spaceBattleMapSegment"]->tex);
		sb->mapSegment->setOrigin(sizeX / 2, sizeY / 2);
		sb->mapSegmentHover = new sf::Sprite(gEnv->modelDB[L"spaceBattleMapSegmentHover"]->tex);
		sb->mapSegmentHover->setOrigin(sizeX / 2, sizeY / 2);
	//	sb->mapSegment->setScale
		//sb->mapSegment->setPosition;
		
		sb->cameraX = 500;
		sb->cameraY = 500;

		for (int i(0); i < sb->maxLines; i++)
		{
			sb->map.push_back(std::vector<SpaceBattleSegment * >());
			for (int j(0); j < sb->maxLength; j++)
			{
				sb->map[i].push_back(new SpaceBattleSegment());
				if (i % 2 == 0)
					sb->map[i][j]->gameX = 0.5f + j;
				else
					sb->map[i][j]->gameX = 1.f + j;
				sb->map[i][j]->gameY = 0.557f + (i * 0.557f * 1.5f);
			}
		}
		sb->state = "idle";
	}

	if (sb->state == "idle")
	{

		auto mousePos = sf::Mouse::getPosition(gEnv->globalWindow);
		int pickX = -1, pickY = -1;
		float minDist = 999999999;


		float scale = sb->scale;
		float x, y;

		x = sb->cameraX  - (gEnv->graphics.windowSizeX / 2);
		y = sb->cameraY  - (gEnv->graphics.windowSizeY / 2);

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

		for (int qy = 0; qy < sb->maxLines; qy++)
		{
			for (int qx = 0; qx < sb->maxLength; qx++)
			{
				int mx, my;

				if (qy % 2 == 1)
				{
					mx = x + dx * qx + subLineOffset;
					my = y + dy * qy;
				}
					
				else
				{
					mx = x + dx * qx;
					my = y + dy * qy;
				}
				
				sb->map[qy][qx]->screenX = mx;
				sb->map[qy][qx]->screenY = my;

				float dist = ((mx - mousePos.x)*(mx - mousePos.x)) + ((my - mousePos.y)*(my - mousePos.y));
				if (dist < (100 * 100 / scale) && dist < minDist)
				{
					pickX = qx;
					pickY = qy;
					minDist = dist;
				}

			}
		}

		// background
		gEnv->globalWindow.draw(*sb->backgroundImage);

		for (int qy = 0; qy < sb->maxLines; qy++)
		{
			for (int qx = 0; qx < sb->maxLength; qx++)
			{
				if (pickX == qx && pickY == qy)
				{
					sb->mapSegmentHover->setPosition(sb->map[qy][qx]->screenX, sb->map[qy][qx]->screenY);
					gEnv->globalWindow.draw(*sb->mapSegmentHover);
				}
				else
				{
					sb->mapSegment->setPosition(sb->map[qy][qx]->screenX, sb->map[qy][qx]->screenY);
					gEnv->globalWindow.draw(*sb->mapSegment);
				}
			}
		}


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
		sb->cameraX -= qMove.x * moveSpeed;
		sb->cameraY -= qMove.y * moveSpeed;

		sb->scale -= (gEnv->game.player.mouseWheelDelta / 2);

		if (sb->scale < 1)
			sb->scale = 1;
		if (sb->scale > 6)
			sb->scale = 6;

	}


}
