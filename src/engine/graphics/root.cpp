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
    mModelGroup = new osg::Group();
	mLightGroup = new osg::Group();
	FRoot->addChild( mLightGroup );
	mLightGroup->addChild( mModelGroup );
	FTerrain = new Terrain();
	FTerrain->createTerrain("data/terrain/test", this);

	
	osg::LightSource * lightsource = new osg::LightSource();
	osg::Light* light = new osg::Light();
	light->setAmbient(osg::Vec4(0.2,0.2,0.2,1.0));
	light->setDiffuse(osg::Vec4(1.0,1.0,1.0,1.0));
	light->setDirection(osg::Vec3(1.0,0.0,0.0));
	light->setConstantAttenuation(1.0);
	lightsource->setLight(light);

	mLightGroup->addChild(lightsource);

	osg::StateSet * stateset = mLightGroup->getOrCreateStateSet();
	lightsource->setStateSetModes(*stateset, osg::StateAttribute::ON);
	PRINT_GREEN<<"[ROOT] Root is ok."<<END_PRINT_COLOR;
}


void Root::AddModel(SceneNode * parNode)
{
	parNode->SetParent(this);
	mModelGroup->addChild(parNode->GetNode());
	FSons.push_back(parNode);
}

void Root::AddLight()
{
}