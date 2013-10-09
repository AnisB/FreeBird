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

void CameraMan::Follow(SceneNode * parNode)
{
	FFollowedNode = parNode;
	FFollowedNode->AddChild(this);
}


void CameraMan::SetDistance(osg::Vec3f parDistance)
{
	Translate(parDistance);
}

void CameraMan::Update()
{
	const osg::Matrix& followedTrans  = FParentNode->GetTransformation(TransformationSpace::TS_WORLD);
	const osg::Vec3f& lookingPoint = followedTrans.getTrans();
	const osg::Vec3f& position = GetPosition(TransformationSpace::TS_WORLD);

	osg::Vec3f UpAxis(-followedTrans(1,0),-followedTrans(1,1),0);
	UpAxis.normalize();
	FCamera->setViewMatrixAsLookAt(position, lookingPoint, UpAxis);

}



void CameraMan::Translate(const osg::Vec3f& parVec)
{
	SceneNode::Translate(parVec);
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
