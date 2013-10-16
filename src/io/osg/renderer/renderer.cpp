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
	//delete FTerrain;
	delete FCameraMan;
}

void Renderer::UpdateScene(float parDelta)
{	
	FCameraMan->Update();
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
}


void Renderer::Run()
{

	if(!FViewer.isRealized())
	    FViewer.realize();
	InitCamera();
	while( !FViewer.done() )
	{
	   UpdateScene(FViewer.elapsedTime());
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
		}
	}
	else
	{
		FKeyHandler[parKey] = false;
	}
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
		}
	}
	else
	{
		FKeyHandler[parKey] = true;
	}
/*
	//PRINT_ORANGE<<"[RENDERER]Key pressed recieved"<<END_PRINT_COLOR;
	switch (parKey)
	{
		case Key::FOWARD:
			FCameraMan->Update();
			
		break;
		
		case Key::BACKWARD:
			FAirplane->Pitch(AirplaneRotation::ANTICLOCKWISE,0.1);
			FCameraMan->Update();

		break;
		
		case Key::LEFT:
			FAirplane->Roll(AirplaneRotation::ANTICLOCKWISE,-0.1);
			FCameraMan->Update();
		break;

		case Key::RIGHT:
			FAirplane->Roll(AirplaneRotation::CLOCKWISE,0.1);
			FCameraMan->Update();
			break;
		case Key::DEBUG0:
			FAirplane->Avance_Debug();
			FCameraMan->Update();
		break;

		case Key::DEBUG1:
			FCameraMan->ChangeFocalLength(true);
		break;
		case Key::DEBUG2:
			FCameraMan->ChangeFocalLength(false);
		break;
		default:
			PRINT("KEY UNHANDLED");
		//Unhandled
	};
	*/
	//PRINT_ORANGE<<"[RENDERER]Key pressed handeled"<<END_PRINT_COLOR;
}

void Renderer::MousePressed(Button::Type parButton)
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
		}
	}
	else
	{
		FButtonHandler[parButton] = true;
	}
	PRINT_ORANGE<<"[RENDERER]BUTTON PRESSED"<<END_PRINT_COLOR;

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
		}
	}
	else
	{
		FButtonHandler[parButton] = false;
	}
	PRINT_ORANGE<<"[RENDERER]BUTTON RELEASED"<<END_PRINT_COLOR;
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
	#ifndef TESS
	std::vector<osg::Camera*> cameraList;
	FViewer.getCameras(cameraList, true);
	FCamera = cameraList[0];
	FCameraMan->SetCamera(FCamera);
	FCameraMan->Update();
	#endif
}

void Renderer::OSGInit()
{
	#ifdef TESS
	const int width( 1280 ), height( 720 );
    const std::string version( "3.2" );
    osg::ref_ptr< osg::GraphicsContext::Traits > traits = new osg::GraphicsContext::Traits();
    traits->x = 20; traits->y = 30;
    traits->width = width; traits->height = height;
    traits->windowDecoration = true;
    traits->doubleBuffer = true;
    traits->glContextVersion = version;
    osg::ref_ptr< osg::GraphicsContext > gc = osg::GraphicsContext::createGraphicsContext( traits.get() );
    if( !gc.valid() )
    {
        PRINT_RED<< "Unable to create OpenGL v" << version << " context." << END_PRINT_COLOR;
        exit(1) ;
    }
    else
    {
        PRINT_GREEN<< "OpenGL current context is: " << version << END_PRINT_COLOR;
    }

    // Create a Camera that uses the above OpenGL context.
    FCamera = new osg::Camera;
    FCamera->setGraphicsContext( gc.get() );
    // Must set perspective projection for fovy and aspect.
    FCamera->setProjectionMatrix( osg::Matrix::perspective( 30., (double)width/(double)height, 1., 100. ) );
    // Unlike OpenGL, OSG viewport does *not* default to window dimensions.
    FCamera->setViewport( new osg::Viewport( 0, 0, width, height ) );

	FCameraMan->SetCamera(FCamera);
	FCameraMan->Update();
	FViewer.setCamera(FCamera);
	#endif
	FViewer.setSceneData( FRoot->GetRoot() );
	FViewer.addEventHandler(FInputHandler);
}

void Renderer::SceneInit()
{
	
	FRoot = new Root();
	FRoot->InitRoot();


	FAirplane= new Airplane();
	FAirplane->Build(FRoot);
	
	
	//FTerrain = new SceneObject("data/terrain/snow/snow.obj");
	//FTerrain->InitObject();
	//FTerrain->Pitch(MathTools::PI);
	//FRoot->AddModel(FTerrain);

	//FTerrain->Translate(osg::Vec3f(0,-20,0));
	//FTerrain->Scale(osg::Vec3f(100,100,100));

	FAirplane2 = new SceneObject("data/DRC/DRC.obj");
	FAirplane2->InitObject();
	FAirplane2->Translate(osg::Vec3f(0,-200,00));
    FAirplane2->Roll(3.14);
    FAirplane2->Yaw(3.14);
	FRoot->AddModel(FAirplane2);
	

	FCameraMan = new CameraMan();
	FCameraMan->InitObject();
	FCameraMan->SetDistance(osg::Vec3f(0,-10,-50));
	FCameraMan->Follow(FAirplane->GetModel());

	FSkybox = new Skybox();
	FSkybox->createSkybox("data/skybox/sky4", FAirplane->GetNode());
	PRINT_GREEN<<"[RENDERER] Scene successfully created"<<END_PRINT_COLOR;
}


