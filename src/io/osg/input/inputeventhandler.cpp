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
	   		Renderer::Instance().HandleKeyPressed((Key::Type)ea.getKey());
   		break;

    	case osgGA::GUIEventAdapter::KEYUP:
	   		Renderer::Instance().HandleKeyReleased((Key::Type)ea.getKey());
		break;
    	case osgGA::GUIEventAdapter::PUSH:
	   		Renderer::Instance().HandleMousePressed((Button::Type)ea.getButton());
		break;
    	case osgGA::GUIEventAdapter::RELEASE:
	   		Renderer::Instance().HandleMouseReleased((Button::Type)ea.getButton());
		break;
   		default:
      		return false;
   	}
   	return true;
}