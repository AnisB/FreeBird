#ifndef DEFINES_INPUT_FREE_BIRD
#define DEFINES_INPUT_FREE_BIRD


#include <osgGA/GUIEventAdapter>


namespace Key
{
  enum Type
  {
  	FOWARD = osgGA::GUIEventAdapter::KEY_Z,
  	LEFT = osgGA::GUIEventAdapter::KEY_Q,
  	RIGHT = osgGA::GUIEventAdapter::KEY_D,
  	BACKWARD = osgGA::GUIEventAdapter::KEY_S
  };
}



namespace Button
{
  enum Type
  {
  	RIGHT = osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON,
  	LEFT = osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON,
  	MID = osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON 
  };
}


#endif // DEFINES_INPUT_FREE_BIRD