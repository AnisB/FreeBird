#include "root.h"


Root::Root()
: SceneObject()
{
}

Root::~Root()
{

}

void Root::InitRoot()
{
    FRoot = new osg::Group();
    mModelGroup = new osg::Group();
	mLightGroup = new osg::Group();
	FRoot->addChild( mLightGroup );
	mLightGroup->addChild( mModelGroup );
}


void Root::AddModel(SceneObject * parNode)
{
	parNode->SetParent(this);
	mModelGroup->addChild(parNode->GetNode());
	FSons.push_back(parNode);
}

void Root::AddLight()
{
}