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

		void InitFX();

	protected:
		osgParticle::ExplosionEffect* FExplosion;
		osgParticle::ExplosionDebrisEffect* FExplosionDebri;

		SceneNode * FAttachedSceneNode;
		SceneNode * R;
};

#endif //FX_EXPLOSION