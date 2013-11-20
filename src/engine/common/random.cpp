#include "random.h"
#include <math.h>

static float SEED = 666;


float RandomDet()
{
	SEED*=(666*333);
	SEED = fmod(SEED,1000);
	return cos(SEED);
}
