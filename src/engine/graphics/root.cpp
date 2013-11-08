#include "root.h"

#include <common/defines.h>

#include <osg/LightSource>
#include <osg/Fog>


osg::ref_ptr< osg::StateSet> setFogState()
{
	osg::ref_ptr<osg::Fog> fog = new osg::Fog();  //The fog object
	fog->setMode(osg::Fog::LINEAR);		  	//Fog type 			
	fog->setColor(osg::Vec4(0.8,0.8,0.8,0));	//Fog color	
	fog->setStart(600);				//Start position of the fog - distance from the camera to the fog
	fog->setEnd(7000); // maximum distance - where the fog terminates.
	osg::ref_ptr< osg::StateSet> fogState (new osg::StateSet);
	fogState->setAttributeAndModes(fog.get(),osg::StateAttribute::ON);
	fogState->setMode(GL_FOG,osg::StateAttribute::ON);
	
	return fogState;

}
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
	#ifndef VRJUGGLER
	light->setAmbient(osg::Vec4(0.4,0.4,0.4,1.0));
	light->setDiffuse(osg::Vec4(0.5,0.5,0.5,1.0));
	light->setPosition(osg::Vec4(-1.0,-1.0,-1.0,0.0));
	light->setSpecular(osg::Vec4(1,0.8,0.8,1));
	#else
	light->setAmbient(osg::Vec4(0.7,0.7,0.7,1.0));
	light->setDiffuse(osg::Vec4(0.5,0.5,0.5,1.0));
	light->setPosition(osg::Vec4(0.0,0.0,1.0,0.0));
	light->setSpecular(osg::Vec4(1,0.8,0.8,1));
	#endif
	lightsource->setLight(light);
	mLightGroup->addChild(lightsource);

	osg::StateSet * stateset = mLightGroup->getOrCreateStateSet();
	lightsource->setStateSetModes(*stateset, osg::StateAttribute::ON);

	FRoot->setStateSet(setFogState().get());
	PRINT_GREEN<<"[ROOT] Root is ok."<<END_PRINT_COLOR;
}


void Root::CreateSkybox(SceneNode* toFollow)
{
	FSkybox = new Skybox();
	FSkybox->createSkybox("data/skybox/sky4", toFollow, this);
}

void Root::CreateTerrain()
{
	FTerrain = new Terrain();
	FTerrain->createTerrain("data/terrain/test", this);
}

void Root::CreateTerrainVR()
{
	FTerrain = new Terrain();
	FTerrain->createTerrainVR("data/terrain/test", this);
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

void Root::UpdateTerrain(osg::Vec3f parPosition)
{
	FTerrain->Update(parPosition);
}

void Root::UpdateSkybox()
{
	FSkybox->Update();
}
