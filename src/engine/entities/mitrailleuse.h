#ifndef MITRAILLEUSE
#define MITRAILLEUSE

// Includes graphiques
#include <graphics/root.h>
#include <graphics/sceneobject.h>

//Includes fx
#include <fx/explosion.h>
#include <fx/splash.h>
#include <fx/fxbase.h>
//Includes entities
#include <entities/projectile.h>
#include <entities/bullet.h>
#include <entities/missile.h>

// Include son
#ifdef VRJUGGLER
#include <fmod.h>
#endif

class Mitrailleuse
{
	public:
		Mitrailleuse();
		~Mitrailleuse();
		// Initialisation de la mitrailleuse
		void Init(bool parFlag);
		// Activation (balles rapides)
		void SetActive(bool parFlag)
		{
			FActive = parFlag;
		}
		// Mise a jour
		void Update(double parDelta);
		// Definition du noeud racide
		void SetRoot(Root* parRoot){FRootNode = parRoot;}
		// Definiton des noeud erlatifs
		void SetAirplaneModel(SceneNode* parAirplane){FAirplaneModel = parAirplane;}
		void SetAirplaneNode(SceneNode* parAirplane){FAirplaneNode = parAirplane;}
		// tirer une balle
		void TirerBalle();
		// Tirer un missile
		void TirerMissile();
		// Maj balles
		void UpdateBullet(double parDelta);
		// Maj missile
		void UpdateMissile(double parDelta);

	protected:
		// Liste des balle
		std::list<Bullet*> FProjectiles;
		// Liste des missiles
		std::list<Missile*> FMissiles;
		// Liste des effets
		std::list<FXBase*> FExplosions;
		// Les noeufs référnce
		SceneNode * FAirplaneModel;
		SceneNode * FAirplaneNode;
		// Noeud racine
		Root * FRootNode;

		// Gestion de la mitrailleuse
		bool FActive;
		double FCoolDown;
		double FCoolDownSound;
		// Gestion duu son
		#ifdef VRJUGGLER
		FMOD_SOUND *sonBalle;
		FMOD_SOUND *sonMissile;
		FMOD_SOUND *sonExplosion;
		#endif
		// Flag de cv maitre actuel
		bool FIsMaitre;

		// Gestion des missile
		bool FRight;
		double FCoolDownMiss;
};
#endif //MITRAILLEUSE
