#ifndef TERRAIN_FREE_BIRD
#define TERRAIN_FREE_BIRD


#include <string>
#include <graphics/root.h>
#include <graphics/sceneobject.h>

#include <osg/Texture2D>

class Root;

class Terrain
{
	public:
		Terrain();
		~Terrain();

		void createTerrain(std::string parFolderName,  Root * parNode);	

	protected:
		SceneObject * FTerrain2;
		SceneObject * FTerrain;
		int FShaderId;

};

#endif //TERRAIN_FREE_BIRD