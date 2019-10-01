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

	dst = &itRow->second;

	return RETURN_CODE(memoryUtil::ok);
}

RETURN_CODE putMemoryCellToExternalTable(std::string tableID, std::string rowID, BaseObject * scr)
{
	if (scr == NULL)
		return RETURN_CODE(memoryUtil::error | memoryUtil::invalidSource);

	auto itTable = gEnv->extTables.find(tableID);

	if (itTable == gEnv->extTables.end())
		return RETURN_CODE(memoryUtil::error | memoryUtil::notFound);

	auto itRow = itTable->second->p_memory.find(rowID);

	if (itRow == itTable->second->p_memory.end())
	{
		itTable->second->p_memory[rowID] = scr;
		return RETURN_CODE(memoryUtil::ok);
	}

	auto code = replaceValue(scr, &itRow->second);

	return RETURN_CODE(code);
}

RETURN_CODE getMemoryCellFromLocalMemory(LocalMemory * mem, std::string rowID, BaseObject ** dst)
{

	if (dst == NULL)
		return RETURN_CODE(memoryUtil::error | memoryUtil::invalidDestination);

	auto itRow = mem->find(rowID);
	
	if (itRow == mem->end())
		return RETURN_CODE(memoryUtil::error | memoryUtil::notFound);

	dst = &itRow->second;

	return RETURN_CODE(memoryUtil::ok);
}

RETURN_CODE putMemoryCellToLocalMemory(LocalMemory * mem, std::string rowID, BaseObject * scr)
{

	if (scr == NULL)
		return RETURN_CODE(memoryUtil::error | memoryUtil::invalidSource);

	auto itRow = mem->find(rowID);

	if (itRow == mem->end())
	{
		(*mem)[rowID] = scr;
		return RETURN_CODE(memoryUtil::ok);
	}

	auto code = replaceValue(scr, &itRow->second);

	return RETURN_CODE(code);
}

RETURN_CODE convertToString(BaseObject * scr, std::string & dst)
{

	switch (scr->objectType)
	{
	case objectType::integer:
		dst = std::to_string(static_cast<IntObject*>(scr)->value);
		break;
	case objectType::string:
		dst = static_cast<StringObject*>(scr)->value;
		break;
	case objectType::real:
		dst = std::to_string(static_cast<FloatObject*>(scr)->value);
		break;

	default:
	{
		auto code = getObjectName(scr, dst);
		return RETURN_CODE(code);
	}
		break;
	}

	return RETURN_CODE(memoryUtil::ok);
}

RETURN_CODE getMemoryCellFromGameEnviroment(std::string variableName, BaseObject ** dst)
{

	return RETURN_CODE(memoryUtil::ok);
}

RETURN_CODE putMemoryCellToGameEnviroment(std::string veriableName, BaseObject * scr)
{

	return RETURN_CODE(memoryUtil::ok);
}

RETURN_CODE getObjectName(BaseObject * scr, std::string & dst)
{
	dst = "NOT IMPLEMENTED";
	return RETURN_CODE(memoryUtil::ok);
}

RETURN_CODE replaceValue(BaseObject * scr, BaseObject ** dst)
{

	switch ((*dst)->objectType)
	{
	case objectType::integer:
	case objectType::string:
	case objectType::real:
		delete(*dst);
		*dst = scr;
		break;

	// any other objects
	case objectType::modelDescriptor: 
		*dst = scr;
		break;

	default:
		return RETURN_CODE(memoryUtil::error | memoryUtil::invalidDestination);
		break;
	}

	return RETURN_CODE(memoryUtil::ok);
}
