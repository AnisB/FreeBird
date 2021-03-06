#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

// Include OSG
#include <osg/Image>

// include projet
#include <common/singleton.h>
#include <resources/resourcemanager.h>
#include <entities/house.h>

// Include autre
#include <vector>

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
	
	int GetDetruits() {return FDetruit;}
	int GetNbCibles() {return FHouses.size();}
	void AddHouse(House* parHouse);
	bool Degats(int parCible, float parVal);
	int IsHouseCollision(const osg::Vec3f& planePosition);
	void DestroyHouse(int parHouse);
	Intersect IsLandCollision(const osg::Vec3f& planePosition);
	Intersect IsTooFarCollision(const osg::Vec3f& parObjectPos, const osg::Vec3f& parPlane);
	osg::Vec3f ComputeNewSpeed(const osg::Vec3f& parCurrentPlaneSped,const osg::Matrix& parTransform,  const osg::Quat& , double parDelta);


protected:
	osg::Image * FTerrainHeight;
	std::vector<House*> FHouses;
	int FDetruit;
};

#endif
