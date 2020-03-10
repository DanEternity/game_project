#pragma once

struct Stat
{
	float baseValue; // base stating value
	float increment; // increment to base value
	float multiplier; // multiplier to (base + increment)
	float totalRaw; // total without negative 
	float decrement; // decrement to total
	float debuffMultiplier; // multiplier that from range 0..1 
	float total; // total (calculated) value
	float current; // current value
	float percentage; // current/total

	void clear()
	{
		// not clearable
		//baseValue = 0; 
		//current = 0;

		multiplier = 0;
		increment = 0;
		total = 0;
		decrement = 0;
		debuffMultiplier = 1; // THIS IS ONLY VALUE THAT IS NOT ZERO BY DEFAULT
		totalRaw = 0;


	}

	void calcTotal()
	{
		/*q.second->totalRaw = (q.second->baseValue + q.second->increment) * (1 + q.second->multiplier);
		q.second->total = (q.second->totalRaw - q.second->decrement) * (q.second->debuffMultiplier);*/

		totalRaw = (baseValue + increment) * (1 + multiplier);
		total = (totalRaw - decrement) * (debuffMultiplier);

	}

	Stat()
	{

		baseValue = 0;
		multiplier = 0;
		increment = 0;
		totalRaw = 0;
		decrement = 0;
		debuffMultiplier = 1; // THIS IS ONLY VALUE THAT IS NOT ZERO BY DEFAULT
		total = 0;
		current = 0;
		percentage = 0;

	}

};