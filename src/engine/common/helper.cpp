#include "helper.h"

#include <sstream>

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
