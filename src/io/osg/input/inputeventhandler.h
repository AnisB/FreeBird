#ifndef KEYBOARD_HANDLER_FREE_BIRD
#define KEYBOARD_HANDLER_FREE_BIRD

// OSG include
#include <osgGA/GUIEventHandler>

// Include projet
#include <renderer/renderer.h>


// Prédéclaration
class Renderer;

//Class qui permet de gérer les évenements entrants
class InputEventHandler : public osgGA::GUIEventHandler
{

public:
	// Constructeur
	InputEventHandler();
	//Destructeur
	~InputEventHandler();
	// Handler pour un evenement
   	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
   	// Accepter pour un événement
   	virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); };
};

#endif // KEYBOARD_HANDLER_FREE_BIRD