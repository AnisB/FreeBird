#ifndef KEYBOARD_HANDLER_FREE_BIRD
#define KEYBOARD_HANDLER_FREE_BIRD

// OSG include
#include <osgGA/GUIEventHandler>

#include <renderer/renderer.h>



class Renderer;
class InputEventHandler : public osgGA::GUIEventHandler
{
public:
	InputEventHandler();
	~InputEventHandler();
   	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
   	virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); };
};

#endif // KEYBOARD_HANDLER_FREE_BIRD