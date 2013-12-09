#include "renderer.h"


#include "helper.h"
#include <common/defines.h>
#include <common/helper.h>	
#include <physics/engine.h>

#include <osgText/Font>
#include <osgText/Text>

#define FIRST_FRAME 10
static float PLANE_SPEED =  30.0;
#define HYPER_SPEED 2.0
static float TOTAL_TIME =  120.0;
FMOD_SYSTEM *systemSound;



Renderer::Renderer(vrj::Kernel * parKernel) 
: vrj::OsgAppCustom(parKernel)
, FB0State(gadget::Digital::OFF)
, FB1State(gadget::Digital::OFF)
, FB2State(gadget::Digital::OFF)
, frameCounter(0)
, timePassed(0.0)
, FIsAlive(false)
, FIsMaitre(false)
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
    vrj::OsgAppCustom::latePreFrame();
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
		/*
		FSpeed = PhysicsEngine::Instance().ComputeNewSpeed(FSpeed,osg::Matrix::inverse(FRoot->GetDynamicModels()->GetNode()->getMatrix()),rotationMatrix.getRotate(),parDelta);
		if(FSpeed.length ()>=30)
		{
			FSpeed/=FSpeed.length();
			FSpeed*=30;
		}
		*/
		FRoot->UpdateVR(rotationMatrix,FSpeed,PLANE_SPEED,parDelta);
		FRoot->SkyboxVR(osg::Matrix::rotate(FRoot->GetDynamicModels()->GetNode()->getMatrix().getRotate()));
		FMitrailleuse.Update(parDelta);
		osg::Matrix toWorld;
		toWorld=osg::Matrix::inverse(FRoot->GetDynamicModels()->GetNode()->getMatrix());
		toWorld.preMult(FAirPlane->GetNode()->getMatrix());
		Intersect inter = PhysicsEngine::Instance().IsLandCollision(toWorld.getTrans());
		if(inter.isValid)
		{
			
			FRoot->RemoveStaticModel(FAirPlane);
			
			osg::Matrix transf(FRoot->GetDynamicModels()->GetNode()->getMatrix());
			transf = osg::Matrix::inverse(transf);

			FEpave->GetNode()->setMatrix(transf);
			FEpave->Translate(osg::Vec3f(0.0,3.0,-10.0));
			
			//FEpave->Translate(-inter.position);
			FRoot->AddModel(FEpave);
			
			FIsAlive = false;
			FObjectif->setColor(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
			FMOD_System_PlaySound(systemSound, FMOD_CHANNEL_FREE, sonMort, 0, NULL);
		}
		FTimer-=parDelta;
		if(PhysicsEngine::Instance().GetDetruits()==PhysicsEngine::Instance().GetNbCibles())
		{
			FIsAlive = false;
			FObjectif->setColor(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
		}
		if(FTimer<=0)
		{
			FIsAlive = false;
			FObjectif->setColor(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
		}
		FTimeString= "Temps restant (sec): ";
		FTimeString+=ConvertIntToString(int(FTimer));
		FTimeString+= "\nScore :";
		FTimeString+=  ConvertIntToString(PhysicsEngine::Instance().GetDetruits());
		FTimeString+= "/";
		FTimeString+= ConvertIntToString(PhysicsEngine::Instance().GetNbCibles());
		FObjectif->setText(FTimeString);
	}
	else
	{
		FTimeString= "\nScore final:";
		FTimeString+=  ConvertIntToString(PhysicsEngine::Instance().GetDetruits());
		FTimeString+= "/";
		FTimeString+= ConvertIntToString(PhysicsEngine::Instance().GetNbCibles());
		FObjectif->setText(FTimeString);
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
	FMOD_RESULT res = FMOD_System_Create(&systemSound);
	res = FMOD_System_Init(systemSound, 5	, FMOD_INIT_NORMAL, NULL);
	if(res== FMOD_OK)
	{
		FIsMaitre=true;
	}

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
	FSpeed = osg::Vec3f(0.0,0.0,PLANE_SPEED);


	osg::Geode * mHudGeode = new osg::Geode();
	osg::MatrixTransform * mHudTransform = new osg::MatrixTransform();
	osg::StateSet * mHudStateSet = new osg::StateSet();

	FObjectif = new  osgText::Text;
	mHudGeode->addDrawable( FObjectif );

	mHudStateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
	mHudGeode->setStateSet(mHudStateSet);

	FObjectif->setColor(osg::Vec4(0.0f,0.0f,0.0f,0.8f));
	FObjectif->setLineSpacing(0.7);
	FObjectif->setCharacterSize(5.0);
	FObjectif->setPosition(osg::Vec3(0.f,15.0f,-30.0f));
	FObjectif->setAlignment(osgText::Text::CENTER_CENTER);
	FObjectif->setBackdropColor(osg::Vec4(1.0f,1.0f,1.0f,0.6f));
	FObjectif->setBackdropType(osgText::Text::OUTLINE);


	mHudTransform->addChild(mHudGeode);
	FRoot->GetRoot()->addChild(mHudTransform);
	FTimer =  TOTAL_TIME;
	FMitrailleuse.Init(FIsMaitre);
	if(FIsMaitre)
	{
		res = FMOD_System_CreateSound(systemSound, "data/son/theme.mp3", FMOD_CREATESAMPLE, 0, &sonTheme);
		ERRCHECK(res);
		FMOD_System_CreateSound(systemSound, "data/son/explosion.mp3", FMOD_CREATESAMPLE, 0, &sonMort);
		res = FMOD_System_CreateSound(systemSound, "data/son/controltower.mp3", FMOD_CREATESAMPLE, 0, &sonControlTower);
		ERRCHECK(res);
		res = FMOD_System_PlaySound(systemSound, FMOD_CHANNEL_FREE, sonTheme, 0, NULL);
		ERRCHECK(res);
		FMOD_System_PlaySound(systemSound, FMOD_CHANNEL_FREE, sonControlTower, 0, NULL);
	}
}


