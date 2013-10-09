#include "renderer.h"


#include <common/defines.h>

Renderer::Renderer() 
: FViewer()
{
	FInputHandler = new InputEventHandler();
}

Renderer::~Renderer()
{
	delete FRoot;
	delete FAirplane;
	delete FAirplane2;
	delete FBuilding;
	delete FCameraMan;
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
		break;
		
		case Key::BACKWARD:
		break;
		
		case Key::LEFT:
		break;

		case Key::RIGHT:
		break;
	};
}
void Renderer::KeyPressed(Key::Type parKey)
{
	//PRINT_ORANGE<<"[RENDERER]Key pressed recieved"<<END_PRINT_COLOR;
	switch (parKey)
	{
		case Key::FOWARD:
			FAirplane->Pitch(AirplaneRotation::CLOCKWISE,-0.1);
			FCameraMan->Update();
			
		break;
		
		case Key::BACKWARD:
			FAirplane->Pitch(AirplaneRotation::ANTICLOCKWISE,0.1);
			FCameraMan->Update();

		break;
		
		case Key::LEFT:
			FAirplane->Roll(AirplaneRotation::CLOCKWISE,-0.1);
			FCameraMan->Update();
		break;

		case Key::RIGHT:
			FAirplane->Roll(AirplaneRotation::ANTICLOCKWISE,0.1);
			FCameraMan->Update();

		case Key::DEBUG0:
			FAirplane->Avance_Debug();
			FCameraMan->Update();
		break;

		case Key::DEBUG1:

		break;
		//Unhandled
	};
	//PRINT_ORANGE<<"[RENDERER]Key pressed handeled"<<END_PRINT_COLOR;
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
	FCameraMan->Update();
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


	FAirplane= new Airplane();
	FAirplane->Build(FRoot);
	
	
	FBuilding = new SceneObject("data/building/building1/building.obj");
	FBuilding->InitObject();
	FRoot->AddModel(FBuilding);

	FBuilding->Translate(osg::Vec3f(0,-3,60));

	FAirplane2 = new SceneObject("data/DRC/DRC.obj");
	FAirplane2->InitObject();
	FAirplane2->Translate(osg::Vec3f(0,-3,60));
    FAirplane2->Roll(3.14);
    FAirplane2->Yaw(3.14);
	FRoot->AddModel(FAirplane2);
	

	FCameraMan = new CameraMan();
	FCameraMan->InitObject();
	FCameraMan->SetDistance(osg::Vec3f(0,-5,-25));
	FCameraMan->Follow(FAirplane->GetNode());
	PRINT_GREEN<<"[RENDERER] Scene successfully created"<<END_PRINT_COLOR;
}


