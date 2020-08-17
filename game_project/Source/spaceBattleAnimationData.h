#pragma once

#include <SFML\Graphics.hpp>


//namespace spaceBattleAnimations
//{
//	enum 
//}

class spaceBattleAnimationElement
{
public:

	sf::Sprite * sprite = NULL;

	sf::Vector2f curPos;

	sf::Vector2f speedVector;
	sf::Vector2f finishPos;

	float moveSpeed = 1.f;
	float speedFactorByTime;
	
	float scale;
	float scaleFactorByTime;

	float timeFromStart;
	float timeRemaining;

	bool destroyWhenFinishPointAchived;
	bool destroyWhenTimeElapsed;
	bool lockAtFinish;
	
	bool destroy;

	spaceBattleAnimationElement()
	{
		scale = 1;
		scaleFactorByTime = 0;
		timeFromStart = 0;
		timeRemaining = 0;
		destroyWhenFinishPointAchived = true;
		destroyWhenTimeElapsed = true;
		lockAtFinish = true;

		speedVector = { 1.f, 0.f };
		curPos = { 0.f, 0.f };
		finishPos = { 0.f, 0.f };
	}

	void update(double deltaTime)
	{
		sf::Vector2f move = speedVector * moveSpeed * float(deltaTime);
		
		float distToFinish = (finishPos.x - curPos.x)*(finishPos.x - curPos.x) + (finishPos.y - curPos.y)*(finishPos.y - curPos.y);

		if (moveSpeed * float(deltaTime) * moveSpeed * float(deltaTime) > distToFinish && lockAtFinish)
		{
			curPos = finishPos;
			if (destroyWhenFinishPointAchived)
				destroy = true;
		}
		else
		{
			curPos += move;
		}

		scale += scaleFactorByTime * deltaTime;
		if (scale < 0)
			scale = 0;

		moveSpeed += speedFactorByTime * deltaTime;
		if (moveSpeed < 0)
			moveSpeed = 0;

		timeFromStart += deltaTime;
		timeRemaining -= deltaTime;

		if (timeRemaining <= 0 && destroyWhenTimeElapsed)
			destroy = true;
	}

};

