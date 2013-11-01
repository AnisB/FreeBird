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
	delete FTerrain;
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
    PRINT_GREEN<< "GLSL current context is: "<<(char*)glGetString(GL_SHADING_LANGUAGE_VERSION)<< END_PRINT_COLOR;

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
}

void Renderer::Init()
{
	SceneInit();
    OSGInit();	
    InitRenderToTexture();
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


void Renderer::InitRenderToTexture()
{
	/*
	float width  = 1440 * 0.35f;
	float height = 900 * 0.35f;
	// Create the texture to render to
	osg::Texture2D* renderTexture = new osg::Texture2D;
	renderTexture->setTextureSize(1440, 900);
	renderTexture->setInternalFormat(GL_RGBA);
	renderTexture->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
	renderTexture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);

	osg::ref_ptr<osg::Geometry> screenQuad;
	screenQuad = osg::createTexturedQuadGeometry(osg::Vec3(),
                                             osg::Vec3(width, 0.0, 0.0),
                                             osg::Vec3(0.0, height, 0.0));
	osg::ref_ptr<osg::Geode> quadGeode = new osg::Geode;
	quadGeode->addDrawable(screenQuad.get());
	osg::StateSet *quadState = quadGeode->getOrCreateStateSet();
	quadState->setTextureAttributeAndModes(0, renderTexture, osg::StateAttribute::ON);


	osg::ref_ptr<osg::Camera> textureCamera = new osg::Camera;
	textureCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	textureCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	textureCamera->setViewport(0, 0, 1440, 900);

	// Frame buffer objects are the best option
	textureCamera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);

	// We need to render to the texture BEFORE we render to the screen
	textureCamera->setRenderOrder(osg::Camera::PRE_RENDER);

	// The camera will render into the texture that we created earlier
	textureCamera->attach(osg::Camera::COLOR_BUFFER, renderTexture);

	// Add whatever children you want drawn to the texture
	textureCamera->addChild(FAirplane->GetModel()->GetModel());


	osg::ref_ptr<osg::Camera> orthoCamera = new osg::Camera;

	// We don't want to apply perspective, just overlay using orthographic
	orthoCamera->setProjectionMatrix(osg::Matrix::ortho2D(0, width, 0, height));

	orthoCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	orthoCamera->setViewMatrix(osg::Matrix::identity());

	// Choose a good spot on the screen to overlay the quad
	float xPos = 1440 * 0.635f;
	float yPos = 900 * 0.625f;

	orthoCamera->setViewport(xPos, yPos, width, height);

	// Make sure to render this after rendering the scene
	// in order to overlay the quad on top
	orthoCamera->setRenderOrder(osg::Camera::POST_RENDER);

	// Render only the quad
	orthoCamera->addChild(quadGeode.get());

	FRoot->GetRoot()->addChild(textureCamera.get());
	FRoot->GetRoot()->addChild(orthoCamera.get());	
	*/
}
void Renderer::OSGInit()
{
	#ifdef TESS
	const int width( 1280 ), height( 720 );
    const std::string version( "4.1" );
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
	
	FRoot->CreateSkybox(FAirplane->GetNode());
	FRoot->CreateTerrain();

	//FTerrain->Translate(osg::Vec3f(0,-20,0));
	//FTerrain->Scale(osg::Vec3f(100,100,100));

	/*
	FAirplane2 = new SceneObject("data/DRC/DRC.obj");
	FAirplane2->InitObject();
	FAirplane2->Translate(osg::Vec3f(0,-200,00));
    FAirplane2->Roll(3.14);
    FAirplane2->Yaw(3.14);
	FRoot->AddModel(FAirplane2);
	*/
	

	FCameraMan = new CameraMan();
	FCameraMan->InitObject();
	FCameraMan->SetDistance(osg::Vec3f(0,-10,-50));
	FCameraMan->Follow(FAirplane->GetModel());

	PRINT_GREEN<<"[RENDERER] Scene successfully created"<<END_PRINT_COLOR;
}


