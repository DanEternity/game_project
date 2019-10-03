#pragma once

#include <string>
#include "baseObject.h"
#include "scriptDescriptor.h"
#include "enviroment.h"

namespace memoryUtil
{

	enum returnCodeStatus
	{

		ok					= 0, // successful
		error				= 1, // something goes wrong =(
		notFound			= 2, // such variable does not exist
		notAvailable		= 4, // cant replace variable or protected from read/write
		convertationFailed	= 8, // cant convert object
		invalidSource		= 16,
		invalidDestination	= 32,
		undefined			= -1000, 

	};

} // memoryProcs

#define RETURN_CODE memoryUtil::returnCodeStatus

//
// Note: Int, String, Float objects automatically destroyed if replaced
// Other objects will not be destroyed unless special command executed
//


RETURN_CODE getMemoryCellFromExternalTable(std::string tableID, std::string rowID, BaseObject ** dst);

RETURN_CODE putMemoryCellToExternalTable(std::string tableID, std::string rowID, BaseObject * src);

RETURN_CODE getMemoryCellFromLocalMemory(LocalMemory * mem ,std::string rowID, BaseObject ** dst);

RETURN_CODE putMemoryCellToLocalMemory(LocalMemory * mem, std::string rowID, BaseObject * src);

RETURN_CODE convertToString(BaseObject * src, std::string &dst);

RETURN_CODE getMemoryCellFromGameEnviroment(std::string variableName, BaseObject ** dst);

RETURN_CODE putMemoryCellToGameEnviroment(std::string veriableName, BaseObject * src);

RETURN_CODE getObjectName(BaseObject * src, std::string &dst);

RETURN_CODE replaceValue(BaseObject * src, BaseObject ** dst);

RETURN_CODE getMemoryCell(std::string queryString, BaseObject ** dst, LocalMemory * localMem = NULL);

RETURN_CODE putMemoryCell(std::string queryString, BaseObject * src, LocalMemory * localMem = NULL);

RETURN_CODE convertConstToObject(std::string src, BaseObject ** dst);

RETURN_CODE checkSourceMemoryStatus(BaseObject * src);

