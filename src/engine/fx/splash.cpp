#include "splash.h"



FXSplash::FXSplash()
{

}

FXSplash::~FXSplash()
{
}


void FXSplash::InitFX(const osg::Vec3f& parPosition)
{
	osg::Vec3 wind(0.0f,-1.0f,0.0f); 
	FExplosionDebri = new osgParticle::ExplosionDebrisEffect(parPosition, 1.0f, 1.00f);

	FExplosionDebri->setWind(wind);

	FAttachedSceneNode.InitObject();
	FAttachedSceneNode.GetNode()->addChild(FExplosionDebri.get());
}
