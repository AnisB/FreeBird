#ifndef FX_SPLASH
#define FX_SPLASH

#include <graphics/scenenode.h>
#include "fxbase.h"
#include <osgParticle/ExplosionDebrisEffect>

class FXSplash : public FXBase
{
	public:
		FXSplash();
		~FXSplash();
		SceneNode& GetNode() {return FAttachedSceneNode;}

		void InitFX(const osg::Vec3f& parPosition);

	protected:
		osg::ref_ptr<osgParticle::ExplosionDebrisEffect> FExplosionDebri;

		SceneNode FAttachedSceneNode;
};

#endif //FX_SPLASH