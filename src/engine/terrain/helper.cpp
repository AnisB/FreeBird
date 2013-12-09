
#include "helper.h"

#include "const.h"


osg::Vec2f ComputeRelativePosition(const osg::Vec3f& parPosition)
{
    osg::Vec2f realPos(fmod(parPosition.x()/TerrainConst::TerrainSize,1.0), fmod(parPosition.z()/TerrainConst::TerrainSize,1.0));
    return realPos;
}

osg::Vec2f ComputeRelativePosition2(const osg::Vec3f& parPosition)
{
	#ifndef VRJUGGLER
    osg::Vec2f realPos(fmod(parPosition.x()/TerrainConst::TerrainSize,1.0), fmod(parPosition.z()/TerrainConst::TerrainSize,1.0));
	#else
	osg::Vec2f realPos(fmod(parPosition.x()/TerrainConst::TerrainSize/2,1.0), fmod(parPosition.z()/TerrainConst::TerrainSize/2,1.0));
	#endif
    return realPos;
}
