#pragma once

#include "ship.h"

struct AttackResult
{
	int hits;
	int misses;

	float shieldDamage;
	float hullDamage;

	bool isCritical;
	bool isLethal;
};


AttackResult weaponAttack(Ship * src, WeaponModule * m, Ship * target, float dist);