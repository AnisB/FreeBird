#ifndef RENDERER_FREE_BIRD
#define RENDERER_FREE_BIRD

#include "sceneobject.h"

#include "root.h"
#include <osgViewer/Viewer>

class Renderer : public vrj::OsgApp
{
	public:		
		Renderer(vrj::Kernel * parVrjKernel);
		~Renderer();

		void InitRenderer();

		// Update methods
		virtual void preFrame();
		virtual void latePreFrame();
		virtual void intraFrame();
		virtual void postFrame();

		// Time handling
		void UpdateScene();

		//Input Methods
		void HandleVRJInputs();
		void HandleButton();

	private:
		// VRJ
		void VRInit();
		void HandleVRJInputs();
		float ComputeTime();

		// Personnal
		void Init();

	protected:

		Root* FRoot;
		

		SceneObject * FAirPlane;

	protected:
		// Time handeling
		vpr::Interval FLastPreFrameTime;
		
		// Input handeling
		gadget::PositionInterface FWand;
		gadget::PositionInterface FHead;
		gadget::DigitalInterface FButton0;
		gadget::Digital FB0State;
		gadget::DigitalInterface FButton1;
		gadget::Digital FB1State;
		gadget::DigitalInterface FButton2;
		gadget::Digital FB2State;


};
#endif //RENDERER_FREE_BIRD