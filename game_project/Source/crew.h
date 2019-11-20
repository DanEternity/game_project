#pragma once

#include "baseObject.h"
#include "person.h"
#include <vector>

class Crew : BaseObject
{
public:
	std::vector<Person*> shipCrew;
};