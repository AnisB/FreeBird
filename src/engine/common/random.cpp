#include "random.h"
#include <ctgmath>

static float SEED = 666;


float RandomDet()
{
	SEED*=(666*333);
	SEED = std::fmod(SEED,1000);
	return std::cos(SEED);
}