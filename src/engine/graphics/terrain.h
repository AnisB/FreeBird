#ifndef TERRAIN_FREE_BIRD
#define TERRAIN_FREE_BIRD


#include <string>
#include <graphics/root.h>
#include <graphics/sceneobject.h>

#include <osg/Texture2D>
#include <osg/Geode>

class Root;

class Terrain
{
	public:
		Terrain();
		~Terrain();

		void createTerrain(std::string parFolderName,  Root * parNode);
		void createTerrainVR(std::string parFolderName,  Root * parNode);
		SceneNode *  GetNode() {return FTerrain;};
		SceneNode *  GetWater() {return FWater;};

		void Update(osg::Vec3f parAirplanePos);
		void UpdateVR(osg::Matrixd parWaterMatrix, float parDisplacement);
		void InitVR();
		
		protected:
			void Palmiers();
			void House();

	protected:
		SceneObject* FTerrain;
		SceneNode* FDecors;
		SceneObject* FPorteAvion;
		SceneObject* FWater;
		SceneNode* FWaterVR;
		int FShaderId;
		int FWaterShaderId;

};

#endif //TERRAIN_FREE_BIRD
