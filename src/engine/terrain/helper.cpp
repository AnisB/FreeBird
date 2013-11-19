
#include "helper.h"

#include "const.h"


osg::Vec2f ComputeRelativePosition(const osg::Vec3f& parPosition)
{
    osg::Vec2f realPos(fmod(parPosition.x()/TerrainConst::TerrainSize,1.0), fmod(parPosition.z()/TerrainConst::TerrainSize,1.0));
    return realPos;
}