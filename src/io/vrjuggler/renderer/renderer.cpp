#include "renderer.h"


#include "helper.h"
#include <common/defines.h>

#include <osg/Quat>


Renderer::Renderer(vrj::Kernel * parKernel) 
: vrj::OsgApp(parKernel)
, FB0State(gadget::Digital::TOGGLE_OFF)
, FB1State(gadget::Digital::TOGGLE_OFF)
, FB2State(gadget::Digital::TOGGLE_OFF)
{
	
}

Renderer::~Renderer()
{
	
}

// Update methods
void Renderer::preFrame()
{
	HandleVRJInputs();
	float delta = ComputeTime();
	UpdateScene(delta);
}
void Renderer::latePreFrame()
{
    // Obtenir la transformation courante (gérée dans nav.h): room to world
    gmtl::Matrix44f curPos_Twr = mNavigator.getCurPos();
   
    // Obtenir la transformation inverse: world to room
    gmtl::Matrix44f world_transform_Trw;
    gmtl::invert( world_transform_Trw, curPos_Twr ); // inverse la seconde matrice dans la première

    // Obtenir un pointeur sur le tableaux des 16 valeurs
    const float *mat_Trw = world_transform_Trw.getData();

    // Mettre à jour la MatrixTransform du graphe de scène avec le pointeur sur ces valeurs
    osg::Matrix osg_current_matrix_Trw( mat_Trw );
    FRoot->GetDynamicModels()->setMatrix( osg_current_matrix_Trw );

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
	return diffTime.secf();
}	

void Renderer::UpdateScene(float parDelta)
{
	
	const gmtl::Matrix44f wand_mat( FWand->getData(getDrawScaleFactor()));
	const gmtl::Matrix44f head_matrix( FHead->getData(getDrawScaleFactor()));

	osg::Matrix airplaneTrans = GmtlToOsg_RotationOnly(wand_mat);
	airplaneTrans = osg::Matrix::inverse(airplaneTrans);
	//airplaneTrans.preMult(osg::Matrix::rotate(MathTools::PI,osg::Vec3f(0.0,0.0,1.0)));
	//airplaneTrans.preMult(osg::Matrix::translate(osg::Vec3f(0.0,200.0,0.0)));
	//airplaneTrans.postMult(osg::Matrix::translate(osg::Vec3f(0.0,0.0,1.0)));
	osg::Quat rotation = airplaneTrans.getRotate();
	rotation.w() = rotation.w()*100;
	osg::Matrix rotationMatrix(rotation);
	osg::Matrix currentMatrix = FRoot->GetTerrain()->GetNode()->GetNode()->getMatrix();
	//airplaneTrans.postMult(osg::Matrix::translate(osg::Vec3f(0.0,0.0,1.0)));
	//airplaneTrans.postMult(osg::Matrix::translate(FPosition.getTrans()));
	//currentMatrix.postMult(osg::Matrix::translate(osg::Vec3f(0.0,0.0,1.0)));
	//airplaneTrans.preMult(osg::Matrix::translate(FPosition));
	currentMatrix.postMult(rotationMatrix);
	currentMatrix.postMult(osg::Matrix::translate(osg::Vec3f(0.0,0.0,2.0)));
	FRoot->GetTerrain()->GetNode()->GetNode()->setMatrix(currentMatrix);
	//FRoot->UpdateTerrain(FRoot->GetTerrain()->GetNode()->GetPosition());
	//FRoot->GetTerrain()->GetWater()->Pitch(MathTools::PI);
	osg::Matrix currentWaterMatrix = FRoot->GetTerrain()->GetWater()->GetNode()->getMatrix();
	currentWaterMatrix.postMult(rotationMatrix);
	currentWaterMatrix.postMult(osg::Matrix::translate(osg::Vec3f(0.0,0.0,3.0)));
	FRoot->GetTerrain()->GetWater()->GetNode()->setMatrix(currentWaterMatrix);



	osg::Matrix currentSkyboxMatrix = FRoot->GetSkybox()->GetNode()->getMatrix();
	currentSkyboxMatrix.postMult(rotationMatrix);
	FRoot->GetSkybox()->GetNode()->setMatrix(currentSkyboxMatrix);
	//FRoot->GetTerrain()->GetNode()->Pitch(-MathTools::PI/2);

}

// Input Methods
void Renderer::HandleVRJInputs()
{
	HandleButton(FButton0, FB0State, Button::BUTTON0);
	HandleButton(FButton1, FB1State, Button::BUTTON1);
	HandleButton(FButton2, FB2State, Button::BUTTON2);
}

void Renderer::HandleButton(gadget::DigitalInterface & parButton, gadget::Digital::State  parState, Button::Type parButtonID)
{
	if (parButton->getData() != parState)
	{
		if (parState == gadget::Digital::ON)
		{
			parState = gadget::Digital::TOGGLE_OFF;
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
		std::cout<<"Buttno0 pressed"<<std::endl;
		}
		break;
		
		case Button::BUTTON1:
		break;
		
		case Button::BUTTON2:
		break;
		//Unhandled
	};
}

void Renderer::ButtonPressed(Button::Type parButton)
{
	switch (parButton)
	{
		case Button::BUTTON0:
		break;
		
		case Button::BUTTON1:
		break;
		
		case Button::BUTTON2:
		break;
		//Unhandled
	};
}
// Init methods
void Renderer::initScene()
{
	VRInit();
	Init();
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


void Renderer::Init()
{
	FRoot = new Root();
	FRoot->InitRoot();

	FAirPlane = new SceneObject("data/DRC/DRC.obj");
	FAirPlane->InitObject();
	FRoot->CreateSkybox(FAirPlane);
	
	FRoot->CreateTerrain();

	mNavigator.init();

	const gmtl::Matrix44f head_matrix( FHead->getData(getDrawScaleFactor()));
        mHeadInitPos = GmtlToOsg(head_matrix);
        FAirPlane->GetNode()->setMatrix(mHeadInitPos);
        FAirPlane->Pitch(MathTools::PI);
        FAirPlane->Translate(osg::Vec3f(-0.11,1.1,-2.5));
	FRoot->GetTerrain()->GetNode()->Pitch(MathTools::PI);
	FRoot->GetTerrain()->GetNode()->Translate(osg::Vec3f(0.0,250,0.0));
	FRoot->GetTerrain()->GetWater()->Pitch(MathTools::PI);
	FRoot->GetTerrain()->GetWater()->Translate(osg::Vec3f(0.0,-50,0.0));
	FPosition = FRoot->GetTerrain()->GetNode()->GetNode()->getMatrix().getTrans();
	//FAirPlane->Scale(osg::Vec3f(0.1, 0.1, 0.1));
	FRoot->AddStaticModel(FAirPlane);
}


