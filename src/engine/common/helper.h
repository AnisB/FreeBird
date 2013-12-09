#ifndef HELPER_COMMON
#define HELPER_COMMON


#include<string>

#include<fmod.h>

std::string ConvertFloatToString(float parVal);

std::string ConvertIntToString(int parVal);

void ERRCHECK(FMOD_RESULT result);

#endif
