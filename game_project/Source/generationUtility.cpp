#include "generationUtility.h"
#include "enviroment.h"


unsigned int getRand()
{	
	const int a = 1664525;
	const int c = 1013904223;
	const int m = 2147483647;
	return 	(gEnv->game.randTmp = (a * gEnv->game.randTmp + c) % m);
}
