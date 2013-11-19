#include "projectile.h"


Projectile::Projectile(osg::Vec3f parInitialPosition, osg::Matrix parDirection, double parVelocity, const std::string & parModelName)
: FInitialPosition(parInitialPosition)
, FOrientation(parDirection)
, FCurrentPosition(parInitialPosition)
, FVelocity(parVelocity)
{
	FNode = new SceneNode();
	FNode->InitObject();
	FNode->SetTransformation(parDirection);
	FNode->GetNode()->postMult(osg::Matrix::translate(parInitialPosition));

	FModel = new SceneObject(parModelName);
	FModel->InitObject();
	FModel->Pitch(-MathTools::PI/2);
	FNode->AddChild(FModel);
}

Projectile::~Projectile()
{
}


void Projectile::Update(float parDelta)
{
	FNode->Translate(osg::Vec3f(0.0,0.0,1.0)*parDelta*FVelocity);
}
