

#include "renderer.h"

// Include projet
#include <common/defines.h>

// Constructeur
Renderer::Renderer() 
: FViewer()
, FPhysicsEngine()
, FLastFrameTime(0.0)
, FIsAlive(true)
{
	FInputHandler = new InputEventHandler();
}


// Destructeur
Renderer::~Renderer()
{
	delete FRoot;
	delete FAirplane;
	delete FCameraMan;
	delete FInputHandler;
}

// Mise à jour de la scene
void Renderer::UpdateScene(float parDelta)
{	
	// Si l'airplane est vivant
	if(FIsAlive)
	{
		// On se déplace et on tourne en fonction des entrée clavier et souris
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

		if(FKeyHandler[Key::DEBUG0])
		{
			FCameraMan->ChangeFocalLength(true);
		}
		if(FKeyHandler[Key::DEBUG1])
		{
			FCameraMan->ChangeFocalLength(false);
		}

		//if(FButtonHandler[Button::LEFT])
		{
			FAirplane->Avance_Debug(parDelta);
		}
		FCameraMan->Update();

		// Mise a jour du terrain
		FRoot->UpdateTerrain(FAirplane->GetNode()->GetPosition());
		// Mise a jour du skybox
		FRoot->UpdateSkybox();
		// Test de l'intersection
		Intersect inter = FPhysicsEngine.IsLandCollision(FAirplane->GetNode()->GetPosition());
		// Si intersection de l'avion avec le sol il y a
		if(inter.isValid)
		{
			// On supprime l'avion
			FRoot->RemoveModel(FAirplane->GetNode());
			//ON crée l'epave
			SceneObject * FEpave = new SceneObject("data/DRC/destroy.obj");
			// On l'initialise
			FEpave->InitObject();
			FEpave->Translate(inter.position);
			FEpave->Scale(osg::Vec3f(3.0,3.0,3.0));
			FEpave->Yaw(MathTools::PI	);
			FRoot->AddModel(FEpave);
			// On crée une exploson
			FXExplosion explosion;
			explosion.InitFX(inter.position+osg::Vec3f(0.0,5.0,0.0),3);
			FRoot->GetDynamicModels()->GetNode()->addChild(explosion.GetNode()->GetNode());			
			PRINT_ORANGE<<"COLLISION DUDE"<<END_PRINT_COLOR;
			FIsAlive = false;
		}
		FMitrailleuse.Update(parDelta);
	}
}


void Renderer::Run()
{
	// On vérifie que le viewer est instancié
	if(!FViewer.isRealized())
	{
		// Sinon on l'instancie
	    FViewer.realize();
	}
	// ON initialize la camera
	InitCamera();
	// Tant que l'on a pas fini de render
	while( !FViewer.done() )
	{
		// On calcule le temps entre cette frame et celle d'avant
		double delta = FViewer.elapsedTime() - FLastFrameTime;
		// On met à jour le scene
	    UpdateScene(delta);
	    // On met à jour le temps de la frame précédete
	    FLastFrameTime =  FViewer.elapsedTime();
	    // On produit une frame
	    FViewer.frame();
	}
	// Fin du run
	QuittingRun();
}

void Renderer::QuittingRun()
{
	//suppression du handler
	FViewer.removeEventHandler(FInputHandler);
}

// Gestion des touches
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
		case Button::LEFT:
		{
	        FMitrailleuse.TirerMissile();
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
	// Creation de la scene
	SceneInit();
	// Init osg
    OSGInit();	
}


void Renderer::InitCamera()
{
	// Récupération de camera et attribution au cameraman
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
	// Création du root
	FRoot = new Root();
	FRoot->InitRoot();
	// Création de l'airplane
	FAirplane = new Airplane();
	FAirplane->Build(FRoot);
	//Création du skybox
	FRoot->CreateSkybox(FAirplane->GetNode());
	FRoot->CreateTerrain();
	// Création du cameraman
	FCameraMan = new CameraMan();
	FCameraMan->InitObject();
	FCameraMan->SetDistance(osg::Vec3f(0,-10,-50));
	FCameraMan->Follow(FAirplane->GetModel());
	// Création de la mitrailleuse
	FMitrailleuse.SetRoot(FRoot);
	FMitrailleuse.SetAirplaneModel(FAirplane->GetModel());
	FMitrailleuse.SetAirplaneNode(FAirplane->GetNode());

	PRINT_GREEN<<"[RENDERER] Scene successfully created"<<END_PRINT_COLOR;
}


