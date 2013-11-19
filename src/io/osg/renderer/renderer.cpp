#include "renderer.h"


#include <common/defines.h>

Renderer::Renderer() 
: FViewer()
, FPhysicsEngine()
, FLastFrameTime(0.0)
{
	FInputHandler = new InputEventHandler();
}

Renderer::~Renderer()
{
	delete FRoot;
	delete FAirplane;
	delete FCameraMan;
}

void Renderer::UpdateScene(float parDelta)
{	
	if(FKeyHandler[Key::FOWARD])
	{
		FAirplane->Pitch(AirplaneRotation::ANTICLOCKWISE,parDelta);
	}

	if(FKeyHandler[Key::BACKWARD])
	{
		FAirplane->Pitch(AirplaneRotation::CLOCKWISE,parDelta);
	}

	if(FKeyHandler[Key::LEFT])
	{
		FAirplane->Roll(AirplaneRotation::ANTICLOCKWISE,parDelta);
	}
	if(FKeyHandler[Key::RIGHT])
	{
		FAirplane->Roll(AirplaneRotation::CLOCKWISE,parDelta);
	}

	if(FKeyHandler[Key::DIAGONAL_LEFT])
	{
		FAirplane->Yaw(AirplaneRotation::ANTICLOCKWISE,parDelta);
	}
	if(FKeyHandler[Key::DIAGONAL_RIGHT])
	{
		FAirplane->Yaw(AirplaneRotation::CLOCKWISE,parDelta);
	}

	if(FButtonHandler[Button::LEFT])
	{
		FAirplane->Avance_Debug(parDelta);
	}
	if(FKeyHandler[Key::DEBUG0])
	{
		FCameraMan->ChangeFocalLength(true);
	}
	if(FKeyHandler[Key::DEBUG1])
	{
		FCameraMan->ChangeFocalLength(false);
	}
	FCameraMan->Update();


	FRoot->UpdateTerrain(FAirplane->GetNode()->GetPosition());
	FRoot->UpdateSkybox();
	if(FPhysicsEngine.IsLandCollision(FAirplane->GetNode()->GetPosition()))
	{
		PRINT_ORANGE<<"COLLISION DUDE"<<END_PRINT_COLOR;
	}

	FMitrailleuse.Update(parDelta);
}


void Renderer::Run()
{
	if(!FViewer.isRealized())
	    FViewer.realize();
	InitCamera();
    PRINT_GREEN<< "GLSL current context is: "<<(char*)glGetString(GL_SHADING_LANGUAGE_VERSION)<< END_PRINT_COLOR;

	while( !FViewer.done() )
	{
		double delta = FViewer.elapsedTime() - FLastFrameTime;
	    UpdateScene(delta);
	    FLastFrameTime =  FViewer.elapsedTime();
	    FViewer.frame();
	}
	QuittingRun();
}

void Renderer::QuittingRun()
{
	FViewer.removeEventHandler(FInputHandler);
}
void Renderer::HandleKeyReleased(Key::Type parKey)
{
	tryget(it,FKeyHandler, parKey);
	if (it!=FKeyHandler.end())
	{
		if (!it->second)
		{
			return;
		}
		else
		{	
			it->second = false;
			KeyReleased(parKey);
		}
	}
	else
	{
		FKeyHandler[parKey] = false;
		KeyReleased(parKey);

	}
}
void Renderer::HandleKeyPressed(Key::Type parKey)
{
	tryget(it,FKeyHandler, parKey);
	if (it!=FKeyHandler.end())
	{

		if (it->second)
		{
			return;
		}
		else
		{	
			it->second = true;
			KeyPressed(parKey);
		}
	}
	else
	{
		FKeyHandler[parKey] = true;
		KeyPressed(parKey);

	}
}




void Renderer::HandleMousePressed(Button::Type parButton)
{
	tryget(it,FButtonHandler, parButton);
	if (it!=FButtonHandler.end())
	{
		if (it->second)
		{
			return;
		}
		else
		{	
			it->second = true;
			MousePressed(parButton);
		}
	}
	else
	{
		FButtonHandler[parButton] = true;
		MousePressed(parButton);
	}
}

void Renderer::HandleMouseReleased(Button::Type parButton)
{
	tryget(it,FButtonHandler, parButton);
	if (it!=FButtonHandler.end())
	{

		if (!it->second)
		{
			return;
		}
		else
		{	
			it->second = false;
			MouseReleased(parButton);
		}
	}
	else
	{
		FButtonHandler[parButton] = false;
		MouseReleased(parButton);
	}
}


void Renderer::KeyReleased(Key::Type parKey)
{
}
void Renderer::KeyPressed(Key::Type parKey)
{
	switch(parKey)
	{
		break;
		default:
		break;
	};

}

void Renderer::MousePressed(Button::Type parButton)
{
	switch(parButton)
	{
		case Button::RIGHT:
			{
		        FMitrailleuse.SetActive(true);
		    }
		break;
		default:
		break;
	};
}

void Renderer::MouseReleased(Button::Type parButton)
{
	switch(parButton)
	{
		case Button::RIGHT:
			{
		        FMitrailleuse.SetActive(false);
		    }
		break;
		default:
		break;
	};
}

void Renderer::Init()
{
	SceneInit();
    OSGInit();	
    InitRenderToTexture();
}


void Renderer::InitCamera()
{
	std::vector<osg::Camera*> cameraList;
	FViewer.getCameras(cameraList, true);
	FCamera = cameraList[0];
	FCameraMan->SetCamera(FCamera);
	FCameraMan->Update();
}


void Renderer::InitRenderToTexture()
{

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
	
	FRoot->CreateSkybox(FAirplane->GetNode());
	FRoot->CreateTerrain();

	FCameraMan = new CameraMan();
	FCameraMan->InitObject();
	FCameraMan->SetDistance(osg::Vec3f(0,-10,-50));
	FCameraMan->Follow(FAirplane->GetModel());

	FMitrailleuse.SetRoot(FRoot);
	FMitrailleuse.SetAirplaneModel(FAirplane->GetModel());
	FMitrailleuse.SetAirplaneNode(FAirplane->GetNode());

	PRINT_GREEN<<"[RENDERER] Scene successfully created"<<END_PRINT_COLOR;
}


