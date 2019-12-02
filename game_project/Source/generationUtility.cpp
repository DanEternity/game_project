#include "generationUtility.h"
#include "enviroment.h"


unsigned int getRand()
{	
	const int a = 1664525;
	const int c = 1013904223;
	const int m = 2147483647;
	return 	(gEnv->game.randTmp = (a * gEnv->game.randTmp + c) % m);
}

std::uint64_t getRand64()
{
	return std::uint64_t(getRand()*getRand());
}

uint64_t procRandom(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
	return uint64_t();
}
