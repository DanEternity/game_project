#include "spaceBattleMechanics.h"

spaceBattle::AttackResult spaceBattle::weaponAttack(Ship * src, WeaponModule * m, Ship * target, float dist, int key)
{
	spaceBattle::AttackResult res = spaceBattle::AttackResult();

	float accuracy = m->accuracy.total;
	float damage = m->baseDamage.total;
	
	float distP = dist - m->optimalDistance.total;

	if (distP > 0)
	{
		accuracy -= distP * m->accuracyPenalty.total * accuracy;
		damage -= distP * m->damagePenalty.total * damage;
	}

	int hits = int(m->projectilesAmount.total);
	
	// apply target evasion
	accuracy -= target->evasion.total;
	// doesnt want to handle negative accuracy
	if (accuracy < 0) accuracy = 0;
	if (damage < 0) damage = 0;

	int key2 = key;
	for (int i(0); i < hits; i++)
	{
		
		float accQ = accuracy / 100;

		key2 = (key2 * 62791 + 1111117) % 65536;
		key2 = abs(key2);

		float keyQ = key2 / 65536;

		if (accQ > keyQ)
		{
			// successfull hit
			res.hits += 1;

			float hullResist = 0;
			float shieldResist = 0;

			if (m->damageType == 1)
			{
				// physical damage

				hullResist = target->hullResistPhysical.total;
				shieldResist = target->shieldResistPhysical.total;

			}

			if (m->damageType == 2)
			{
				// energy damage

				hullResist = target->hullResistEnergy.total;
				shieldResist = target->shieldResistEnergy.total;
			}

			hullResist -= hullResist * m->resistanceIgnoreHullPercent.total + m->resistanceIgnoreHullFlat.total;
			shieldResist -= shieldResist * m->resistanceIgnoreShieldPercent.total + m->resistanceIgnoreShieldFlat.total;

			if (hullResist < 0) hullResist = 0;
			if (shieldResist < 0) shieldResist = 0;

			hullResist = hullResist / (hullResist + 100);
			shieldResist = shieldResist / (shieldResist + 100);

			// critical strike calc
			/*key2 = (key2 * 62791 + 1111117) % 65536;
			key2 = abs(key2);
			float keyQ2 = key2 / 65536;*/

			float fDamage = damage;

			float targetShield = target->shield.current;
			float targetHull = target->hull.current;

			if (fDamage * (1 - shieldResist) > targetShield)
			{
				// damage exceeds shield

				res.shieldDamage += targetShield;
				fDamage -= targetShield / (1 - shieldResist);
				//targetShield -= fDamage * (1 - shieldResist);

				targetHull -= fDamage * (1 - hullResist);
				res.hullDamage += fDamage;
			}
			else
			{
				targetShield -= fDamage * (1 - shieldResist);
				res.shieldDamage += fDamage;
			}

			target->shield.current = targetShield;
			target->hull.current = targetHull;

		}
		else
		{
			res.misses += 1;
		}
	}

	return res;
}

