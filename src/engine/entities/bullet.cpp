#include "bullet.h"


static std::string BULLET_MODEL = "data/bullet/bullet.3ds";

Bullet::Bullet(osg::Vec3f parInitialPosition, osg::Matrix parDirection, double parVelocity)
: Projectile(parInitialPosition, parDirection, parVelocity, BULLET_MODEL)
{

}

Bullet::~Bullet()
{
	
}
