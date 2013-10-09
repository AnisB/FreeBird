#include "renderer.h"


#include <common/defines.h>

Renderer::Renderer() 
: FViewer()
{
	FInputHandler = new InputEventHandler();
}

Renderer::~Renderer()
{
	//delete FRoot;
	//delete FAirplane;
	//delete FCameraMan;
}

void Renderer::UpdateScene(float parDelta)
{	
}


void Renderer::Run()
{
	if(!FViewer.isRealized())
	    FViewer.realize();
	InitCamera();
	while( !FViewer.done() )
	{
	   UpdateScene(0.1);
	   FViewer.frame();
	}
	QuittingRun();
}

void Renderer::QuittingRun()
{
	FViewer.removeEventHandler(FInputHandler);
}
void Renderer::KeyReleased(Key::Type parKey)
{
	switch (parKey)
	{
		case Key::FOWARD:
			FAirplane->Pitch(-0.1);
		break;
		
		case Key::BACKWARD:
			FAirplane->Pitch(0.1);
		break;
		
		case Key::LEFT:
			FAirplane->Roll(-0.1);
		break;

		case Key::RIGHT:
			FAirplane->Roll(0.1);
		break;
		//Unhandled
	};
}
void Renderer::KeyPressed(Key::Type parKey)
{
	switch (parKey)
	{
		case Key::FOWARD:
		break;
		
		case Key::BACKWARD:
		break;
		
		case Key::LEFT:
		break;

		case Key::RIGHT:
		break;
	};
}

void Renderer::MousePressed(Button::Type parButton)
{
	switch (parButton)
	{
		case Button::LEFT:
		break;
		
		case Button::RIGHT:
		break;
		
		case Button::MID:
		break;
		//Unhandled
	};
}

void Renderer::MouseReleased(Button::Type parButton)
{
	switch (parButton)
	{
		case Button::LEFT:
		break;
		
		case Button::RIGHT:
		break;
		
		case Button::MID:
		break;
		//Unhandled
	};
}

void Renderer::Init()
{
	SceneInit();
    OSGInit();	
}


void Renderer::InitCamera()
{
	std::vector<osg::Camera*> cameraList;
	FViewer.getCameras(cameraList, true);
	FCamera = cameraList[0];
	FCameraMan->SetCamera(FCamera);
}

void Renderer::OSGInit()
{
	FViewer.setSceneData( FRoot->GetRoot() );
	FViewer.addEventHandler(FInputHandler);
}

void Renderer::SceneInit()
{
	
	FRoot = new Root();
	FRoot->InitRoot();


	FAirplane= new SceneObject("data/DRC/DRC.obj");
	FAirplane->InitObject();
	FAirplane->Translate(osg::Vec3f(0,-3,-30));
    FAirplane->Roll(3.14);
    FAirplane->Yaw(3.14);
	FRoot->AddModel(FAirplane);

	FCameraMan = new CameraMan();
	FCameraMan->InitObject();
	//FCameraMan->Translate(osg::Vec3f(0,0,-30));
	FAirplane->AddChild(FCameraMan);
}


