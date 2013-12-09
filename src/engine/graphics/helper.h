#ifndef HELPER
#define HELPER

#include <osg/Matrix>

osg::Matrix getRotationOnly(const osg::Matrix& parMatrix);

osg::Matrix getTranslationOnly(const osg::Matrix& parMatrix);


osg::Vec3f fromTextureToWorld(const osg::Vec3f& parPos);

#endif // HELPER
