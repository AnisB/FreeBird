#ifndef RENDERER_FREE_BIRD
#define RENDERER_FREE_BIRD

//Rendering includes
#include <graphics/root.h>
#include <graphics/sceneobject.h>
// Include defines
#include <input/defines.h>

// Project includes
#include <osgViewer/Viewer>

class Renderer
{
	public:		
		Renderer();
		~Renderer();

		// Time handling
		void UpdateScene(float parDelta);

		// Personnal
		void Init();
		void Run();


	private:
		//Input Methods
		void ButtonReleased(Button::Type parButton);
		void ButtonPressed(Button::Type parButton);
	
		void OSGInit();
		void SceneInit();

	protected:
		// Scene objetcs
		Root* FRoot;
		SceneObject * FAirPlane;
		// OSG Viewer
		osgViewer::Viewer FViewer;
};
#endif //RENDERER_FREE_BIRD
