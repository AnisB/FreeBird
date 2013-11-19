#ifndef BULLET_ENTITY
#define BULLET_ENTITY

#include <entities/projectile.h>


class Bullet : public Projectile
{
	public:
		Bullet(osg::Vec3f parInitialPosition,osg::Matrix parDirection, double parVelocity);
		~Bullet();
};

#endif //BULLET_ENTITY