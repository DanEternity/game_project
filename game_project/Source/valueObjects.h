#pragma once

#include "baseObject.h"
#include <string>
#include <map>

// This file contain data types for scripts

class IntObject : public BaseObject
{
public:
	int value;
	IntObject()
	{
		this->objectType = objectType::integer;
	}
};

class StringObject : public BaseObject
{
public:
	std::string value;
	StringObject()
	{
		this->objectType = objectType::string;
	}
};

class FloatObject : public BaseObject
{
public: 
	double value;
	FloatObject()
	{
		this->objectType = objectType::real;
	}
};

class ExternalTable : public BaseObject
{
public:
	std::map<std::string, BaseObject*> p_memory;
};