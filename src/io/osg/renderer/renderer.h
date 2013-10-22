#ifndef RENDERER_FREE_BIRD
#define RENDERER_FREE_BIRD

//Rendering includes
#include <graphics/root.h>
#include <graphics/sceneobject.h>
#include <graphics/cameraman.h>
// Include defines
#include <input/defines.h>
#include <input/inputeventhandler.h>

//Inlcude Entities
#include <entities/airplane.h>
// Project includes
#include <osgViewer/Viewer>


#include <graphics/skybox.h>


class InputEventHandler;

class Renderer : public Singleton<Renderer>
{
	public:		
		Renderer();
		~Renderer();

		// Time handling
		void UpdateScene(float parDelta);

		// Personnal
		void Init();
		void Run();



	public:
		//Input Methods
		void KeyReleased(Key::Type parKey);
		void KeyPressed(Key::Type parKey);

		void MousePressed(Button::Type parButton);
		void MouseReleased(Button::Type parButton);
	
	protected:
		// Init
		void OSGInit();
		void SceneInit();

		// Camera
		void InitCamera();

		void QuittingRun();
		void InitRenderToTexture();





	protected:
		// Scene objetcs
		Root* FRoot;
		Airplane * FAirplane;
		SceneObject * FAirplane2;
		SceneObject * FTerrain;
		// OSG Viewer
		osgViewer::Viewer FViewer;

		// Input Handler
		InputEventHandler * FInputHandler;

		std::map<Key::Type,bool> FKeyHandler;
		std::map<Button::Type,bool> FButtonHandler;

		// Camera
		osg::Camera * FCamera;

		CameraMan * FCameraMan;

		Skybox*	  FSkybox;

};
#endif //RENDERER_FREE_BIRD
