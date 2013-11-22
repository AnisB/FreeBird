#include "scenenode.h"

#include <common/defines.h>




SceneNode::SceneNode(NodeType::Type parTypeNode)
: FIsRoot(parTypeNode)
, FIsValid(false)
, FScaleVect(1,1,1)
{

}

SceneNode::~SceneNode()
{
}

void SceneNode::SetPosition(osg::Vec3f parPosition)
{
	FModelTrans->setMatrix(osg::Matrix::translate(parPosition));
	FModelTrans->preMult(osg::Matrix::scale(FScaleVect));
}


void SceneNode::Translate(const osg::Vec3f& parVec)
{
	// Translation dans le repère local
	FModelTrans->preMult(osg::Matrix::translate(parVec));
}

void SceneNode::InitObject()
{
	FModelTrans = new osg::MatrixTransform();
}

void SceneNode::AddChild(SceneNode * parNode)
{
	parNode->SetParent(this);
	FModelTrans->addChild(parNode->GetNode());
	FSons.push_back(parNode);
}

void SceneNode::SetParent(SceneNode * parNode)
{
	FParentNode = parNode;
}

void SceneNode::Rotate(float parAngle, const osg::Vec3f& parAxe)
{

}

void SceneNode::Rotate(const osg::Matrix& parRotationMatrix)
{
	FModelTrans->postMult(parRotationMatrix);
}

void SceneNode::Scale(osg::Vec3f parVectScale)
{
	FScaleVect=osg::Vec3f(parVectScale.x()*FScaleVect.x(),parVectScale.y()*FScaleVect.y(),parVectScale.z()*FScaleVect.z());
	FModelTrans->preMult(osg::Matrix::scale(parVectScale));
}


void SceneNode::Yaw(float parRadian, TransformationSpace::Type parTrans)
{
	if(parTrans == TransformationSpace::TS_LOCAL)
	{
		// Translation dans le repère local
		FModelTrans->preMult(osg::Matrix::rotate(parRadian,0,1,0));
	}
}
void SceneNode::Pitch(float parRadian, TransformationSpace::Type parTrans)
{
	if(parTrans == TransformationSpace::TS_LOCAL)
	{
		// Translation dans le repère local
		FModelTrans->preMult(osg::Matrix::rotate(parRadian,1,0,0));
	}
}
void SceneNode::Roll(float parRadian, TransformationSpace::Type parTrans)
{
	if(parTrans == TransformationSpace::TS_LOCAL)
	{
		// Translation dans le repère local
		FModelTrans->preMult(osg::Matrix::rotate(parRadian,0,0,1));
	}
}

osg::Vec3f SceneNode::GetPosition(TransformationSpace::Type parTrans)
{
	return GetTransformation(parTrans).getTrans();
}

osg::Vec3f SceneNode::GetPositionInv(TransformationSpace::Type parTrans)
{
	return osg::Matrix::inverse(GetTransformation(parTrans)).getTrans();
}

void SceneNode::SetTransformation(const osg::Matrix& parMatrix)
{	
	FModelTrans->setMatrix(parMatrix);
}
osg::Matrix SceneNode::GetTransformation(TransformationSpace::Type parTrans)
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


osg::Matrix SceneNode::GetLocalTransformation()
{
	return FModelTrans->getMatrix();
}
osg::Matrix SceneNode::GetParentRelativeTransformation()
{
	return (FModelTrans->getMatrix() * FParentNode->GetLocalTransformation());
}
osg::Matrix SceneNode::GetAbsoluteTransformation()
{
	if(FIsRoot)
	{
		return osg::Matrix::identity();
	}
	return (FModelTrans->getMatrix() * FParentNode->GetAbsoluteTransformation());
}
