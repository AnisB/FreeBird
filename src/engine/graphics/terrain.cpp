#include "terrain.h"

#include <common/defines.h>
#include "shadermanager.h"
#include <resources/resourcemanager.h>


#include <osg/Geometry>
#include <osg/BlendFunc>

 
#define TERRAIN_MODEL "data/terrain/base/terrain.obj"
#define WATER_MODEL "data/terrain/base/water.obj"
#define GET_HEIGHTMAP(textureName, parFolderName) std::string textureName = parFolderName; textureName+="/heightmap.png";
#define TERRAIN_SIZE_VR 1000
#define TERRAIN_SIZE 5000

osg::Vec2f ComputeRelativePosition(const osg::Vec3f& parPosition)
{
    osg::Vec2f realPos(fmod(parPosition.x()/TERRAIN_SIZE,1.0), fmod(parPosition.z()/TERRAIN_SIZE,1.0));
    return realPos;
}

osg::Vec2f ComputeRelativePositionVR(const osg::Vec3f& parPosition)
{
    osg::Vec2f realPos(fmod(parPosition.x()/TERRAIN_SIZE_VR,1.0), fmod(parPosition.z()/TERRAIN_SIZE_VR,1.0));
    return realPos;
}

Terrain::Terrain()
: FShaderId(-1)
{

}

Terrain::~Terrain()
{

}


void Terrain::UpdateVR(osg::Matrixd parRotationMatrix, float parDisplacement)
{
	osg::Matrix currentMatrix = FTerrain->GetNode()->getMatrix();
	currentMatrix.postMult(parRotationMatrix);
	currentMatrix.postMult(osg::Matrix::translate(osg::Vec3f(0.0,0.0,parDisplacement)));
	FTerrain->GetNode()->setMatrix(currentMatrix);

	osg::Matrix currentWaterMatrix = FWaterVR->GetNode()->getMatrix();
	currentWaterMatrix.postMult(parRotationMatrix);
	currentWaterMatrix.postMult(osg::Matrix::translate(osg::Vec3f(0.0,0.0,parDisplacement)));
	FWaterVR->GetNode()->setMatrix(currentWaterMatrix);

	osg::Vec3f scale = currentWaterMatrix.getScale();
	osg::Vec3f transPrime = -(osg::Matrix::inverse(currentWaterMatrix).getTrans());
	osg::Vec3f waterHeight(0.0,transPrime.y(),0.0);
	osg::Quat rotation = currentWaterMatrix.getRotate();
	osg::Matrix finalMatrix(rotation);
	finalMatrix.preMult(osg::Matrix::translate(waterHeight));
	finalMatrix.preMult(osg::Matrix::scale(scale));
	FWater->GetNode()->setMatrix(finalMatrix);

    osg::Vec2f relativePos = ComputeRelativePositionVR(-transPrime);
    InjectVec2(FWater->GetNode(), relativePos, "planePosition");
  
}

void Terrain::InitVR()
{
	
}

void Terrain::Update(osg::Vec3f parAirplanePos)
{
    osg::Vec3f TerrainPos(parAirplanePos.x(),590, parAirplanePos.z());
    FWater->SetPosition(TerrainPos);

    osg::Vec2f relativePos = ComputeRelativePosition(TerrainPos);
    InjectVec2(FWater->GetNode(), relativePos, "planePosition");
    
    DEBUG_PRINT("Airplane"<<VEC3_TO_STREAM(TerrainPos));
}


void Terrain::createTerrainVR(std::string parFolderName, Root * parNode)
{

    FTerrain = new SceneObject(TERRAIN_MODEL);
    FTerrain->InitObject();
    //FTerrain->Scale(osg::Vec3f(5,5,5));
   
    FTerrain->SetDynamic();
    FTerrain->Pitch(MathTools::PI);
    FTerrain->Translate(osg::Vec3f(0.0,100,0.0));

    
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
    //FWater->Scale(osg::Vec3f(5,5,5));
    FWater->Pitch(MathTools::PI);
    FWater->Translate(osg::Vec3f(0.0,120.0,0.0));

    FWaterShaderId = ShaderManager::Instance().CreateShader("data/shaders/waterVertex.glsl","data/shaders/waterFragment.glsl");
    ShaderManager::Instance().ActivateShader(FWater->GetNode(), FWaterShaderId);
    BindCubeMap(FWater->GetNode(), "skybox","data/skybox/sky4",0);
    BindTexture(FWater->GetNode(), "normalMap","data/terrain/base/water.jpg",1);


    osg::BlendFunc *fuct = new osg::BlendFunc(); 
    fuct->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    FWater->GetNode()->getStateSet()->setAttributeAndModes(fuct); 
    parNode->AddModel(FWater);

    FWaterVR = new SceneNode();
    FWaterVR->InitObject();
    //FWaterVR->Scale(osg::Vec3f(5,5,5));
    FWaterVR->GetNode()->setMatrix(FWater->GetNode()->getMatrix());


    //parNode->AddModel(FWaterVR);
}



void Terrain::createTerrain(std::string parFolderName, Root * parNode)
{

    FTerrain = new SceneObject(TERRAIN_MODEL);
    FTerrain->InitObject();
    FTerrain->Scale(osg::Vec3f(5,5,5));
    FTerrain->Translate(osg::Vec3f(0.0,120,0.0));
    FTerrain->SetDynamic();
    
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
    
	
    FWater = new SceneObject(WATER_MODEL);
    FWater->InitObject();
    FWater->Scale(osg::Vec3f(5,5,5));

    FWaterShaderId = ShaderManager::Instance().CreateShader("data/shaders/waterVertex.glsl","data/shaders/waterFragment.glsl");
    ShaderManager::Instance().ActivateShader(FWater->GetNode(), FWaterShaderId);
    BindCubeMap(FWater->GetNode(), "skybox","data/skybox/sky4",0);
    BindTexture(FWater->GetNode(), "normalMap","data/terrain/base/water.jpg",1);


    osg::BlendFunc *fuct = new osg::BlendFunc(); 
    fuct->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    FWater->GetNode()->getStateSet()->setAttributeAndModes(fuct); 
    parNode->AddModel(FWater);
}
