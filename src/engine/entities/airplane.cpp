// Projet includes
#include "airplane.h"


#include <common/defines.h>




Airplane::Airplane()
{

}
Airplane::~Airplane()
{

}

void Airplane::Build(Root * parRootNode)
{
	FModelNode =  new SceneObject("data/DRC/DRC.obj");
	FModelNode->InitObject();
	FNode =  new SceneNode();
	FNode->InitObject();
	FNode->Translate(osg::Vec3f(0,-2,-30));
	FNode->AddChild(FModelNode);
	parRootNode->AddModel(FNode);
    FNode->Pitch(3.14);
}

// Moving methods
void Airplane::Roll(AirplaneRotation::Type parType, float parTime)
{
	if(parType == AirplaneRotation::CLOCKWISE)
		FNode->Roll(0.1);	
	else
		FNode->Roll(-0.1);	

}
void Airplane::Pitch(AirplaneRotation::Type parType, float parTime)
{
	if(parType == AirplaneRotation::CLOCKWISE)
		FModelNode->Pitch(0.1);	
	else
		FModelNode->Pitch(-0.1);
}


void Airplane::Avance_Debug()
{
	FNode->Translate(osg::Vec3f(0,0,4) * FModelNode->GetTransformation());
}
