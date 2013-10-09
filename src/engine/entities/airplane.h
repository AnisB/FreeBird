#ifndef AIR_PLANE_FREE_BIRD
#define AIR_PLANE_FREE_BIRD

// Projet includes
#include <graphics/scenenode.h>
#include <graphics/sceneobject.h>
#include <graphics/root.h>



namespace AirplaneRotation
{
	enum Type
	{
		CLOCKWISE,
		ANTICLOCKWISE
	};
}
class Airplane
{
	public:
		Airplane();
		~Airplane();
		
		void Build(Root * parRoot);

		SceneNode * GetNode() {return FNode;}
		void Avance_Debug();
		
		// Moving methods
		void Roll(AirplaneRotation::Type parType, float parTime);
 		void Pitch(AirplaneRotation::Type parType, float parTime);

	protected:
			SceneNode * FModelNode;			
			SceneNode * FNode;			
};



#endif // AIR_PLANE_FREE_BIRD
