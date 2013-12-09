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

    mNavModelGroup = new SceneNode(NodeType::ROOT);
	mNavModelGroup->InitObject();
	mNoNavModelGroup = new SceneNode(NodeType::ROOT);
	mNoNavModelGroup->InitObject();

	mLightGroup->addChild( mNavModelGroup->GetNode() );
	mLightGroup->addChild( mNoNavModelGroup->GetNode() );
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
	#ifndef VRJUGGLER
	FSkybox = new Skybox();
	FSkybox->createSkybox("data/skybox/sky4", toFollow, this);
	#else
	FSkybox = new Skybox();
	FSkybox->createSkybox("data/skybox/sky4", toFollow, this);
	#endif
}

void Root::CreateTerrain()
{
	FTerrain = new Terrain();
	FTerrain->createTerrain("data/terrain/test", this);
}


void Root::RemoveStaticModel(SceneNode * parNode)
{
	PRINT_ORANGE<<mNoNavModelGroup->GetNode()->removeChild(parNode->GetNode())<<END_PRINT_COLOR;
	FSons.remove(parNode);
}

void Root::RemoveModel(SceneNode * parNode)
{
	PRINT_ORANGE<<mNavModelGroup->GetNode()->removeChild(parNode->GetNode())<<END_PRINT_COLOR;
	FSons.remove(parNode);
}
void Root::AddModel(SceneNode * parNode)
{
	parNode->SetParent(this);
	mNavModelGroup->AddChild(parNode);
	FSons.push_back(parNode);
}

void Root::AddStaticModel(SceneNode * parNode)
{
	parNode->SetParent(this);
	mNoNavModelGroup->AddChild(parNode);
	FSons.push_back(parNode);
}


void Root::AddNode(osg::Node * parNode)
{
	mNavModelGroup->GetNode()->addChild(parNode);

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
void Root::SkyboxVR(const osg::Matrix& parTransf)
{
	FSkybox->SetRotation(parTransf);
}
void Root::UpdateVR(osg::Matrixd parRotationMatrix, const osg::Vec3f& parDirectionfloat, float  parSpeed, float parTime)
{
    osg::Matrix currentMatrix = mNavModelGroup->GetNode()->getMatrix();
    currentMatrix.postMult(parRotationMatrix);
    currentMatrix.postMult(osg::Matrix::translate(osg::Vec3f(0.0,0.0,parSpeed*parTime)));
	//currentMatrix.postMult(osg::Matrix::translate(parDirection*parDisplacement));
    mNavModelGroup->GetNode()->setMatrix(currentMatrix);
	FTerrain->UpdateVR(parRotationMatrix, parSpeed*parTime);
	FTerrain->Animation(parTime);
}

