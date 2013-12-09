#include "mitrailleuse.h"

#include <physics/engine.h>
#include <common/random.h>
#include <graphics/helper.h>

#define DUREE_COOLDOWN 0.2
#define BULLET_SCALE 0.5

#define HOUSE_SCALE 3

#define DUREE_COOLDOWN_MISS 1.0
#define MISSILE_SCALE 10.0

#ifndef VRJUGGLER
#define BALLE_VITESSE 2000.0
#define MISSILE_VITESSE 1000.0
#else
#define BALLE_VITESSE 200.0
#define MISSILE_VITESSE 100.0
#endif

Mitrailleuse::Mitrailleuse()
: FCoolDown(0.0)
, FActive(false)
, FCoolDownMiss(0.0)
, FRight(false)
{

}


Mitrailleuse::~Mitrailleuse()
{
	
}
void Mitrailleuse::Update(double parDelta)
{
	FCoolDownMiss -= parDelta;
	if(FActive)
	{
		FCoolDown -= parDelta; 
		if (FCoolDown<=0.0)
		{
			//PRINT_ORANGE<<"COOLDOWN ETAT: " <<FCoolDown<<END_PRINT_COLOR;
			TirerBalle();
			FCoolDown = DUREE_COOLDOWN;

		}
	}
	UpdateBullet(parDelta);	
	UpdateMissile(parDelta);
}

void Mitrailleuse::UpdateBullet(double parDelta)
{
	PhysicsEngine & FPhysicsEngine = PhysicsEngine::Instance();
	// Mise a jour des porjectiles
	std::list<std::list<Bullet*>::iterator> toRemove;
	foreach(proj, FProjectiles)
	{
		// On update
		(*proj)->Update(parDelta);

		// Collision avec une maison
		int result = FPhysicsEngine.IsHouseCollision((*proj)->GetNode()->GetPosition());
		if(result>=0)
		{
			FXExplosion explosion;
			#ifndef VR_JUGGLER
			explosion.InitFX((*proj)->GetNode()->GetPosition(),HOUSE_SCALE);
			FRootNode->GetDynamicModels()->GetNode()->addChild(explosion.GetNode()->GetNode());
			#else
			//FRootNode->GetDynamicModels()->AddChild(explosion.GetNode());
			//FRootNode->GetDynamicModels()->GetNode()->addChild(explosion.GetNode()->GetNode());			
			#endif
			
			if(FPhysicsEngine.Degats(result,3))
			{
				FXExplosion explosion;
				#ifndef VR_JUGGLER
				explosion.InitFX((*proj)->GetNode()->GetPosition(),HOUSE_SCALE);
				FRootNode->GetDynamicModels()->GetNode()->addChild(explosion.GetNode()->GetNode());
				#else
				//FRootNode->GetDynamicModels()->AddChild(explosion.GetNode());
				//FRootNode->GetDynamicModels()->GetNode()->addChild(explosion.GetNode()->GetNode());	
				#endif
			}
			toRemove.push_back(proj);
		}


		// Collsion avec le sol?
		if(FPhysicsEngine.IsLandCollision((*proj)->GetNode()->GetPosition()).isValid)
		{
			FXExplosion explosion;
			#ifndef VR_JUGGLER
			explosion.InitFX((*proj)->GetNode()->GetPosition(),BULLET_SCALE);
			FRootNode->GetDynamicModels()->GetNode()->addChild(explosion.GetNode()->GetNode());
			#else
			//FRootNode->GetDynamicModels()->AddChild(explosion.GetNode());
			//FRootNode->GetDynamicModels()->GetNode()->addChild(explosion.GetNode()->GetNode());			
			#endif
			toRemove.push_back(proj);

		}
		// trop loin, on le detruit
		#ifdef VRJUGGLER
		else if(FPhysicsEngine.IsTooFarCollision(FAirplaneNode->GetPositionInv(), (*proj)->GetNode()->GetPosition()).isValid)
		#else
		else if(FPhysicsEngine.IsTooFarCollision(FAirplaneNode->GetPosition(), (*proj)->GetNode()->GetPosition()).isValid)
		#endif
		{
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

void Mitrailleuse::UpdateMissile(double parDelta)
{
	PhysicsEngine & FPhysicsEngine = PhysicsEngine::Instance();
	// Mise a jour des porjectiles
	std::list<std::list<Missile*>::iterator> toRemove;
	foreach(proj, FMissiles)
	{
		// On update
		(*proj)->Update(parDelta);
		// Collision avec une maison
		int result = FPhysicsEngine.IsHouseCollision((*proj)->GetNode()->GetPosition());
		if(result>=0)
		{
			FXExplosion explosion;
			explosion.InitFX((*proj)->GetNode()->GetPosition(),MISSILE_SCALE);
			#ifndef VR_JUGGLER
			FRootNode->GetDynamicModels()->GetNode()->addChild(explosion.GetNode()->GetNode());
			#else
			//FRootNode->GetDynamicModels()->AddChild(explosion.GetNode());
			FRootNode->GetDynamicModels()->GetNode()->addChild(explosion.GetNode()->GetNode());			
			#endif
			
			if(FPhysicsEngine.Degats(result,30))
			{
				FXExplosion explosion;
				//explosion.InitFX((*proj)->GetNode()->GetPosition(),HOUSE_SCALE);
				explosion.InitFX((*proj)->GetNode()->GetPosition(),MISSILE_SCALE);
				#ifndef VR_JUGGLER
				FRootNode->GetDynamicModels()->GetNode()->addChild(explosion.GetNode()->GetNode());
				#else
				//FRootNode->GetDynamicModels()->AddChild(explosion.GetNode());
				FRootNode->GetDynamicModels()->GetNode()->addChild(explosion.GetNode()->GetNode());	
				#endif
			}
			
			toRemove.push_back(proj);
		}
		// Collsion avec le sol?
		if(FPhysicsEngine.IsLandCollision((*proj)->GetNode()->GetPosition()).isValid)
		{
			FXExplosion explosion;
			explosion.InitFX((*proj)->GetNode()->GetPosition(),MISSILE_SCALE);
			#ifndef VR_JUGGLER
			FRootNode->GetDynamicModels()->GetNode()->addChild(explosion.GetNode()->GetNode());
			#else
			//FRootNode->GetDynamicModels()->AddChild(explosion.GetNode());
			FRootNode->GetDynamicModels()->GetNode()->addChild(explosion.GetNode()->GetNode());			
			#endif
			toRemove.push_back(proj);
		}
		// trop loin, on le detruit
		#ifdef VRJUGGLER
		else if(FPhysicsEngine.IsTooFarCollision(FAirplaneNode->GetPositionInv(), (*proj)->GetNode()->GetPosition()).isValid)
		#else
		else if(FPhysicsEngine.IsTooFarCollision(FAirplaneNode->GetPosition(), (*proj)->GetNode()->GetPosition()).isValid)
		#endif
		{
			toRemove.push_back(proj);
		}
	}
	// destruction réelle
	foreach(proj, toRemove)
	{
		FRootNode->RemoveModel((*(*proj))->GetNode());
		delete *(*proj);
		FMissiles.erase(*proj);
	}
}

void Mitrailleuse::TirerBalle()
{
	#ifdef VRJUGGLER
	osg::Vec3f randPos(RandomDet(),RandomDet() + 2.0,0.0);
	osg::Matrix transf = FAirplaneNode->GetTransformation();
	transf =osg::Matrix::inverse(transf);
	transf.preMult(osg::Matrix::rotate(MathTools::PI,0.0,1.0,0.0));
	transf.postMult(osg::Matrix::translate(randPos));
	Bullet * newBullet = new Bullet(randPos, transf,BALLE_VITESSE);
	#else
	osg::Vec3f randPos(RandomDet(),RandomDet(),0.0);
	const osg::Matrix& transf = FAirplaneModel->GetTransformation(TransformationSpace::TS_WORLD);
	Bullet * newBullet = new Bullet(randPos, transf,BALLE_VITESSE);
	#endif
    FRootNode->AddModel(newBullet->GetNode());
    FProjectiles.push_back(newBullet);
}


void Mitrailleuse::TirerMissile()
{
	if(FCoolDownMiss<=0)
	{
		FCoolDownMiss =  DUREE_COOLDOWN_MISS;
		osg::Vec3f randPos;
		if(FRight)
		{
			randPos = osg::Vec3f(3,1,0.0);
		}
		else
		{
			randPos = osg::Vec3f(-3,1,0.0);
		}
		FRight=(!FRight);
		#ifdef VRJUGGLER
		osg::Vec3f deplace(0.0,2.0,1.0);
		osg::Matrix transform = FAirplaneNode->GetTransformation();
		transform =osg::Matrix::inverse(transform);
		transform.preMult(osg::Matrix::rotate(MathTools::PI,0.0,1.0,0.0));
		transform.postMult(osg::Matrix::translate(deplace));
		Missile * newBullet = new Missile(randPos, transform,MISSILE_VITESSE);
		#else
		const osg::Matrix& transf = FAirplaneModel->GetTransformation(TransformationSpace::TS_WORLD);
		Missile * newBullet = new Missile(randPos, transf,MISSILE_VITESSE);
		#endif
	    FRootNode->AddModel(newBullet->GetNode());
	    FMissiles.push_back(newBullet);
	}
}
