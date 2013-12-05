#ifndef RENDERER_FREE_BIRD
#define RENDERER_FREE_BIRD

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

//External icludess
#include <vrj/Draw/OSG/OsgApp.h>




class Renderer : public vrj::OsgApp
{
	public:		
		Renderer(vrj::Kernel * parVrjKernel);
		~Renderer();

		void initScene();
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
		// Generic
		Root* FRoot;
		SceneObject * FAirPlane;
		Skybox * FSkybox;
		Mitrailleuse FMitrailleuse;
		// Displacement
		osg::Vec3f FPosition;

		//VRJ
		osg::Matrix mHeadInitPos;
		osg::MatrixTransform*   mNavTrans;
		OsgNavigator mNavigator;

	protected:
		// Time handeling
		vpr::Interval FLastPreFrameTime;
		
		int frameCounter;
		double timePassed;
		
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
