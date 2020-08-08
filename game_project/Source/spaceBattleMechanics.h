#pragma once

#include "ship.h"
#include "enviroment.h"
#include <cmath>

namespace spaceBattle
{

	struct AttackResult
	{
		int hits;
		int misses;
		int crits;
		int total;

		float shieldDamage;
		float hullDamage;

		bool isCritical;
		bool isLethal;

		AttackResult()
		{
			hits = 0;
			misses = 0;
			crits = 0;
			total = 0;

			shieldDamage = 0;
			hullDamage = 0;
			isCritical = false;
			isLethal = false;
		}

	};


	AttackResult weaponAttack(Ship * src, WeaponModule * m, Ship * target, float dist, int key);

}

Ship* getCurrentPickShip();