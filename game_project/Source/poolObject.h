#pragma once


//
// This file contain PoolObject class
//
//

#include <map>
#include <string>
#include "baseObject.h"

struct PoolDataCell
{
	BaseObject ** a;
};

class PoolObject : public BaseObject
{
public:
	std::map<int, PoolDataCell*> data;
	int argCount;
	int totalWeight;
	int current;
	PoolObject() : BaseObject()
	{
		// saved to objectStorage
		this->memoryControl = memoryControl::fixed;
		this->objectType = objectType::pool;
		totalWeight = 0;
		argCount = 0;
	}
	~PoolObject()
	{
		// delete all free objects 
		for (auto it = this->data.begin(); it != this->data.end(); it++)
		{
			for (int i(0); i<argCount; i++)
				if (it->second->a[i]->memoryControl == memoryControl::free)
					delete(it->second->a[i]);
			delete[] it->second->a;
		}
	}

	PoolDataCell * GetRandomObject(int key)
	{
		key *= 131797;
		key = key % totalWeight;
		auto r = data.lower_bound(key);
		return r->second;
	}

	void AddObject(PoolDataCell * obj, int weight)
	{
		totalWeight += weight;
		data[totalWeight] = obj;
	}

};