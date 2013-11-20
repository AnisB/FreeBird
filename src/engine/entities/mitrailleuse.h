#ifndef MITRAILLEUSE
#define MITRAILLEUSE


#include <graphics/root.h>
#include <graphics/sceneobject.h>
#include <fx/explosion.h>
#include <fx/splash.h>
#include <entities/projectile.h>
#include <fx/fxbase.h>
#include <entities/bullet.h>
#include <entities/missile.h>

class Mitrailleuse
{
	public:
		Mitrailleuse();
		~Mitrailleuse();

		void SetActive(bool parFlag)
		{
			FActive = parFlag;
		}

		void Update(double parDelta);
		void SetRoot(Root* parRoot){FRootNode = parRoot;}
		void SetAirplaneModel(SceneNode* parAirplane){FAirplaneModel = parAirplane;}
		void SetAirplaneNode(SceneNode* parAirplane){FAirplaneNode = parAirplane;}

		void TirerBalle();
		void TirerMissile();
		void UpdateBullet(double parDelta);
		void UpdateMissile(double parDelta);

	protected:
		std::list<Bullet*> FProjectiles;
		std::list<Missile*> FMissiles;
		std::list<FXBase*> FExplosions;
		SceneNode * FAirplaneModel;
		SceneNode * FAirplaneNode;
		Root * FRootNode;

		// Gestion de la mitrailleuse
		bool FActive;
		double FCoolDown;

		// Gestion des missile
		bool FRight;
		double FCoolDownMiss;
};
#endif //MITRAILLEUSE