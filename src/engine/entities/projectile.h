#ifndef PROJECTILE_ENTITY
#define PROJECTILE_ENTITY

#include <graphics/sceneobject.h>
#include <common/defines.h>


class Projectile
{
	public:
		Projectile(osg::Vec3f parInitialPosition,osg::Matrix parDirection, double parVelocity, const std::string & parModelName);
		~Projectile();
		SceneNode * GetNode() {return FNode;};

		void Update(float parDelta);

	protected:
		SceneNode * FNode;
		SceneObject * FModel;
		osg::Vec3f FInitialPosition;
		osg::Matrix FOrientation;
		osg::Vec3f FCurrentPosition;
		double FVelocity;
};

#endif //PROJECTILE_ENTITY