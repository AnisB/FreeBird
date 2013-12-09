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

		// Methods to create the terain
		void createTerrain(std::string parFolderName,  Root * parNode);

		//Getters
		SceneNode *  GetNode() {return FTerrain;};
		SceneNode *  GetWater() {return FWater;};

		// Update scene
		void Update(osg::Vec3f parAirplanePos);
		void UpdateVR(osg::Matrixd parWaterMatrix, float parDisplacement);
		void InitVR();
		
	protected:

		// Chargment du terrain
		void LoadTerrain();
		void LoadShader();

		// Chargment de l'eau
		void LoadWater();
		void LoadWaterShader();

		// Creation des decors
		void LoadDecors();
		void Palmiers();
		void HouseGeneration();
		void PalmiersVR();
		void HouseVR();

	protected:

		// Terrain
		SceneObject* FTerrain;
		int FShaderId;

		//Decors
		SceneNode* FDecors;
		SceneObject* FPorteAvion;

		//Water management
		SceneObject* FWater;
		SceneNode* FWaterVR;
		int FWaterShaderId;

};

#endif //TERRAIN_FREE_BIRD
