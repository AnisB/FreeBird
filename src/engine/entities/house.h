#ifndef HOUSE_FREEBIRD
#define HOUSE_FREEBIRD

#include <graphics/sceneobject.h>

class House
{ 
	public:
		House();
		void Init(const osg::Vec3f& parPosition);
		~House();
		bool IsIntersect(const osg::Vec3f& parPosition);
		bool Degats(float parVal);
		void Destroy();
		SceneNode * GetNode() {return FNode;}
		
	protected:
		bool FIsAlive;
		osg::Vec3f FPosition;
		SceneNode * FNode;
		SceneObject* FModel;
		SceneObject* FDebris;
		float mPV;
};
#endif
