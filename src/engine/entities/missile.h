#ifndef MISSILE_ENTITY
#define MISSILE_ENTITY

#include <entities/projectile.h>


class Missile : public Projectile
{
	public:
		Missile(osg::Vec3f parInitialPosition,osg::Matrix parDirection, double parVelocity);
		~Missile();
};

#endif //MISSILE_ENTITY