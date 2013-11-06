#ifndef ROOT_FREE_BIRD
#define ROOT_FREE_BIRD

#include "scenenode.h"


#include <graphics/terrain.h>
#include <graphics/skybox.h>

class Terrain;
class Skybox;

class Root : public SceneNode
{
	public:		
		Root();
		~Root();

		void InitRoot();
		void CreateTerrain();
		void CreateSkybox(SceneNode* toFollow);

		osg::Group* GetRoot(){ return FRoot;}
		Terrain* GetTerrain(){ return FTerrain;}
		Skybox* GetSkybox(){ return FSkybox;}
		osg::MatrixTransform* GetDynamicModels(){ return mNavModelGroup;}
		osg::MatrixTransform* GetStaticModels(){ return mNoNavModelGroup;}

		void AddModel(SceneNode * parNode);
		void AddStaticModel(SceneNode * parNode);
		void AddNode(osg::Node * parNode);
		void AddLight();


		void UpdateTerrain(osg::Vec3f parPosition);
		void UpdateSkybox();
	protected:
		osg::Group*   FRoot;
		osg::MatrixTransform*   mNavModelGroup;
		osg::MatrixTransform*   mNoNavModelGroup;
		osg::Group*   mLightGroup;

		Terrain * FTerrain;
		Skybox* FSkybox;

};
#endif //ROOT_FREE_BIRD
