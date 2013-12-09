#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include <osg/Image>

#include <common/singleton.h>
#include <resources/resourcemanager.h>


struct Intersect
{
	Intersect(bool parVal = false)
	{
		isValid = parVal;
	}
	bool isValid;
	osg::Vec3f position;
};

class PhysicsEngine: public Singleton<PhysicsEngine>
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	Intersect IsLandCollision(const osg::Vec3f& planePosition);
	Intersect IsTooFarCollision(const osg::Vec3f& parObjectPos, const osg::Vec3f& parPlane);


protected:
	osg::Image * FTerrainHeight;
};

#endif
