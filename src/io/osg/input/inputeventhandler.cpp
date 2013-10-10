#include "inputeventhandler.h"




InputEventHandler::InputEventHandler()
{

}
InputEventHandler::~InputEventHandler()
{

}
bool InputEventHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	switch(ea.getEventType())
   	{
		case osgGA::GUIEventAdapter::KEYDOWN:
	   		Renderer::Instance().KeyPressed((Key::Type)ea.getKey());
   		break;

    	case osgGA::GUIEventAdapter::KEYUP:
	   		Renderer::Instance().KeyReleased((Key::Type)ea.getKey());
		break;
    	case osgGA::GUIEventAdapter::PUSH:
	   		Renderer::Instance().MousePressed((Button::Type)ea.getButton());
		break;
    	case osgGA::GUIEventAdapter::RELEASE:
	   		Renderer::Instance().MouseReleased((Button::Type)ea.getButton());
		break;
		

   		default:
      		return false;
   	}
   	return true;
}