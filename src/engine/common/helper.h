
#ifndef HELPER_COMMON
#define HELPER_COMMON

// Includes
#include <string>

#ifdef VRJUGGLER
#include <fmod.h>
#endif
// Conversion d'un flottant en string
std::string ConvertFloatToString(float parVal);
// Conversion d'un entier en string
std::string ConvertIntToString(int parVal);

// Vérification des erreurs fmodapi
#ifdef VRJUGGLER
void ERRCHECK(FMOD_RESULT result);
#endif
#endif
