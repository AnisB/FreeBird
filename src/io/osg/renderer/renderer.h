#ifndef RENDERER_FREE_BIRD
#define RENDERER_FREE_BIRD

// Ce renderer est uniquement réservé 
// au simulateur version openscenegraph

//graphics includes
#include <graphics/root.h>
#include <graphics/sceneobject.h>
#include <graphics/cameraman.h>

// physics includes
#include <physics/engine.h>
// Include defines
#include <input/defines.h>
#include <input/inputeventhandler.h>

//Inlcude Entities
#include <entities/airplane.h>
#include <entities/mitrailleuse.h>

// Osg includes
#include <osgViewer/Viewer>
#include <graphics/skybox.h>
#include <osgText/Font>
#include <osgText/Text>

// Predeclaration
class InputEventHandler;

// Class principale pour le rendu en osg uniquement
class Renderer : public Singleton<Renderer>
{
	public:		
		// Constructeur
		Renderer();
		// Destructeur
		~Renderer();

		// Mise a jour de la scene
		void UpdateScene(float parDelta);

		// Init du renderer
		void Init();
		// Lancement du rendering
		void Run();


	public:
		//Input Methods
		void HandleKeyReleased(Key::Type parKey);
		void HandleKeyPressed(Key::Type parKey);

		void HandleMousePressed(Button::Type parButton);
		void HandleMouseReleased(Button::Type parButton);

		void MousePressed(Button::Type parButton);
		void MouseReleased(Button::Type parButton);

		void KeyReleased(Key::Type parKey);
		void KeyPressed(Key::Type parKey);

	protected:
		// Init
		void OSGInit();
		void SceneInit();

		// Camera
		void InitCamera();

		void QuittingRun();


	protected:
		// Scene objetcs
		Root* FRoot;
		Airplane * FAirplane;
		Mitrailleuse FMitrailleuse;
		osgText::Text * FObjectif;
		osgText::Text * FTime;
		bool FIsAlive;
		// OSG Viewer
		osgViewer::Viewer FViewer;

		// Physics
		PhysicsEngine FPhysicsEngine;
		// Input Handler
		InputEventHandler * FInputHandler;

		std::map<Key::Type,bool> FKeyHandler;
		std::map<Button::Type,bool> FButtonHandler;

		// Camera
		osg::Camera * FCamera;
		CameraMan * FCameraMan;
		Skybox*	  FSkybox;

		double FLastFrameTime;

};
#endif //RENDERER_FREE_BIRD
