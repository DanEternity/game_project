#pragma once

#include "baseObject.h"
#include <string>
#include <map>

// This file contain data types for scripts

class IntObject : public BaseObject
{
public:
	int value;
};

class StringObject : public BaseObject
{
public:
	std::string value;
};

class FloatObject : public BaseObject
{
public: 
	double value;
};

class ExternalTable : public BaseObject
{
public:
	std::map<std::string, BaseObject*> p_memory;
};