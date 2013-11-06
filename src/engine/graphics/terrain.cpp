#include "terrain.h"

#include <common/defines.h>
#include "shadermanager.h"
#include <resources/resourcemanager.h>


#include <osg/Geometry>
#include <osg/BlendFunc>

 
#define TERRAIN_MODEL "data/terrain/base/terrain.obj"
#define WATER_MODEL "data/terrain/base/water.obj"
#define GET_HEIGHTMAP(textureName, parFolderName) std::string textureName = parFolderName; textureName+="/heightmap.png";
#define TERRAIN_SIZE 10000

osg::Vec2f ComputeRelativePosition(const osg::Vec3f& parPosition)
{
    osg::Vec2f realPos(fmod(parPosition.x()/TERRAIN_SIZE,1.0), fmod(parPosition.z()/TERRAIN_SIZE,1.0));
    return realPos;
}

Terrain::Terrain()
: FShaderId(-1)
{

}

Terrain::~Terrain()
{

}


void Terrain::UpdateVR(osg::Matrixd parWaterMatrix)
{
    osg::Vec3f waterHeight(parWaterMatrix.getTrans());
    osg::Quat rotation = parWaterMatrix.getRotate();
    osg::Matrix finalMatrix(rotation);
    finalMatrix.postMult(osg::Matrix::translate(waterHeight));
    DEBUG_PRINT("Airplane"<<VEC3_TO_STREAM(waterHeight));
    FWater->GetNode()->setMatrix(finalMatrix);
    //FWater->GetNode()->postMult(osg::Matrix(parWaterMatrix.getRotate()));

    //osg::Vec3f waterPos(parWaterMatrix.getTrans().x(),0.0,parWaterMatrix.getTrans().z());
    //osg::Vec2f relativePos = ComputeRelativePosition(waterPos);
    //InjectVec2(FWater->GetNode(), relativePos, "planePosition");
}

void Terrain::Update(osg::Vec3f parAirplanePos)
{
    osg::Vec3f TerrainPos(parAirplanePos.x(),600, parAirplanePos.z());
    FWater->SetPosition(TerrainPos);

    osg::Vec2f relativePos = ComputeRelativePosition(TerrainPos);
    InjectVec2(FWater->GetNode(), relativePos, "planePosition");
    
    DEBUG_PRINT("Airplane"<<VEC3_TO_STREAM(TerrainPos));
}


void Terrain::createTerrain(std::string parFolderName, Root * parNode)
{

    FTerrain = new SceneObject(TERRAIN_MODEL);
    FTerrain->InitObject();
    FTerrain->Scale(osg::Vec3f(5,5,5));
    //FTerrain->Scale(osg::Vec3f(0.10,0.10,0.10));
    FTerrain->Translate(osg::Vec3f(0.0,120,0.0));
    FTerrain->SetDynamic();
    //FLowerTerrain->Translate(osg::Vec3f(0,1000,0));
    
    FShaderId = ShaderManager::Instance().CreateShader("data/shaders/terrainVertex.glsl","data/shaders/terrainFragment.glsl");
    
    ShaderManager::Instance().ActivateShader(FTerrain->GetNode(), FShaderId);

    BindTexture(FTerrain->GetNode(), "heightMap","data/terrain/base/heightmap.png",0);
    BindTexture(FTerrain->GetNode(), "normalMap","data/terrain/base/normalMap.png",1);
    BindTexture(FTerrain->GetNode(), "riverMap","data/terrain/base/river.jpg",2);
    BindTexture(FTerrain->GetNode(), "ground","data/terrain/base/ground.jpg",3);
    BindTexture(FTerrain->GetNode(), "grass","data/terrain/base/grass.jpg",4);
    BindTexture(FTerrain->GetNode(), "snow","data/terrain/base/snow.jpg",5);
    BindTexture(FTerrain->GetNode(), "sand","data/terrain/base/sand.jpg",6);
    BindCubeMap(FTerrain->GetNode(), "skybox","data/skybox/sky4",7);

    parNode->AddModel(FTerrain);
    
	
    FWater = new SceneObject(TERRAIN_MODEL);
    FWater->InitObject();
    FWater->Scale(osg::Vec3f(5,5,5));
    FWater->SetDynamic();

    FWaterShaderId = ShaderManager::Instance().CreateShader("data/shaders/waterVertex.glsl","data/shaders/waterFragment.glsl");
    ShaderManager::Instance().ActivateShader(FWater->GetNode(), FWaterShaderId);
    BindCubeMap(FWater->GetNode(), "skybox","data/skybox/sky4",0);
    BindTexture(FWater->GetNode(), "normalMap","data/terrain/base/water.jpg",1);


    osg::BlendFunc *fuct = new osg::BlendFunc(); 
    fuct->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    FWater->GetNode()->getStateSet()->setAttributeAndModes(fuct); 
    parNode->AddModel(FWater);
	

    
}
