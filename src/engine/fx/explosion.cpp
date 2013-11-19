#include "explosion.h"



FXExplosion::FXExplosion()
{

}

FXExplosion::~FXExplosion()
{
	delete FAttachedSceneNode;
}


void FXExplosion::InitFX(const osg::Vec3f& parPosition)
{
	osg::Vec3 wind(0.0f,0.0f,0.0f); 
	FExplosion = new osgParticle::ExplosionEffect(osg::Vec3f(0.0,0.0,0.0), 10.0f, 100.0f);
	FExplosionDebri = new osgParticle::ExplosionDebrisEffect(osg::Vec3f(0.0,0.0,0.0), 10.0f, 1.00f);

	FExplosion->setEmitterDuration(100);
	FExplosion->setParticleDuration(100);

	FAttachedSceneNode = new SceneNode();
	FAttachedSceneNode->InitObject();
	FAttachedSceneNode->GetNode()->addChild(FExplosion);
	FAttachedSceneNode->GetNode()->addChild(FExplosionDebri);
	FAttachedSceneNode->SetPosition(parPosition);
}