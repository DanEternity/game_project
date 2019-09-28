#pragma once

namespace objectType {

	enum ObjectType
	{
		modelDescriptor,
		integer,
		string,
		real,
	};

} // namespace objectType

// abstact class 
class BaseObject
{
public:
	objectType::ObjectType objectType;
	int tableId;
};