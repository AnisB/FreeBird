//Include header
#include "helper.h"

// Include auters
#include <sstream>
#include <common/defines.h>
#include <iostream>


std::string ConvertFloatToString(float parVal)
{
	std::stringstream sStream;
	sStream<<parVal;
	std::string result;
	sStream>>result;
	return result;
}


std::string ConvertIntToString(int parVal)
{
	std::stringstream sStream;
	sStream<<parVal;
	std::string result;
	sStream>>result;
	return result;
}
#ifdef VRJUGGLER
void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        PRINT_RED<<"FMOD error!"<< result<<" "<<END_PRINT_COLOR;
        return;
    }
}
#endif
