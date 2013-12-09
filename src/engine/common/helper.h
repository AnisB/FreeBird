
#ifndef HELPER_COMMON
#define HELPER_COMMON

// Includes
#include <string>
#include <fmod.h>

// Conversion d'un flottant en string
std::string ConvertFloatToString(float parVal);
// Conversion d'un entier en string
std::string ConvertIntToString(int parVal);

// Vérification des erreurs fmodapi
void ERRCHECK(FMOD_RESULT result);

#endif
