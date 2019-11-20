#pragma once

#include "baseObject.h"
#include "item.h"
#include <vector>

class Character : public BaseObject
{
public:

	// common information

	std::wstring name;
	
	// links

	std::vector<Equipment*> equipment;

	// stats


};