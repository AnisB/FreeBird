#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include <osg/Image>
#include <resources/resourcemanager.h>

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	bool IsLandCollision(const osg::Vec3f& planePosition);
	bool IsTooFarCollision(const osg::Vec3f& parObjectPos, const osg::Vec3f& parPlane);


protected:
	osg::Image * FTerrainHeight;
};

#endif