#ifndef ROOT_FREE_BIRD
#define ROOT_FREE_BIRD

#include "scenenode.h"


#include <graphics/terrain.h>

class Terrain;

class Root : public SceneNode
{
	public:		
		Root();
		~Root();

		void InitRoot();

		osg::Group* GetRoot(){ return FRoot;}

		void AddModel(SceneNode * parNode);
		void AddLight();


	protected:
		osg::Group*   FRoot;
		osg::Group*	  mModelGroup;
		osg::Group*	  mLightGroup;
		Terrain * FTerrain;

};
#endif //ROOT_FREE_BIRD
