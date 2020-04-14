#pragma once

namespace objectType {

	enum ObjectType
	{
		undefined = 0,
		modelDescriptor,
		scriptDescriptor,
		scriptCommand,
		integer,
		string,
		real,
		boolean,
		externalTable,
		mapMarker,
		mapDecoration,
		mapSector,
		effect,
		item,
		pool,
		skillObject
	};

} // namespace objectType

namespace memoryControl {

	enum MemoryControlType
	{
		free		= 0, // no special type

		fixed		= 1, // requires special function to delete
						 // replacing only overrides pointer

		readOnly	= 2, // only read possible

		writeOnly	= 4, // only write possible // does not work

		singleUse	= 8, // destroy after copying or processing

	};

}

// abstact class 
class BaseObject
{
public:
	objectType::ObjectType objectType;
	memoryControl::MemoryControlType memoryControl;
	int tableId;

	BaseObject()
	{
		objectType = objectType::undefined;
		memoryControl = memoryControl::free;
	}

	bool singleUse()
	{
		return ((memoryControl & memoryControl::singleUse) != 0);
	}

};