#ifndef FX_EXPLOSION
#define FX_EXPLOSION

#include <graphics/scenenode.h>

#include <osgParticle/ExplosionEffect>
#include <osgParticle/ExplosionDebrisEffect>
#include <osgParticle/SmokeEffect>
#include <osgParticle/SmokeTrailEffect>
#include <osgParticle/FireEffect>

class FXExplosion
{
	public:
		FXExplosion();
		~FXExplosion();
		SceneNode * GetNode() {return FAttachedSceneNode;};

		void InitFX(const osg::Vec3f& parPosition);

	protected:
		osg::ref_ptr<osgParticle::ExplosionEffect> FExplosion;
		osg::ref_ptr<osgParticle::ExplosionDebrisEffect> FExplosionDebri;

		SceneNode * FAttachedSceneNode;
};

#endif //FX_EXPLOSION