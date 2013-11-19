#include "mitrailleuse.h"

#include <physics/engine.h>
#include <common/random.h>

#define BALLE_VITESSE 5000.0
#define DUREE_COOLDOWN 0.1


Mitrailleuse::Mitrailleuse()
: FCoolDown(0.0)
, FActive(false)
{

}


Mitrailleuse::~Mitrailleuse()
{
	
}
void Mitrailleuse::Update(double parDelta)
{
	if(FActive)
	{
		FCoolDown -= parDelta; 
		if (FCoolDown<=0.0)
		{
			PRINT_ORANGE<<"COOLDOWN ETAT: " <<FCoolDown<<END_PRINT_COLOR;
			TirerBalle();
			FCoolDown = DUREE_COOLDOWN;

		}
	}
	PhysicsEngine & FPhysicsEngine = PhysicsEngine::Instance();
	// Mise a jour des porjectiles
	std::list<std::list<Projectile*>::iterator> toRemove;
	foreach(proj, FProjectiles)
	{
		// On update
		(*proj)->Update(parDelta);
		// Collsion avec le sol?
		if(FPhysicsEngine.IsLandCollision((*proj)->GetNode()->GetPosition()))
		{
			PRINT_ORANGE<<"Projectile a detuire(Sol)"<<END_PRINT_COLOR;
			//FXExplosion explosion = FXExplosion();
			//explosion.InitFX((*proj)->GetNode()->GetPosition());
			//FRootNode->AddModel(explosion.GetNode());
			toRemove.push_back(proj);
		}
		// trop loin, on le detruit
		else if(FPhysicsEngine.IsTooFarCollision(FAirplaneNode->GetPosition(), (*proj)->GetNode()->GetPosition()))
		{
			PRINT_ORANGE<<"Projectile a detuire(Trop loin)"<<END_PRINT_COLOR;
			toRemove.push_back(proj);
		}
	}
	// destruction réelle
	foreach(proj, toRemove)
	{
		FRootNode->RemoveModel((*(*proj))->GetNode());
		delete *(*proj);
		FProjectiles.erase(*proj);
	}

	
}

void Mitrailleuse::TirerBalle()
{
	osg::Vec3f randPos(RandomDet(),RandomDet(),0.0);
	const osg::Matrix& transf = FAirplaneModel->GetTransformation(TransformationSpace::TS_WORLD);
	Bullet * newBullet = new Bullet(randPos, transf,BALLE_VITESSE);
    FRootNode->AddModel(newBullet->GetNode());
    FProjectiles.push_back(newBullet);
}