#ifndef HELPER_TERRAIN
#define HELPER_TERRAIN


#include <osg/Matrix>


// Terrain helper fuctions
// Pour la position des objet
osg::Vec2f ComputeRelativePosition(const osg::Vec3f& parPosition);

// Pour l'eau
osg::Vec2f ComputeRelativePosition2(const osg::Vec3f& parPosition);

#endif
