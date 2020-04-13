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
		BaseObject();
		this->objectType = objectType::integer;
	}

	IntObject(int value)
	{
		BaseObject();
		this->objectType = objectType::integer;
		this->value = value;
	}
};

class StringObject : public BaseObject
{
public:
	std::wstring value;
	StringObject()
	{
		this->objectType = objectType::string;
	}

	StringObject(std::wstring arg)
	{
		this->objectType = objectType::string;
		value = arg;
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

	FloatObject(float x)
	{
		this->objectType = objectType::real;
		this->value = x;
	}
};

class BooleanObject : public BaseObject
{
public:
	bool value;
	BooleanObject()
	{
		this->objectType = objectType::boolean;
	}
};

class ExternalTable : public BaseObject
{
public:
	std::map<std::wstring, BaseObject*> p_memory;
	ExternalTable()
	{
		this->objectType = objectType::externalTable;
		this->memoryControl = memoryControl::fixed;
	}
};