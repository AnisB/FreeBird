#include "renderer.h"

Renderer::Renderer() 
: FViewer()
{
  
}

Renderer::~Renderer()
{
	
}

void Renderer::UpdateScene(float parDelta)
{
}


void Renderer::Run()
{
	if(!FViewer.isRealized())
	    FViewer.realize();
	while( !FViewer.done() )
	{
	   FViewer.frame();
	}
}

void Renderer::ButtonReleased(Button::Type parButton)
{
	switch (parButton)
	{
		case Button::BUTTON0:
		break;
		
		case Button::BUTTON1:
		break;
		
		case Button::BUTTON2:
		break;
		//Unhandled
	};
}

void Renderer::ButtonPressed(Button::Type parButton)
{
	switch (parButton)
	{
		case Button::BUTTON0:
		break;
		
		case Button::BUTTON1:
		break;
		
		case Button::BUTTON2:
		break;
		//Unhandled
	};
}
void Renderer::Init()
{
	SceneInit();
        OSGInit();	
}

void Renderer::OSGInit()
{
	FViewer.setSceneData( FRoot->GetRoot() );
}

void Renderer::SceneInit()
{
	
	FRoot = new Root();
	FRoot->InitRoot();

	//FRoot->AddLight();
	FAirPlane = new SceneObject("data/DRC/DRC.obj");
	FAirPlane->InitObject();
	FAirPlane->Translate(osg::Vec3f(2,0,-10));
        FAirPlane->Roll(3.14);
	FRoot->AddModel(FAirPlane);

	FViewer.setSceneData( FRoot->GetRoot() );
}


