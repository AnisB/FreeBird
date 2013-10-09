#ifndef MOUSE_HANDLER_FREE_BIRD
#define MOUSE_HANDLER_FREE_BIRD

// OSG include
#include <osgGA/GUIEventHandler>

class KeyboardEventHandler : public osgGA::GUIEventHandler
{
public:
   virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
   virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); };
};

bool KeyboardEventHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
 {
   switch(ea.getEventType())
   {
   case(osgGA::GUIEventAdapter::KEYDOWN):
      {
         switch(ea.getKey())
         {
         case 'w':
            std::cout << " w key pressed" << std::endl;
            return false;
            break;
         default:
            return false;
         } 
      }
   default:
      return false;
   }
}
#endif // MOUSE_HANDLER_FREE_BIRD