#include "cameraman.h"

#include <common/defines.h>
#include <osgUtil/CullVisitor>
CameraMan::CameraMan()
: FIsValid(false)
{
	FFocalLength = 10;
}
CameraMan::~CameraMan()
{

}

void CameraMan::SetCamera(osg::Camera * parCamera)
{
	FCamera = parCamera;
	CameraInits();
	FCamera->setClearColor(osg::Vec4f(0.0,0.0,0.0,0.0));
	FCamera->setCullingMode( osg::CullSettings::NO_CULLING );
	glDisable(GL_CULL_FACE);

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

	osg::Vec3f UpAxis(-followedTrans(1,0),-followedTrans(1,1),-followedTrans(1,2));
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

void CameraMan::CameraInits()
{
	FCamera->getProjectionMatrixAsPerspective(FFovy, FAspectRatio,FNear,FFar);
	
	PRINT(FNear);
	PRINT(FFar);
	PRINT(FFocalLength);

	FFocalLength = 900.0/(tan(FFovy*MathTools::PI/MathTools::FULL_ANGLE)*2.0);
	FFovy = atan(900/ 2.0 / FFocalLength)*360.0/MathTools::PI; 
	FCamera->setProjectionMatrixAsPerspective(FFovy, FAspectRatio, FNear, FFar); 

}

void CameraMan::ChangeFocalLength(bool parVal)
{
	if(parVal)
	{
		FFocalLength*= 0.9;
		if(FFocalLength<=800)
		{
			FFocalLength=800;
		}
	}
	else
	{
		FFocalLength*= 1.1;

		if(FFocalLength>=1730)
		{
			FFocalLength=1730;
		}
	}
	PRINT(FFocalLength);
	FFovy = atan(900/ 2.0 / FFocalLength)*360.0/MathTools::PI; 
	FCamera->setProjectionMatrixAsPerspective(FFovy, FAspectRatio, FNear, FFar); 
}
