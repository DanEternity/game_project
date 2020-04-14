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

	case getHash(L"Self"):
	case getHash(L"self"):
		return gEnv->scripts.currentScript;


	case getHash(L"money"):
	case getHash(L"Money"):
		return new IntObject(gEnv->game.player.money);
	default:
		break;
	}
	return nullptr;
}