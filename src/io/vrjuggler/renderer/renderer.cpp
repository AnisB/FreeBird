#include "renderer.h"

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

	//FRoot->AddLight();
	FAirPlane = new SceneObject("data/DRC/DRC.obj");
	FAirPlane->InitObject();
	FRoot->AddModel(FAirPlane);
}


