#ifndef RENDERER_FREE_BIRD
#define RENDERER_FREE_BIRD

// Incluess génériques
#include <stdio.h>
#include <string.h>

//Rendering includes
#include <graphics/root.h>
#include <graphics/skybox.h>
#include <graphics/sceneobject.h>

//Mitrailleuse
#include <entities/mitrailleuse.h>

//INPUT && NAV
#include <input/defines.h>
#include <input/nav.h>

//External icludes
//vrj
#include <vrj/Draw/OSG/OsgApp.h>
//osg
#include <osgText/Font>
#include <osgText/Text>


// system sound as a global var
extern FMOD_SYSTEM *systemSound;

// Classe principale du rendu
class Renderer : public vrj::OsgApp
{
	public:		
		// Constructeur
		Renderer(vrj::Kernel * parVrjKernel);
		//Destructeur
		~Renderer();

		// Méthode d'init de la scene
		void initScene();
		// Méthode qui renvoie la scene
		osg::Group* getScene();

		// Update methods
		virtual void preFrame();
		virtual void latePreFrame();
		virtual void intraFrame();
		virtual void postFrame();

		// Time handling
		void UpdateScene(float parDelta);


	private:
		// VRJ
		void VRInit();
		void HandleVRJInputs();
		float ComputeTime();

		//Input Methods
		void HandleButton(gadget::DigitalInterface & parButton,
			 	gadget::Digital::State& parState, 
				Button::Type parButtonID);
		void ButtonReleased(Button::Type parButton);
		void ButtonPressed(Button::Type parButton);
		// Personnal
		void InitSceneContent();

	protected:
		// Osg generic
		Root* FRoot;
		SceneObject * FAirPlane;
		SceneObject * FEpave;
		Skybox * FSkybox;
		Mitrailleuse FMitrailleuse;

		// Displacement
		osg::Vec3f FPosition;
		osg::Vec3f FSpeed;

		// HUD text
		osgText::Text * FObjectif;
		// Gestion du texte
		osg::ref_ptr<osg::Geode> FGeode;
		osg::ref_ptr<osg::MatrixTransform> FTransform;
		osg::ref_ptr<osg::StateSet> FStateSet;
		
		//VRJ
		osg::Matrix mHeadInitPos;
		osg::MatrixTransform*   mNavTrans;
		OsgNavigator mNavigator;

	protected:
		// Time handeling
		vpr::Interval FLastPreFrameTime;
		//Attributs pour l'init
		int frameCounter;
		double timePassed;

		// Flag de vie de l'avion
		bool FIsAlive;
		// String contenant l'information
		std::string FTimeString;
		std::string FScoreString;

		// Conteneurs des sons
		FMOD_SOUND * sonTheme;
		FMOD_SOUND *sonControlTower;
		FMOD_SOUND *sonMort;
		//Timer pour la partie
		float FTimer;
		// Flag qui définit si on est sur la machine maitre (Pour le son)
		bool FIsMaitre;


	protected:
		// Input handeling
		gadget::PositionInterface FWand;
		gadget::PositionInterface FHead;
		gadget::DigitalInterface FButton0;
		gadget::Digital::State FB0State;
		gadget::DigitalInterface FButton1;
		gadget::Digital::State FB1State;
		gadget::DigitalInterface FButton2;
		gadget::Digital::State FB2State;


};
#endif //RENDERER_FREE_BIRD
