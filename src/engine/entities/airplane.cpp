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
	//FModelNode =  new SceneObject("data/DRC/DRC.obj");
	FModelNode =  new SceneObject("data/cockpit/cockpit.obj");
	FModelNode->InitObject();
	FNode =  new SceneNode();
	FNode->InitObject();
	FNode->AddChild(FModelNode);

	parRootNode->AddModel(FNode);
}

// Moving methods
void Airplane::Roll(AirplaneRotation::Type parType, float parTime)
{
	if(parType == AirplaneRotation::CLOCKWISE)
		FModelNode->Roll(1.2*parTime);	
	else
		FModelNode->Roll(-1.2*parTime);	

}
void Airplane::Pitch(AirplaneRotation::Type parType, float parTime)
{
	if(parType == AirplaneRotation::CLOCKWISE)
		FModelNode->Pitch(1.0*parTime);	
	else
		FModelNode->Pitch(-1.0*parTime);
}

void Airplane::Yaw(AirplaneRotation::Type parType, float parTime)
{
	if(parType == AirplaneRotation::CLOCKWISE)
		FModelNode->Yaw(0.3*parTime);	
	else
		FModelNode->Yaw(-0.3*parTime);
}

void Airplane::ForceTransformation(osg::Matrix parForceTransformation)
{
	FModelNode->GetNode()->setMatrix(parForceTransformation);
}
void Airplane::Avance_Debug(double parTime)
{
	FNode->Translate(osg::Vec3f(0,0,500*parTime) * FModelNode->GetTransformation());
}
