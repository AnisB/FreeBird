#include "helper.h"

#include <terrain/const.h>

osg::Matrix getRotationOnly(const osg::Matrix& parMatrix)
{
	osg::Quat rotation = parMatrix.getRotate();
	return osg::Matrix::rotate(rotation);
}

osg::Matrix getTranslationOnly(const osg::Matrix& parMatrix)
{
	osg::Vec3f translate = parMatrix.getTrans();
	return osg::Matrix::translate(translate);	
}


osg::Vec3f fromTextureToWorld(const osg::Vec3f& parPos)
{
	#ifndef VRJUGGLER
	return osg::Vec3f((parPos.z()-1024)*4.9,(1.0-(float)parPos.y()/255.0)*1080+125,-(parPos.x()-1024)*4.9);
	#else
	return osg::Vec3f(-(parPos.z()-1024)/2.0,-((1.0-(float)parPos.y()/255.0))*TerrainConst::WaterHeight,-(parPos.x()-1024)/2.0);
	#endif
}
