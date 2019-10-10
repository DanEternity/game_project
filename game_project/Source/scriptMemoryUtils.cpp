#include "scriptMemoryUtils.h"

RETURN_CODE getMemoryCellFromExternalTable(std::string tableID, std::string rowID, BaseObject ** dst)
{

	if (dst == NULL)
		return RETURN_CODE(memoryUtil::error | memoryUtil::invalidDestination);

	auto itTable = gEnv->extTables.find(tableID);

	if (itTable == gEnv->extTables.end())
		return RETURN_CODE(memoryUtil::error | memoryUtil::notFound);

	auto itRow = itTable->second->p_memory.find(rowID);

	if (itRow == itTable->second->p_memory.end())
		return RETURN_CODE(memoryUtil::error | memoryUtil::notFound);

	(*dst) = itRow->second;

	return RETURN_CODE(memoryUtil::ok);
}

RETURN_CODE putMemoryCellToExternalTable(std::string tableID, std::string rowID, BaseObject * src)
{
	if (src == NULL)
		return RETURN_CODE(memoryUtil::error | memoryUtil::invalidSource);

	auto itTable = gEnv->extTables.find(tableID);

	if (itTable == gEnv->extTables.end())
		return RETURN_CODE(memoryUtil::error | memoryUtil::notFound);

	auto itRow = itTable->second->p_memory.find(rowID);

	if (itRow == itTable->second->p_memory.end())
	{
		itTable->second->p_memory[rowID] = new BaseObject();
		itRow = itTable->second->p_memory.find(rowID);
		//auto code = checkSourceMemoryStatus(src);
		//return RETURN_CODE(memoryUtil::ok | code);
	}

	auto code = replaceValue(src, &itRow->second);

	return RETURN_CODE(code);
}

RETURN_CODE getMemoryCellFromLocalMemory(LocalMemory * mem, std::string rowID, BaseObject ** dst)
{

	if (dst == NULL)
		return RETURN_CODE(memoryUtil::error | memoryUtil::invalidDestination);

	auto itRow = mem->find(rowID);
	
	if (itRow == mem->end())
		return RETURN_CODE(memoryUtil::error | memoryUtil::notFound);

	(*dst) = itRow->second;

	return RETURN_CODE(memoryUtil::ok);
}

RETURN_CODE putMemoryCellToLocalMemory(LocalMemory * mem, std::string rowID, BaseObject * src)
{

	if (src == NULL)
		return RETURN_CODE(memoryUtil::error | memoryUtil::invalidSource);

	auto itRow = mem->find(rowID);

	if (itRow == mem->end())
	{
		(*mem)[rowID] = new BaseObject();
		itRow = mem->find(rowID);
		//auto code = checkSourceMemoryStatus(src);
		//return RETURN_CODE(memoryUtil::ok | code);
	}

	auto code = replaceValue(src, &itRow->second);

	return RETURN_CODE(code);
}

RETURN_CODE convertToString(BaseObject * src, std::string & dst)
{

	switch (src->objectType)
	{
	case objectType::integer:
		dst = std::to_string(static_cast<IntObject*>(src)->value);
		break;
	case objectType::string:
		dst = static_cast<StringObject*>(src)->value;
		break;
	case objectType::real:
		dst = std::to_string(static_cast<FloatObject*>(src)->value);
		break;
	case objectType::boolean:
		dst = std::to_string(static_cast<BooleanObject*>(src)->value);
		break;
	default:
	{
		auto code = getObjectName(src, dst);
		return RETURN_CODE(code);
	}
		break;
	}

	return RETURN_CODE(memoryUtil::ok);
}

RETURN_CODE getMemoryCellFromGameEnviroment(std::string variableName, BaseObject ** dst)
{

	return RETURN_CODE(memoryUtil::error);
}

RETURN_CODE putMemoryCellToGameEnviroment(std::string veriableName, BaseObject * src)
{

	return RETURN_CODE(memoryUtil::error);
}

RETURN_CODE getObjectName(BaseObject * src, std::string & dst)
{
	dst = "NOT IMPLEMENTED";
	return RETURN_CODE(memoryUtil::ok);
}

RETURN_CODE replaceValue(BaseObject * src, BaseObject ** dst)
{
	try
	{
		if (((*dst)->memoryControl & memoryControl::readOnly) != 0)
		{

			if ((src->memoryControl & memoryControl::singleUse) != 0)
				delete src;

			return RETURN_CODE(memoryUtil::error | memoryUtil::notAvailable);
		}

		if (((*dst)->memoryControl & memoryControl::fixed) == 0)
			delete(*dst);

		if ((src->memoryControl & memoryControl::fixed) != 0)
			*dst = src;
		else
		{
			int code = copyObject(src, dst);

			if (code != memoryUtil::ok)
			{

				if ((src->memoryControl & memoryControl::singleUse) != 0)
					delete src;

				return RETURN_CODE(code);
			}
		}

		if (((src->memoryControl & memoryControl::singleUse) != 0) && ((src->memoryControl & memoryControl::fixed) == 0))
			delete src;

	}
	catch (const std::exception&)
	{
		return RETURN_CODE(memoryUtil::error);
	}
	return RETURN_CODE(memoryUtil::ok);
}

RETURN_CODE getMemoryCell(std::string queryString, BaseObject ** dst, LocalMemory * localMem)
{

	try
	{
		// deleting $
		queryString = queryString.substr(1, queryString.size() - 1);

		if (queryString[0] == '_')
		{
			// local memory
			if (localMem == NULL)
				return RETURN_CODE(memoryUtil::error | memoryUtil::notAvailable);

			auto code = getMemoryCellFromLocalMemory(localMem, queryString.substr(1, queryString.size() - 1), dst);

			return RETURN_CODE(code);

		}

		if (queryString.find_first_of("EXT:", 0) != std::string::npos)
		{
			// external table parse
			// 
			// Descriptor has following format:
			// 01234567890123456789 
			// EXT:XXXX:VALUE

			int pos = queryString.find_first_of(':', 4);

			std::string tableId = queryString.substr(4, pos - 4);

			std::string rowId = queryString.substr(pos+1, queryString.size() - pos - 1);

			return RETURN_CODE(getMemoryCellFromExternalTable(tableId, rowId, dst));
		}

		// check game enviroment
		return RETURN_CODE(getMemoryCellFromGameEnviroment(queryString, dst));
		
	}
	catch (const std::exception&)
	{
		// unknown error
	}

	return RETURN_CODE(memoryUtil::undefined);
}

RETURN_CODE putMemoryCell(std::string queryString, BaseObject * src, LocalMemory * localMem)
{
	try
	{
		// deleting $
		queryString = queryString.substr(1, queryString.size() - 1);

		if (queryString[0] == '_')
		{
			// local memory
			if (localMem == NULL)
				return RETURN_CODE(memoryUtil::error | memoryUtil::notAvailable);

			auto code = putMemoryCellToLocalMemory(localMem, queryString.substr(1, queryString.size() - 1), src);

			return RETURN_CODE(code);

		}

		if (queryString.find_first_of("EXT:", 0) != std::string::npos)
		{
			// external table
			// need parse

			// 01234567890123456789 
			// EXT:XXXX:VALUE

			int pos = queryString.find_first_of(':', 4);

			std::string tableId = queryString.substr(4, pos - 4);

			std::string rowId = queryString.substr(pos + 1, queryString.size() - pos - 1);

			return RETURN_CODE(putMemoryCellToExternalTable(tableId, rowId, src));
		}

		// check game enviroment
		return RETURN_CODE(putMemoryCellToGameEnviroment(queryString, src));

	}
	catch (const std::exception&)
	{
		// unknown error
	}

	return RETURN_CODE(memoryUtil::undefined);
}

RETURN_CODE convertConstToObject(std::string src, BaseObject ** dst)
{

	try
	{

		// try to convert to int
		char *endptr;
		int valInt = std::strtol(src.c_str(), &endptr, 10);
		if (*endptr == '\0')
		{
			// src is a number
			IntObject * ptr = new IntObject();
			ptr->value = valInt;
			ptr->memoryControl = memoryControl::singleUse;
			*dst = ptr;
			return RETURN_CODE(memoryUtil::ok);
		}

		// try to convert to float
		float valFloat = std::strtof(src.c_str(), &endptr);
		if (*endptr == '\0')
		{
			// src is a float number
			FloatObject * ptr = new FloatObject();
			ptr->value = valFloat;
			ptr->memoryControl = memoryControl::singleUse;
			*dst = ptr;
			return RETURN_CODE(memoryUtil::ok);
		}

		// convert to boolean
		if (src == "true" || src == "True" || src == "TRUE")
		{
			// is a boolean (true)
			BooleanObject * ptr = new BooleanObject();
			ptr->value = true;
			ptr->memoryControl = memoryControl::singleUse;
			*dst = ptr;
			return RETURN_CODE(memoryUtil::ok);
		}
		else
			if (src == "false" || src == "False" || src == "FALSE")
			{
				// is a boolean (false)
				BooleanObject * ptr = new BooleanObject();
				ptr->value = false;
				ptr->memoryControl = memoryControl::singleUse;
				*dst = ptr;
				return RETURN_CODE(memoryUtil::ok);
			}

		// convert to string
		StringObject * ptr = new StringObject();
		ptr->value = src;
		ptr->memoryControl = memoryControl::singleUse;
		*dst = ptr;
		return RETURN_CODE(memoryUtil::ok);

	}
	catch (const std::exception&)
	{
		// failed
	}

	return RETURN_CODE(memoryUtil::undefined);
}

RETURN_CODE checkSourceMemoryStatus(BaseObject * src)
{
	try
	{

		if ((src->memoryControl & memoryControl::singleUse) != 0)
			delete src;

	}
	catch (const std::exception&)
	{
		return RETURN_CODE(memoryUtil::error);
	}

	return RETURN_CODE(memoryUtil::ok);
}

RETURN_CODE copyObject(BaseObject * src, BaseObject ** dst)
{

	if (src == NULL)
		return RETURN_CODE(memoryUtil::error | memoryUtil::invalidSource);

	if (dst == NULL)
		return RETURN_CODE(memoryUtil::error | memoryUtil::invalidDestination);

	try
	{
		BaseObject * ptr = NULL;
		switch (src->objectType)
		{
		case objectType::integer:
			ptr = new IntObject();
			static_cast<IntObject*>(ptr)->value = static_cast<IntObject*>(src)->value;
			break;
		case objectType::string:
			ptr = new StringObject();
			static_cast<StringObject*>(ptr)->value = static_cast<StringObject*>(src)->value;
			break;
		case objectType::real:
			ptr = new FloatObject();
			static_cast<FloatObject*>(ptr)->value = static_cast<FloatObject*>(src)->value;
			break;
		case objectType::boolean:
			ptr = new BooleanObject();
			static_cast<BooleanObject*>(ptr)->value = static_cast<BooleanObject*>(src)->value;
			break;
		default:
			break;
		}
		if (ptr == NULL)
			return RETURN_CODE(memoryUtil::undefined);
		(*dst) = ptr;
		return RETURN_CODE(memoryUtil::ok);
	}
	catch (const std::exception&)
	{

	}

	return RETURN_CODE(memoryUtil::undefined);
}

