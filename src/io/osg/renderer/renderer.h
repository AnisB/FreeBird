#ifndef RENDERER_FREE_BIRD
#define RENDERER_FREE_BIRD

//Rendering includes
#include <graphics/root.h>
#include <graphics/sceneobject.h>
#include <graphics/cameraman.h>
// Include defines
#include <input/defines.h>
#include <input/inputeventhandler.h>


// Project includes
#include <osgViewer/Viewer>

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




	protected:
		// Scene objetcs
		Root* FRoot;
		SceneObject * FAirplane;
		// OSG Viewer
		osgViewer::Viewer FViewer;

		// Input Handler
		InputEventHandler * FInputHandler;

		// Camera
		osg::Camera * FCamera;

		CameraMan * FCameraMan;
};
#endif //RENDERER_FREE_BIRD
