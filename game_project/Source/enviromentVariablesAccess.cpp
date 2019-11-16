#include "enviromentVariablesAccess.h"

BaseObject * _getEnviromentVariable(uint32_t hash)
{
	switch (hash)
	{
		//
		// case getHash(L"value"):
		// return value;
	case getHash(L"NULL"):
		return nullptr;
	case getHash(L"gameTime"):
	case getHash(L"GameTime"):
		return new IntObject(gEnv->game.adventureData.gameTime);
	default:
		break;
	}
	return nullptr;
}