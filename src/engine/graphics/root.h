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
		void CreateTerrain();

		osg::Group* GetRoot(){ return FRoot;}
		osg::MatrixTransform* GetDynamicModels(){ return mNavModelGroup;}
		osg::MatrixTransform* GetStaticModels(){ return mNoNavModelGroup;}

		void AddModel(SceneNode * parNode);
		void AddStaticModel(SceneNode * parNode);
		void AddNode(osg::Node * parNode);
		void AddLight();


	protected:
		osg::Group*   FRoot;
		osg::MatrixTransform*   mNavModelGroup;
		osg::MatrixTransform*   mNoNavModelGroup;
		osg::Group*   mLightGroup;

		Terrain * FTerrain;

};
#endif //ROOT_FREE_BIRD
