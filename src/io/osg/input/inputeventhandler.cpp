#include "inputeventhandler.h"


// Constructeur
InputEventHandler::InputEventHandler()
{
	// Nothing to do
}
// Destructeur
InputEventHandler::~InputEventHandler()
{
	// Nothing to do
}

// Handler d'evenement
bool InputEventHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	switch(ea.getEventType())
   	{
   		// Touche appuiyée
		case osgGA::GUIEventAdapter::KEYDOWN:
	   		Renderer::Instance().HandleKeyPressed((Key::Type)ea.getKey());
   		break;
   		// Touche relachée
    	case osgGA::GUIEventAdapter::KEYUP:
	   		Renderer::Instance().HandleKeyReleased((Key::Type)ea.getKey());
		break;
		// Boutton appuiyé
    	case osgGA::GUIEventAdapter::PUSH:
	   		Renderer::Instance().HandleMousePressed((Button::Type)ea.getButton());
		break;
		// Boutton relaché
    	case osgGA::GUIEventAdapter::RELEASE:
	   		Renderer::Instance().HandleMouseReleased((Button::Type)ea.getButton());
		break;
   		default:
      		return false;
   	}
   	return true;
}