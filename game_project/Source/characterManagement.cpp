#include "characterManagement.h"

void updateCharacterStats()
{
	for (auto q : gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->characterStats)
	{
		if (q.second->total == 0)
			q.second->percentage = 0;
		else
			q.second->percentage = q.second->current / q.second->total;
	}

	clearCharacterStats();
	collectEquipment();
}

void clearCharacterStats()
{

	gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->health.clear(); 
	gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->armor.clear(); 
	gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->shield.clear(); 
	gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->ShieldReg.clear();
	gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->block.clear();
	gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->resist.clear();
	gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->ShieldReg.clear();
	gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->actionPoints.clear();
	gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->energy.clear();
	gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->energyReg.clear();
	gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->initiative.clear();

}

void collectEquipment()
{
	// check for hyperdrive
	for (Character* c : gEnv->game.player.crew.characters)
	{
		for (Equipment*m : c->equipment)
		{

			if (m == NULL)
				continue;

			applyCharEquipmentEffects(c, m);

		}
	}

	for (Character* c : gEnv->game.player.crew.characters)
	{
		for (auto q : c->characterStats)
		{
			q.second->calcTotal();
			q.second->current = q.second->percentage * q.second->total;

		}
	}
}

void applyCharEquipmentEffects(Character * c, Equipment * m)
{

	auto type = m->equipmentType;
	if (type == equipmentType::null)
	{
		for (EffectObject*e : m->effects)
		{
			auto eGroup = e->effectGroup;
			if (eGroup == effectGroups::statModifier)
			{
				StatModEffect * st = static_cast<StatModEffect *>(e);
				if (st->targetType != targetType::character)
				{
					continue;
				}

				applyCharacterStatEffect(c, st);

			}
		}
	}

}

void applyCharacterStatEffect(Character * c, StatModEffect * e)
{

	auto stName = e->statName;

	auto s = c->characterStats[stName];

	s->increment += e->p_add;
	s->multiplier += e->p_mul;
	s->decrement += e->p_sub;
	s->debuffMultiplier *= (1 - e->p_negMul);

}