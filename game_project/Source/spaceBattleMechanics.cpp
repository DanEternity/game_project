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
	
	res.total = hits;

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

		float keyQ = float(key2) / 65536;

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

			bool criticalS = false;
			bool criticalH = false;
			float critChanceS = m->criticalChanceShield.total;
			float critChanceH = m->criticalChanceHull.total;

			key2 = (key2 * 62791 + 1111117) % 65536;
			key2 = abs(key2);
			float keyQ2 = float(key2) / 65536;

			if (critChanceS > keyQ2)
				criticalS = true;

			key2 = (key2 * 62791 + 1111117) % 65536;
			key2 = abs(key2);
			keyQ2 = float(key2) / 65536;

			if (critChanceH > keyQ2)
				criticalH = true;

			float bDamage = damage;
			float fDamage = damage;

			if (criticalS)
				fDamage += std::max(0.f, fDamage * m->criticalDamageShield.total - target->shieldStructureStability.total);

			float targetShield = target->shield.current;
			float targetHull = target->hull.current;

			if (fDamage * (1 - shieldResist) > targetShield)
			{
				if ((targetShield > 0 && criticalS) || criticalH)
					res.crits++;

				// damage exceeds shield
				res.shieldDamage += targetShield;
				targetShield = 0;
				fDamage -= targetShield / (1 - shieldResist);

				if (criticalS)
				{
					fDamage = fDamage / std::max(1.f, 1 + m->criticalDamageShield.total - target->shieldStructureStability.total);
				}

				if (criticalH)
				{
					fDamage += fDamage * m->criticalDamageHull.total;
				}

				//targetShield -= fDamage * (1 - shieldResist);

				targetHull -= fDamage * (1 - hullResist);
				res.hullDamage += fDamage * (1 - hullResist);
			}
			else
			{

				fDamage = bDamage;
				if (criticalH)
				{
					res.crits++;
					fDamage += std::max(0.f, fDamage * m->criticalDamageHull.total - target->hullStructureStability.total);
				}

				targetShield -= fDamage * (1 - shieldResist);
				res.shieldDamage += fDamage * (1 - shieldResist);
			}

			target->shield.current = targetShield;
			target->hull.current = targetHull;

		}
		else
		{
			res.misses += 1;
		}
	}

	// update cooldowns
	m->activationsRemainingPartial--;
	m->activationsRemainingFull--;

	src->actionPoints.current -= m->activationCost.total;

	if (m->activationsRemainingPartial == 0 && m->activationsPartial.total != 0)
	{
		m->currentCooldown = m->partialCooldown.total;
		m->weaponState = weaponModuleState::partialCooldown;
	}

	if (m->activationsRemainingFull == 0 && m->activationsLimit.total != 0)
	{
		m->currentCooldown = m->fullCooldown.total;
		m->weaponState = weaponModuleState::fullCooldown;
	}

	return res;
}

Ship* getCurrentPickShip()
{
	if (gEnv->game.spaceBattle.SelectI == -1 || gEnv->game.spaceBattle.SelectJ == -1) return NULL;
	if (gEnv->game.spaceBattle.map[gEnv->game.spaceBattle.SelectI][gEnv->game.spaceBattle.SelectJ]->ships.size() == 0) return NULL;
	if (gEnv->game.spaceBattle.map[gEnv->game.spaceBattle.SelectI][gEnv->game.spaceBattle.SelectJ]->ships[gEnv->game.spaceBattle.SelectedShipId] == NULL) return NULL;
	return gEnv->game.spaceBattle.map[gEnv->game.spaceBattle.SelectI][gEnv->game.spaceBattle.SelectJ]->ships[gEnv->game.spaceBattle.SelectedShipId];
}