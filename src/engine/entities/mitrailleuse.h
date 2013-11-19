#ifndef MITRAILLEUSE
#define MITRAILLEUSE


#include <graphics/root.h>
#include <graphics/sceneobject.h>
#include <fx/explosion.h>
#include <entities/projectile.h>
#include <entities/bullet.h>

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

	protected:
		std::list<Projectile*> FProjectiles;
		SceneNode * FAirplaneModel;
		SceneNode * FAirplaneNode;
		Root * FRootNode;

		bool FActive;
		double FCoolDown;
};
#endif //MITRAILLEUSE