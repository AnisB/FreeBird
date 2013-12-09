// Include du header
#include "renderer.h"

// Include projet
#include "helper.h"
#include <common/defines.h>
#include <common/helper.h>	
#include <physics/engine.h>

// Includes exrérieurs
#include <osgText/Font>
#include <osgText/Text>

// Constantes utiles pour les parties
#define FIRST_FRAME 10
static float PLANE_SPEED =  30.0;
#define HYPER_SPEED 2.0
static float TOTAL_TIME =  120.0;

// Sytème de son
FMOD_SYSTEM *systemSound;


// Constructeur
Renderer::Renderer(vrj::Kernel * parKernel) 
: vrj::OsgApp(parKernel)
, FB0State(gadget::Digital::OFF)
, FB1State(gadget::Digital::OFF)
, FB2State(gadget::Digital::OFF)
, frameCounter(0)
, timePassed(0.0)
, FIsAlive(false)
, FIsMaitre(false)
{

}

// Destructeur
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
// Mise à jour de la scene
void Renderer::UpdateScene(float parDelta)
{
	//Calcul de la matrice de wand
	const gmtl::Matrix44f wand_mat( FWand->getData(getDrawScaleFactor()));
	// Conversion en osg
	osg::Matrix wandRotation = GmtlToOsg_RotationOnly(wand_mat);
	// Inversion
	wandRotation = osg::Matrix::inverse(wandRotation);
	// Interposlation de la rotation (car elle est trop grande sinon)
	osg::Matrix rotationMatrix = Interpolate(wandRotation, parDelta);

	// Si le personnage est en vie
	if(FIsAlive)
	{
		// Ce calcul est le cacul physique réaliste du déplacement de l'avion, étant donné le manque de temps, e n'ai pas eu le 
		// temps de faire un équilibrage dessus le déplacement initial est préférable dans ce cas
		/*
		FSpeed = PhysicsEngine::Instance().ComputeNewSpeed(FSpeed,osg::Matrix::inverse(FRoot->GetDynamicModels()->GetNode()->getMatrix()),rotationMatrix.getRotate(),parDelta);
		if(FSpeed.length ()>=30)
		{
			FSpeed/=FSpeed.length();
			FSpeed*=30;
		}
		*/
		// Mise à jour du graphe de scene
		FRoot->UpdateVR(rotationMatrix,FSpeed,PLANE_SPEED,parDelta);
		// Mise à jour du skybox
		FRoot->SkyboxVR(osg::Matrix::rotate(FRoot->GetDynamicModels()->GetNode()->getMatrix().getRotate()));
		// Mise à jour de la mitraillese ainsi que des projectiles
		FMitrailleuse.Update(parDelta);

		// Onrécupère la matrice de transformation de l'avion au point de la scene
		osg::Matrix toWorld;
		toWorld=osg::Matrix::inverse(FRoot->GetDynamicModels()->GetNode()->getMatrix());
		toWorld.preMult(FAirPlane->GetNode()->getMatrix());
		// On utilise cette position pour tester l'intersection avec le sol
		Intersect inter = PhysicsEngine::Instance().IsLandCollision(toWorld.getTrans());
		if(inter.isValid)
		{
			// SI intersection il ya on supprime l'avion du graphe de scene
			FRoot->RemoveStaticModel(FAirPlane);
			// On crée la transformation de l'épave pouyr la placer au bon endroit
			osg::Matrix transf(FRoot->GetDynamicModels()->GetNode()->getMatrix());
			transf = osg::Matrix::inverse(transf);
			FEpave->GetNode()->setMatrix(transf);
			FEpave->Translate(osg::Vec3f(0.0,3.0,-10.0));
			
			// On rajoute l'epave au graphe de scene
			FRoot->AddModel(FEpave);
			// On modifie le flag de vie
			FIsAlive = false;
			// On définie la couleur de l'hud comme rouge
			FObjectif->setColor(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
			// On joue le son d'explosion 
			FMOD_System_PlaySound(systemSound, FMOD_CHANNEL_FREE, sonMort, 0, NULL);
		}
		// On réduit le temps restant
		FTimer-=parDelta;
		if(PhysicsEngine::Instance().GetDetruits()==PhysicsEngine::Instance().GetNbCibles())
		{
			// Toutes les cibles ont été détruites
			FIsAlive = false;
			// On affiche le score en vert
			FObjectif->setColor(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
		}
		if(FTimer<=0)
		{
			// temps imparti fini
			FIsAlive = false;
			// Affichage de l'hud en rouge
			FObjectif->setColor(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
		}
		// On affiche temps restant et score
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
		// On affiche uniquemlent le score final
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
// Inits VRJ
void Renderer::VRInit()
{
	FWand.init(WAND_NAME_STR);
	FHead.init(HEAD_NAME_STR);
	FButton0.init(B0_NAME_STR);
	FButton1.init(B1_NAME_STR);
	FButton2.init(B2_NAME_STR);
}

// Initialisation du conteu de la scene
void Renderer::InitSceneContent()
{
	// Initialisation du son
	FMOD_RESULT res = FMOD_System_Create(&systemSound);
	res = FMOD_System_Init(systemSound, 5	, FMOD_INIT_NORMAL, NULL);
	if(res== FMOD_OK)
	{
		FIsMaitre=true;
	}
	// Création de la racine de la scen
	FRoot = new Root();
	FRoot->InitRoot();
	// Création de l'avion
	FAirPlane = new SceneObject("data/DRC/DRC.obj");
	FAirPlane->InitObject();
	//Création de l'epave
	FEpave = new SceneObject("data/DRC/destroy.obj");
	FEpave->InitObject();
	//FAirPlane = new SceneObject("data/cockpit/cockpit.obj");
	//Création du skybox
	FRoot->CreateSkybox(FAirPlane);
	//Création du terrain
	FRoot->CreateTerrain();
	//Initi du navigateur
	mNavigator.init();

	// Intialisaiton de l'avion
	const gmtl::Matrix44f head_matrix( FHead->getData(getDrawScaleFactor()));
	mHeadInitPos = GmtlToOsg(head_matrix);
	FAirPlane->GetNode()->setMatrix(mHeadInitPos);
	FAirPlane->Pitch(MathTools::PI);
	FAirPlane->Translate(osg::Vec3f(-0.11,0.0,12));
	FRoot->AddStaticModel(FAirPlane);

	FEpave->GetNode()->setMatrix(mHeadInitPos);
	// init de la mitrailleuse
	FMitrailleuse.SetRoot(FRoot);
	FMitrailleuse.SetAirplaneModel(FAirPlane);
	FMitrailleuse.SetAirplaneNode(FRoot->GetDynamicModels());

	PRINT_GREEN<<"Scene well initiated "<<END_PRINT_COLOR;
	// Flag de vie
	FIsAlive = true;
	// Vitesse de déplacement
	FSpeed = osg::Vec3f(0.0,0.0,PLANE_SPEED);


	//Création de la zone de texte
	FGeode = new osg::Geode();
	FTransform = new osg::MatrixTransform();
	FStateSet = new osg::StateSet();
	FObjectif = new  osgText::Text;
	FGeode->addDrawable( FObjectif );

	FStateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
	FGeode->setStateSet(FStateSet.get());

	FObjectif->setColor(osg::Vec4(0.0f,0.0f,0.0f,0.8f));
	FObjectif->setLineSpacing(0.7);
	FObjectif->setCharacterSize(5.0);
	FObjectif->setPosition(osg::Vec3(0.f,15.0f,-30.0f));
	FObjectif->setAlignment(osgText::Text::CENTER_CENTER);
	FObjectif->setBackdropColor(osg::Vec4(1.0f,1.0f,1.0f,0.6f));
	FObjectif->setBackdropType(osgText::Text::OUTLINE);


	FTransform->addChild(FGeode.get());
	FRoot->GetRoot()->addChild(FTransform.get());
	FTimer =  TOTAL_TIME;
	FMitrailleuse.Init(FIsMaitre);
	// Si on est dans cv maitre crée les son etc
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


