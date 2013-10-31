#ifndef MATRIX_HELPER
#define MATRIX_HELPER

#include <osg/Matrix>

#include <gmtl/Vec.h> 
#include <gmtl/Coord.h> 
#include <gmtl/Xforms.h> 
#include <gmtl/Math.h>


osg::Matrix GmtlToOsg(const gmtl::Matrix44f& parMatrix);

osg::Matrix GmtlToOsg_TranslationOnly(const gmtl::Matrix44f& parMatrix);

osg::Matrix GmtlToOsg_RotationOnly(const gmtl::Matrix44f& parMatrix);

#endif // MATRIX_HELPER
