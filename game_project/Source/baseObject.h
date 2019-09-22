#pragma once

namespace objectType {

	enum ObjectType
	{
		modelDescriptor,

	};

} // namespace objectType

// abstact class 
class BaseObject
{
public:
	objectType::ObjectType objectType;
	int tableId;
};