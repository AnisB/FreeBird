#include "explosion.h"


#include <graphics/sceneobject.h>
FXExplosion::FXExplosion()
{

}

FXExplosion::~FXExplosion()
{
}


void FXExplosion::InitFX(const osg::Vec3f& parPosition,  double parFloat)
{
	osg::Vec3 wind(0.0f,0.0f,0.0f); 
	FExplosion = new osgParticle::ExplosionEffect(parPosition, 10.0f*parFloat, 10.0f);
	//FExplosion->setWind(wind);

	FAttachedSceneNode.InitObject();
	FAttachedSceneNode.GetNode()->addChild(FExplosion.get());
}
