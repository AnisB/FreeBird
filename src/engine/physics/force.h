#ifndef PHYSICS_FORCE
#define PHYSICS_FORCE



class Force
{
public:
	Force();
	~Force();


protected:
	osg::Vec3f FApplicationPoint;
	double FModule;
};

#endif