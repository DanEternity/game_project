#pragma once

#include <string>

// only for initial sector generation
class MapSectorPropertyTemplate
{
public:
	// initial parameter name. Used to input and display.
	std::string srcName;

	// base level 
	int baseValue = 0;

	// distribution parameter 
	int valueDistribution = 0;
	// value in range [baseLevel-x .. baseLevel+x]

	// algorythm
	int distributionType = 0;
	// 0 for uniform distrubution

	// value probability weight
	int valueWeight;
	
	// value list of prohibited properties
	std::set<std::string> conflictProperties;

	// this property will not have any effect unless these properties connected
	std::set<std::string> requiredProperties;
	// Sector should have all properties from this list in order to activate this property

	// region specific condition 
	std::string regionCondition = "";
	// Does not have special format yet
	// Probably region name

	float getLocalProbability(float value)
	{
		if (distributionType == 0)
		{
			if (value >= baseValue - valueDistribution && value <= baseValue + valueDistribution)
			{
				return valueWeight;
			}
			// not in range
			return 0;
		}

		// incorrect // impossible
		return 0;
	}


};