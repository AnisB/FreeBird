

#include "house.h"

#include <iostream>

#ifdef VRJUGGLER
#define HOUSE_SIZE 15.0
#else
#define HOUSE_SIZE 50.0
#endif

House::House()
{
	mPV = 20; 
	FIsAlive = true;
}



House::~House()
{

}

void House::Init(const osg::Vec3f& parPosition)
{
	FNode = new SceneNode();
	FNode->InitObject();
	FModel = new SceneObject("data/models/house/house.3ds");
	FModel->InitObject();
	FDebris = new SceneObject("data/models/house/house.obj");
	FDebris->InitObject();
	FNode->AddChild(FModel);
	FNode->Translate(parPosition);
	FPosition=parPosition;
}

void House::Destroy()
{
	if(	FIsAlive)
	{
		FNode->RemoveChild(FModel);
		FNode->AddChild(FDebris);
		FIsAlive = false;
	}
}

bool House::IsIntersect(const osg::Vec3f& parPosition)
{
	bool isinX = ((parPosition.x()>(FPosition.x()-HOUSE_SIZE))&& (parPosition.x()<(FPosition.x()+HOUSE_SIZE)));
	bool isinY = ((parPosition.y()>(FPosition.y()-HOUSE_SIZE))&& (parPosition.y()<(FPosition.y()+HOUSE_SIZE)));
	bool isinZ = ((parPosition.z()>(FPosition.z()-HOUSE_SIZE))&& (parPosition.z()<(FPosition.z()+HOUSE_SIZE)));
	if(isinX && isinY && isinZ)
	{
		return true;
	}
	return false;
}

bool House::Degats(float parVal)
{
	mPV-=parVal;
	if(mPV<=0)
	{
		Destroy();
		return true;
	}
	return false;
}
