#include "sceneobject.h"


#include <resources/resourcemanager.h>



SceneObject::SceneObject(const std::string& parModelName)
: FIsRoot(false)
, FIsValid(false)
{
	FModelName = parModelName;
}

SceneObject::SceneObject()
: FIsRoot(true)
, FIsValid(true)
{
	FModelName = "";
}

SceneObject::~SceneObject()
{

}

void SceneObject::InitObject()
{
	FModel = ResourceManager::Instance().LoadModel(FModelName);
	if(FModel != NULL)
	{
		FIsValid = true;

		FModelTrans = new osg::MatrixTransform();
		FModelTrans->addChild(FModel);
	}
}


void SceneObject::Translate(const osg::Vec3f& parVec)
{
	// Translation dans le repère local
	FModelTrans->preMult(osg::Matrix::translate(parVec));
}


void SceneObject::AddChild(SceneObject * parNode)
{
	parNode->SetParent(this);
	FModelTrans->addChild(parNode->GetNode());
	FSons.push_back(parNode);
}

void SceneObject::SetParent(SceneObject * parNode)
{
	FParentNode = parNode;
}

void SceneObject::Rotate(float parAngle, const osg::Vec3f& parAxe)
{

}


void SceneObject::Yaw(float parRadian, TransformationSpace::Type parTrans)
{

}
void SceneObject::Pitch(float parRadian, TransformationSpace::Type parTrans)
{

}
void SceneObject::Roll(float parRadian, TransformationSpace::Type parTrans)
{

}

osg::Vec3f SceneObject::GetPosition(TransformationSpace::Type parTrans)
{
	return GetTransformation(parTrans).getTrans();
}


osg::Matrix SceneObject::GetTransformation(TransformationSpace::Type parTrans)
{
	if(parTrans == TransformationSpace::TS_LOCAL)
	{
		return GetLocalTransformation();
	}
	else if(parTrans == TransformationSpace::TS_PARENT)
	{
		return GetParentRelativeTransformation();
	}
	else
	{
		return GetAbsoluteTransformation();
	}
}


osg::Matrix SceneObject::GetLocalTransformation()
{
	return FModelTrans->getMatrix();
}
osg::Matrix SceneObject::GetParentRelativeTransformation()
{
	return (FModelTrans->getMatrix() * FParentNode->GetLocalTransformation());
}
osg::Matrix SceneObject::GetAbsoluteTransformation()
{
	if(FIsRoot)
	{
		return osg::Matrix::identity();
	}
	return (FModelTrans->getMatrix() * FParentNode->GetAbsoluteTransformation());
}