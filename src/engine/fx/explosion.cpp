#include "explosion.h"



FXExplosion::FXExplosion()
{

}

FXExplosion::~FXExplosion()
{

}


void FXExplosion::InitFX()
{
		osg::Vec3 wind(0.0f,0.0f,0.0f); 
		FExplosion = new osgParticle::ExplosionEffect(osg::Vec3f(0.0,0.0,0.0), 1.0f, 10.0f);
		FExplosionDebri = new osgParticle::ExplosionDebrisEffect(osg::Vec3f(0.0,0.0,0.0), 1.0f, 1.0f);
		osgParticle::SmokeEffect* smoke = new osgParticle::SmokeEffect(osg::Vec3f(0.0,0.0,0.0), 1.0f, 1.0f);
		osgParticle::SmokeTrailEffect* smokeTrail = new osgParticle::SmokeTrailEffect(osg::Vec3f(0.0,0.0,0.0), 1.0f, 1.0f);
		osgParticle::FireEffect* fire = new osgParticle::FireEffect(osg::Vec3f(0.0,0.0,0.0), 1.0f,100.0f);

		smokeTrail->setEmitterDuration(100);
		smokeTrail->setParticleDuration(10);
		smokeTrail->setUseLocalParticleSystem(true);
		//FExplosion->setEmitterDuration(100);
		//FExplosion->setParticleDuration(10);
		//FExplosion->setWind(wind);
		//FExplosionDebri->setWind(wind);
		//smoke->setWind(wind);
		//smokeTrail->setWind(wind);
		//fire->setWind(wind);

		FAttachedSceneNode = new SceneNode();
		FAttachedSceneNode->InitObject();
		//FAttachedSceneNode->GetNode()->addChild(FExplosion);
		FAttachedSceneNode->GetNode()->addChild(smokeTrail);
		//FAttachedSceneNode->GetNode()->addChild(FExplosionDebri);
		//FAttachedSceneNode->GetNode()->addChild(smoke);
		//FAttachedSceneNode->GetNode()->addChild(fire);

}