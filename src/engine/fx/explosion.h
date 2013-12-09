#ifndef FX_EXPLOSION
#define FX_EXPLOSION

#include <graphics/scenenode.h>
#include "fxbase.h"
#include "explode.h"

class FXExplosion : public FXBase
{
	public:
		FXExplosion();
		~FXExplosion();
		SceneNode* GetNode() {return &FAttachedSceneNode;};

		void InitFX(const osg::Vec3f& parPosition, double parFloat);

	protected:
		//osg::ref_ptr<osgParticle::ExplosionEffect> FExplosion;
		osg::ref_ptr<osgParticle::Explode> FExplosion;
		SceneNode FAttachedSceneNode;
};

#endif //FX_EXPLOSION
