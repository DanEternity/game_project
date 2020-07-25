#pragma once

#include "ship.h"

namespace spaceBattle
{

	struct AttackResult
	{
		int hits;
		int misses;

		float shieldDamage;
		float hullDamage;

		bool isCritical;
		bool isLethal;

		AttackResult()
		{
			hits = 0;
			misses = 0;
			shieldDamage = 0;
			hullDamage = 0;
			isCritical = false;
			isLethal = false;
		}

	};


	AttackResult weaponAttack(Ship * src, WeaponModule * m, Ship * target, float dist, int key);

}