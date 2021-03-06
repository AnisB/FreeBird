#ifndef AIR_PLANE_FREE_BIRD
#define AIR_PLANE_FREE_BIRD

// Projet includes
#include <graphics/scenenode.h>
#include <graphics/sceneobject.h>
#include <graphics/root.h>

#include <fx/explosion.h>



// Rotations 
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
		SceneNode * GetModel() {return FModelNode;}
		void Avance_Debug(double time);
		
		// Moving methods
		void Roll(AirplaneRotation::Type parType, float parTime);
 		void Pitch(AirplaneRotation::Type parType, float parTime);
 		void Yaw(AirplaneRotation::Type parType, float parTime);


		// Debug methods
		void ForceTransformation(osg::Matrix parForceTransformation);
	protected:
			SceneNode * FModelNode;			
			SceneNode * FNode;	
};



#endif // AIR_PLANE_FREE_BIRD
