#include "shipManagement.h"

void updateShipValues(Ship * p)
{

	// calculate module stats

	for (auto q : p->shipStats)
	{
		if (q.second->total == 0)
			q.second->percentage = 0;
		else
			q.second->percentage = q.second->current / q.second->total;
	}

	clearStats(p);
	collectModules(p);
	//calcModuleStats(p);


}

void clearStats(Ship * p)
{

	p->powerSupply.clear(); // ship energy for module operation
	p->highPowerSupply.clear(); // ship energy for module operation
	p->actionPoints.clear(); // ship power condensator capacity

					   // defence stats
	p->hull.clear();
	p->hullResist.clear();
	p->hullReg.clear();
	p->hullStructureStability.clear();
	p->shield.clear();
	p->shieldResist.clear();
	p->shieldReg.clear();
	p->shieldStructureStability.clear();

	p->evasion.clear();
	p->mobility.clear();
	p->stealth.clear();
	p->stealthTier.clear();
	p->sensorPower.clear();
	p->sensorTier.clear();
	p->missileDefense.clear();
	p->missileDefenseTier.clear();

	// hyperdrive 
	p->hyperDrivePower.clear();
	p->hyperDriveTier.clear();
	p->hyperDriveFuelEfficiency.clear();

	p->additionalWeaponAccuracy.clear();
	float totalDamageMultiplier = 0; // output damage multiplier

	float missileDefencePenalty = 0;  // penalty due to dense missile attack
	float actionPointsPenalty = 0; // penalty due to damage to Core

	p->fuel.clear(); // hyperdrive fuel

}

void calcModuleStats(Ship * p)
{

	for (Module*m : p->modules)
	{
		auto type = m->moduleType;
		if (type == moduleType::system && m->online)
		{
			for (EffectObject*e : m->effects)
			{
				auto eGroup = e->effectGroup;
				if (eGroup == effectGroups::statModifier)
				{
					StatModEffect * st = static_cast<StatModEffect *>(e);
					if (st->targetType != targetType::ship)
					{
						continue;
					}

					applyStatEffect(p, st);

				}
			}
		}
	}

	for (auto q : p->shipStats)
	{

		if (q.first == statNames::powerSupply || q.first == statNames::highPowerSupply)
			continue;

		q.second->calcTotal();

		if (q.first == statNames::fuel || q.first == statNames::powerSupply || q.first == statNames::highPowerSupply)
			continue;

		q.second->current = q.second->percentage * q.second->total;

	}

	p->fuel.current = (p->fuel.current < p->fuel.total) ? p->fuel.current : p->fuel.total;

}

void collectModules(Ship * p)
{

	// collect energy initial energy
	// from buffs, effects, something that can give it

	p->powerSupply.calcTotal();
	p->highPowerSupply.calcTotal();

	p->powerSupply.current = 0;
	p->highPowerSupply.current = 0;

	//for (Module*m : p->modules)
	//{
	//	auto type = m->moduleType;
	//	if (type == moduleType::system)
	//	{
	//		for (EffectObject*e : m->effects)
	//		{
	//			auto eGroup = e->effectGroup;
	//			if (eGroup == effectGroups::statModifier)
	//			{
	//				StatModEffect * st = static_cast<StatModEffect *>(e);
	//				if (st->targetType != targetType::ship)
	//				{
	//					continue;
	//				}

	//				if (st->statName == statNames::powerSupply || st->statName == statNames::highPowerSupply)
	//				{
	//					applyStatEffect(p, st);
	//				}

	//			}
	//		}
	//	}
	//}


	for (Module*m : p->modules)
	{

		if (m == NULL)
			continue;

		m->online = false; // disable all by default then boot one by one
	}

	//for (int i(0); i < p->modules.size(); i++)
	//{
	//	if (p->modules[i] == NULL) continue;
	//	p->modules[i]->online = false;
	//	
	//}

	// collect modules
	
	int minimalPriorityCollected = -1;



	while (1)
	{
		int minimalPriorityFound = 100; // Maximum priority is 99. No one module will have 100 priority.

		// we will collect modules that are at least more than minimal priority collected;
		
		// fimding minimal (best) priority 

		for (Module*m : p->modules)
		{

			if (m == NULL)
				continue;

			if (m->powerPriority > minimalPriorityCollected && m->powerPriority < minimalPriorityFound)
				minimalPriorityFound = m->powerPriority;
		}

		if (minimalPriorityFound == 100) // no new modules found
			break;

		// powering all modules from group
		
		for (Module*m : p->modules)
		{

			if (m == NULL)
				continue;

			if (m->powerPriority == minimalPriorityFound)
			{

				if (m->slot == moduleSlot::hyperdrive)
				{
					continue;
				}

				// powering module if possible
				if (checkRequirements(p,m))
				{
					
					m->online = true;
					p->powerSupply.current += m->powerSupply;
					p->highPowerSupply.current += m->highPowerSupply;

					applySysModuleEffects(p, m);

					p->powerSupply.calcTotal();
					p->highPowerSupply.calcTotal();

				}
			}
		}

		minimalPriorityCollected = minimalPriorityFound;

	}


	// check for hyperdrive 
	for (Module*m : p->modules)
	{

		if (m == NULL)
			continue;

		if (m->slot == moduleSlot::hyperdrive)
		{
			if (p->powerSupply.total >= m->powerSupply && p->highPowerSupply.total >= m->highPowerSupply)
			{
				
				m->online = true;
				applySysModuleEffects(p, m);
				break;
			}
			
		}
	}

	for (auto q : p->shipStats)
	{

		if (q.first == statNames::powerSupply || q.first == statNames::highPowerSupply)
			continue;

		q.second->calcTotal();

		if (q.first == statNames::fuel || q.first == statNames::powerSupply || q.first == statNames::highPowerSupply)
			continue;

		q.second->current = q.second->percentage * q.second->total;

	}

	p->fuel.current = (p->fuel.current < p->fuel.total) ? p->fuel.current : p->fuel.total;


}

void applySysModuleEffects(Ship * p, Module * m)
{

	auto type = m->moduleType;
	if (type == moduleType::system && m->online)
	{
		for (EffectObject*e : m->effects)
		{
			auto eGroup = e->effectGroup;
			if (eGroup == effectGroups::statModifier)
			{
				StatModEffect * st = static_cast<StatModEffect *>(e);
				if (st->targetType != targetType::ship)
				{
					continue;
				}

				applyStatEffect(p, st);

			}
		}
	}

}

void applyStatEffect(Ship * p, StatModEffect * e)
{

	auto stName = e->statName;

	auto s = p->shipStats[stName];

	s->increment += e->p_add;
	s->multiplier += e->p_mul;
	s->decrement += e->p_sub;
	s->debuffMultiplier *= (1 - e->p_negMul);

}

bool checkRequirements(Ship * p, Module * m)
{

	bool check = true;

	if (!(p->powerSupply.total - p->powerSupply.current >= m->powerSupply
		&& p->highPowerSupply.total - p->highPowerSupply.current >= m->highPowerSupply))
	{
		return false;
	}

	//for (int i(0); i<gEnv->game.gameLogic.moduleWorkRequirements_otherModuleByClass)
	auto t = gEnv->game.gameLogic.moduleWorkRequirements_otherModuleByClass.lower_bound(m->itemClass);

	while (t != gEnv->game.gameLogic.moduleWorkRequirements_otherModuleByClass.end() && t->first == m->itemClass)
	{
		auto req = t->second;
		bool f = false;
		for (auto mmm : p->modules)
			if (mmm != NULL)
			{
				if (mmm->itemClass == req)
				{
					f = true;
					break;
				}
			}
		if (!f)
			return false;
	}


	return check;
}
