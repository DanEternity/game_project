#pragma once

#include <string>

// only for initial sector generation
class MapSectorPropertyTemplate
{
public:
	// initial parameter name. Used to input and display.
	std::wstring srcName;

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
	std::set<std::wstring> conflictProperties;

	// this property will not have any effect unless these properties connected
	std::set<std::wstring> requiredProperties;
	// Sector should have all properties from this list in order to activate this property

	// region specific condition 
	std::wstring regionCondition = L"";
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

	MapSectorPropertyTemplate()
	{
	}

	MapSectorPropertyTemplate(std::wstring name, int base, int distribution, int weight)
	{

		this->baseValue = base;
		this->srcName = name;
		this->valueDistribution = distribution;
		this->valueWeight = weight;

	}
};