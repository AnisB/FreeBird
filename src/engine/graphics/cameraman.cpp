#include "cameraman.h"

#include <common/defines.h>
CameraMan::CameraMan()
: FIsValid(false)
{

}
CameraMan::~CameraMan()
{

}

void CameraMan::SetCamera(osg::Camera * parCamera)
{
	FCamera = parCamera;
}


void CameraMan::Update()
{
	PRINT_RED<<"Position 1"<<VEC3_TO_STREAM(FParentNode->GetPosition(TransformationSpace::TS_WORLD))<<END_PRINT_COLOR;
	PRINT_RED<<"Position 2"<<VEC3_TO_STREAM(GetPosition(TransformationSpace::TS_WORLD))<<END_PRINT_COLOR;
	FCamera->setViewMatrixAsLookAt(GetPosition(TransformationSpace::TS_WORLD),FParentNode->GetPosition(TransformationSpace::TS_WORLD),osg::Vec3f(0,1,0));
}



void CameraMan::Translate(const osg::Vec3f& parVec)
{
	SceneNode::Translate(parVec);
	Update();
}
void CameraMan::Rotate(float parAngle, const osg::Vec3f& parAxe)
{
	SceneNode::Rotate(parAngle, parAxe);
	Update();
}

void CameraMan::Yaw(float parRadian, TransformationSpace::Type parTrans)
{
	SceneNode::Yaw(parRadian, parTrans);
	Update();
}
void CameraMan::Pitch(float parRadian, TransformationSpace::Type parTrans)
{
	SceneNode::Pitch(parRadian, parTrans);
	Update();
}
void CameraMan::Roll(float parRadian, TransformationSpace::Type parTrans)
{
	SceneNode::Roll(parRadian, parTrans);
	Update();
}
