#include "terrain.h"

#include <common/defines.h>
#include "shadermanager.h"
#include <resources/resourcemanager.h>
 

#define TERRAIN_MODEL "data/terrain/base/terrain.obj"
#define GET_HEIGHTMAP(textureName, parFolderName) std::string textureName = parFolderName; textureName+="/heightmap.png";


Terrain::Terrain()
: FShaderId(-1)
{

}

Terrain::~Terrain()
{

}

void Terrain::createTerrain(std::string parFolderName, Root * parNode)
{

    FTerrain = new SceneObject(TERRAIN_MODEL);
  	FTerrain->InitObject();
    //FTerrain->Scale(osg::Vec3f(0.01,0.01,0.01));
    FTerrain->Scale(osg::Vec3f(10,10,10));
    FTerrain->Pitch(MathTools::PI/2);
  	FTerrain->SetDynamic();
    
    
    #ifdef WITH_TESSELLATION    
    FShaderId = ShaderManager::Instance().CreateShaderTess("data/shaders/terrainVertex.glsl", 
                                                            "data/shaders/tessControl.glsl",
                                                            "data/shaders/tessEval.glsl",
                                                            "data/shaders/terrainFragment.glsl");
    #else
    FShaderId = ShaderManager::Instance().CreateShader("data/shaders/terrainVertex.glsl","data/shaders/terrainFragment.glsl");
    #endif
    
    ShaderManager::Instance().ActivateShader(FTerrain->GetModel(), FShaderId);

	  osg::StateSet* brickState = FTerrain->GetNode()->getOrCreateStateSet();

    osg::Texture2D * river = ResourceManager::Instance().LoadTexture("data/terrain/base/river.bmp");
    ShaderManager::Instance().InitUniform_Texture("riverMap",FTerrain->GetNode(), 1);
    brickState->setTextureAttributeAndModes(1, river, osg::StateAttribute::ON);

    osg::Texture2D * rock = ResourceManager::Instance().LoadTexture("data/terrain/base/rock.bmp");
    ShaderManager::Instance().InitUniform_Texture("rockMap",FTerrain->GetNode(), 2);
    brickState->setTextureAttributeAndModes(2, rock, osg::StateAttribute::ON);

    osg::Texture2D * ground = ResourceManager::Instance().LoadTexture("data/terrain/base/ground.jpg");
    ShaderManager::Instance().InitUniform_Texture("ground",FTerrain->GetNode(), 3);
    brickState->setTextureAttributeAndModes(3, ground, osg::StateAttribute::ON);

    osg::Texture2D * grass = ResourceManager::Instance().LoadTexture("data/terrain/base/grass.jpg");
    ShaderManager::Instance().InitUniform_Texture("grass",FTerrain->GetNode(), 4);
    brickState->setTextureAttributeAndModes(4, grass, osg::StateAttribute::ON);

    parNode->AddModel(FTerrain);
}
