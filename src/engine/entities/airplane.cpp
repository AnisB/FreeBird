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
	FNode->Translate(osg::Vec3f(0,-200,0));
	FNode->AddChild(FModelNode);
	parRootNode->AddModel(FNode);
    //FNode->Pitch(3.14);
    FNode->Yaw(3.14);
}

// Moving methods
void Airplane::Roll(AirplaneRotation::Type parType, float parTime)
{
	if(parType == AirplaneRotation::CLOCKWISE)
		FModelNode->Roll(0.03);	
	else
		FModelNode->Roll(-0.03);	

}
void Airplane::Pitch(AirplaneRotation::Type parType, float parTime)
{
	if(parType == AirplaneRotation::CLOCKWISE)
		FModelNode->Pitch(0.02);	
	else
		FModelNode->Pitch(-0.02);
}

void Airplane::Yaw(AirplaneRotation::Type parType, float parTime)
{
	if(parType == AirplaneRotation::CLOCKWISE)
		FModelNode->Yaw(0.005);	
	else
		FModelNode->Yaw(-0.005);
}

void Airplane::Avance_Debug(double time)
{
	FNode->Translate(osg::Vec3f(0,0,4) * FModelNode->GetTransformation());
}
