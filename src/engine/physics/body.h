#ifndef PHYSICS_BODY
#define PHYSICS_BODY



class Body
{
public:
	Body();
	~Body();


protected:
	// Dynamic properties
	osg::Vec3f FPosition;
	osg::Vec3f FVelocity;
	osg::Vec3f FAcceleration;

	// Static properties
	double FMass;


	std::list<Force> FForces;
};

#endif