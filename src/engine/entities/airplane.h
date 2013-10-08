#ifndef AIR_PLANE_FREE_BIRD
#define AIR_PLANE_FREE_BIRD

// Projet includes
#include <graphics/sceneobjetc.h>



namespace AirplaneRotation
{
	enum Type
	{
		CLOCKWISE,
		ANTICLOCKWISE
	}
}
class Airplane
{
	public:
		Airplane();
		~Airplane();
		
		void Build();
		
		// Moving methods
		void Roll(AirplaneRotation::Type parType, float parTime);
 		void Pitch(AirplaneRotation::Type parType, float parTime);

	protected:
		SceneObject * FNode;
							
};



#endif // AIR_PLANE_FREE_BIRD
