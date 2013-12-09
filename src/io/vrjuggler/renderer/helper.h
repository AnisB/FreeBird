#ifndef MATRIX_HELPER
#define MATRIX_HELPER

// Fichier de helper pour la conversion de matrices
// Include osg
#include <osg/Matrix>
// Include gmtl
#include <gmtl/Vec.h> 
#include <gmtl/Coord.h> 
#include <gmtl/Xforms.h> 
#include <gmtl/Math.h>

// Convertit une matrice gmtl4 en osg::Matrix4
osg::Matrix GmtlToOsg(const gmtl::Matrix44f& parMatrix);
//Récupère uniquement la translation d'une matrice gmtl
osg::Matrix GmtlToOsg_TranslationOnly(const gmtl::Matrix44f& parMatrix);
//Récupère uniquement la rotation d'une matrice gmtl
osg::Matrix GmtlToOsg_RotationOnly(const gmtl::Matrix44f& parMatrix);

#endif // MATRIX_HELPER
