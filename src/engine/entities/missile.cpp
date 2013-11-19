#include "missile.h"

static std::string MISSILE_MODEL = "data/model/missile/missile.obj";

Missile::Missile(osg::Vec3f parInitialPosition,osg::Matrix parDirection, double parVelocity)
: Projectile(parInitialPosition, parDirection, parVelocity, MISSILE_MODEL)
{

}

Missile::~Missile()
{
	
}
