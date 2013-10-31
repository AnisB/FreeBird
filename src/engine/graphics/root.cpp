#include "root.h"

#include <common/defines.h>

#include <osg/LightSource>

Root::Root()
: SceneNode(NodeType::ROOT)
{
}

Root::~Root()
{

}

void Root::InitRoot()
{
        FRoot = new osg::Group();

	mLightGroup = new osg::Group();
	FRoot->addChild( mLightGroup );

        mNavModelGroup = new osg::MatrixTransform();
	mNoNavModelGroup = new osg::MatrixTransform();
	
	mLightGroup->addChild( mNavModelGroup );
	mLightGroup->addChild( mNoNavModelGroup );

	osg::LightSource * lightsource = new osg::LightSource();
	osg::Light* light = new osg::Light();
	light->setAmbient(osg::Vec4(0.2,0.2,0.2,1.0));
	light->setDiffuse(osg::Vec4(1.0,1.0,1.0,1.0));
	light->setDirection(osg::Vec3(0.0,-1.0,0.0));
	light->setConstantAttenuation(1.0);
	lightsource->setLight(light);
	mLightGroup->addChild(lightsource);

	osg::StateSet * stateset = mLightGroup->getOrCreateStateSet();
	lightsource->setStateSetModes(*stateset, osg::StateAttribute::ON);
	PRINT_GREEN<<"[ROOT] Root is ok."<<END_PRINT_COLOR;
}
void Root::CreateTerrain()
{
	FTerrain = new Terrain();
	FTerrain->createTerrain("data/terrain/test", this);
}


void Root::AddModel(SceneNode * parNode)
{
	parNode->SetParent(this);
	mNavModelGroup->addChild(parNode->GetNode());
	FSons.push_back(parNode);
}

void Root::AddStaticModel(SceneNode * parNode)
{
	parNode->SetParent(this);
	mNoNavModelGroup->addChild(parNode->GetNode());
	FSons.push_back(parNode);
}


void Root::AddNode(osg::Node * parNode)
{
	mNavModelGroup->addChild(parNode);

}

void Root::AddLight()
{

}
