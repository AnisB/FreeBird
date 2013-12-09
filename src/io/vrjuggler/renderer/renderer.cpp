#include "renderer.h"


#include "helper.h"
#include <common/defines.h>
#include <physics/engine.h>
#include <osg/Quat>


#define FIRST_FRAME 10
static float PLANE_SPEED =  20.0;
#define HYPER_SPEED 5.0

Renderer::Renderer(vrj::Kernel * parKernel) 
: vrj::OsgApp(parKernel)
, FB0State(gadget::Digital::OFF)
, FB1State(gadget::Digital::OFF)
, FB2State(gadget::Digital::OFF)
, frameCounter(0)
, timePassed(0.0)
, FIsAlive(false)
{
	
}


Renderer::~Renderer()
{
	
}

// Update methods
void Renderer::preFrame()
{
	// Input handeling
	HandleVRJInputs();

	// Computing passed time
	float delta = ComputeTime();
	timePassed+=delta;

	// Waiting first Ok Frame
	if(frameCounter<FIRST_FRAME)	
	{
		frameCounter++;
		return;
	}
	UpdateScene(delta);
}

void Renderer::latePreFrame()
{
    // Obtenir la transformation courante (gérée dans nav.h): room to world
    gmtl::Matrix44f curPos_Twr = mNavigator.getCurPos();
   
    // Obtenir la transformation inverse: world to room
    gmtl::Matrix44f world_transform_Trw;
    gmtl::invert( world_transform_Trw, curPos_Twr ); // inverse la seconde matrice dans la première

    // Finish updating the scene graph.
    vrj::OsgApp::latePreFrame();
}
void Renderer::intraFrame()
{

}
void Renderer::postFrame()
{

}

// Computing delta time
float Renderer::ComputeTime()
{
	vpr::Interval curTime = FWand->getTimeStamp();
	vpr::Interval diffTime (curTime - FLastPreFrameTime);

	if(FLastPreFrameTime.getBaseVal() >= curTime.getBaseVal())
	{
		diffTime.secf(0.0);
	}
	FLastPreFrameTime = curTime;
	float time =  diffTime.secf();
	if(time>1000)
	{
		time = 0.0;
	}
	return time;
}	

// Interpole une rotation 
osg::Matrixd Interpolate(const osg::Matrix& parWand, float parTime)
{
	osg::Matrixd ident;
	ident.makeIdentity ();
	osg::Quat actualRotation = ident.getRotate();
	osg::Quat finalRotation = parWand.getRotate();
	osg::Quat result;
	result.slerp(0.5*parTime,actualRotation,finalRotation);
	return osg::Matrix(result);
	
}
void Renderer::UpdateScene(float parDelta)
{
	
	const gmtl::Matrix44f wand_mat( FWand->getData(getDrawScaleFactor()));

	osg::Matrix wandRotation = GmtlToOsg_RotationOnly(wand_mat);
	wandRotation = osg::Matrix::inverse(wandRotation);

	osg::Matrix rotationMatrix = Interpolate(wandRotation, parDelta);
	if(FIsAlive)
	{
		FRoot->UpdateVR(rotationMatrix,PLANE_SPEED*parDelta);
		FMitrailleuse.Update(parDelta);
		osg::Matrix toWorld;
		toWorld=osg::Matrix::inverse(FRoot->GetDynamicModels()->GetNode()->getMatrix());
		//toWorld.postMult(FAirPlane->GetNode()->getMatrix());
		toWorld.postMult(osg::Matrix::translate(osg::Vec3f(0.0,4.0,-3.0)));
		//PRINT_ORANGE<<VEC3_TO_STREAM(osg::Matrix::inverse(FRoot->GetDynamicModels()->GetNode()->getMatrix()).getTrans())<<END_PRINT_COLOR;
		Intersect inter = PhysicsEngine::Instance().IsLandCollision(toWorld.getTrans());
		if(inter.isValid)
		{
			FRoot->RemoveStaticModel(FAirPlane);
			
			osg::Matrix transf(FRoot->GetDynamicModels()->GetNode()->getMatrix());
			transf = osg::Matrix::inverse(transf);

			FEpave->GetNode()->setMatrix(transf);
			FEpave->Translate(osg::Vec3f(0.0,5,-10.0));
			
			//FEpave->Translate(-inter.position);
			FRoot->AddModel(FEpave);
			
			FIsAlive = false;
		}
	}
}

// Input Methods
void Renderer::HandleVRJInputs()
{
	HandleButton(FButton0, FB0State, Button::BUTTON0);
	HandleButton(FButton1, FB1State, Button::BUTTON1);
	HandleButton(FButton2, FB2State, Button::BUTTON2);
}

void Renderer::HandleButton(gadget::DigitalInterface & parButton, gadget::Digital::State&  parState, Button::Type parButtonID)
{
	if (parButton->getData() != parState)
	{
		if (parState == gadget::Digital::ON)
		{
			parState = gadget::Digital::OFF;
			ButtonReleased(parButtonID);
		}
		else
		{	
			parState = gadget::Digital::ON;
			ButtonPressed(parButtonID);
		}
	}
}

void Renderer::ButtonReleased(Button::Type parButton)
{
	switch (parButton)
	{
		case Button::BUTTON0:
		{
			PLANE_SPEED/=HYPER_SPEED;
		}
		break;
		
		case Button::BUTTON1:
		{
			
		}
		break;
		
		case Button::BUTTON2:
			FMitrailleuse.SetActive(false);
		break;
		//Unhandled
	};
}

void Renderer::ButtonPressed(Button::Type parButton)
{
	switch (parButton)
	{
		case Button::BUTTON0:
		{
			PLANE_SPEED*=HYPER_SPEED;
		}
		break;
		
		case Button::BUTTON1:
		{
			FMitrailleuse.TirerMissile();
		}
		break;
		
		case Button::BUTTON2:
			FMitrailleuse.SetActive(true);
		break;
		//Unhandled
	};
}
// Init methods
void Renderer::initScene()
{
	VRInit();
	InitSceneContent();
}

osg::Group* Renderer::getScene()
{
	return FRoot->GetRoot();
}

void Renderer::VRInit()
{
	FWand.init(WAND_NAME_STR);
	FHead.init(HEAD_NAME_STR);
	FButton0.init(B0_NAME_STR);
	FButton1.init(B1_NAME_STR);
	FButton2.init(B2_NAME_STR);
}


void Renderer::InitSceneContent()
{

	FRoot = new Root();
	FRoot->InitRoot();

	FAirPlane = new SceneObject("data/DRC/DRC.obj");
	FEpave = new SceneObject("data/DRC/destroy.obj");
	FEpave->InitObject();
	//FAirPlane = new SceneObject("data/cockpit/cockpit.obj");
	FAirPlane->InitObject();
	FRoot->CreateSkybox(FAirPlane);
	
	FRoot->CreateTerrain();

	mNavigator.init();

	const gmtl::Matrix44f head_matrix( FHead->getData(getDrawScaleFactor()));
	mHeadInitPos = GmtlToOsg(head_matrix);
	FAirPlane->GetNode()->setMatrix(mHeadInitPos);
	FAirPlane->Pitch(MathTools::PI);
	FAirPlane->Translate(osg::Vec3f(-0.11,0.0,12));

	FEpave->GetNode()->setMatrix(mHeadInitPos);
	FRoot->AddStaticModel(FAirPlane);

	FMitrailleuse.SetRoot(FRoot);
	FMitrailleuse.SetAirplaneModel(FAirPlane);
	FMitrailleuse.SetAirplaneNode(FRoot->GetDynamicModels());
	PRINT_GREEN<<"Scene well initiated "<<END_PRINT_COLOR;
	FIsAlive = true;
}


