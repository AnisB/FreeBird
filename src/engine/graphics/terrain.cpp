#include "terrain.h"

#include <common/defines.h>
#include "shadermanager.h"
#include <resources/resourcemanager.h>


#include <osg/Geometry>

 

#define TERRAIN_MODEL "data/terrain/base/terrain.obj"
#define GET_HEIGHTMAP(textureName, parFolderName) std::string textureName = parFolderName; textureName+="/heightmap.png";


Terrain::Terrain()
: FShaderId(-1)
{

}

Terrain::~Terrain()
{

}

/*
osg::Geometry * GenerateGrid(size_t parGridResolution, size_t parGridUnitSize)
{
    osg::Vec3Array *vertexArray = new osg::Vec3Array();
    osg::DrawElementsUInt *faceArray = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    osg::Vec3Array *normalArray = new osg::Vec3Array();
    osg::Vec2Array* texcoords = new osg::Vec2Array(parGridResolution*parGridResolution);

    for(size_t i =0; i<parGridResolution; i++)
        for(size_t j =0; j<parGridResolution; j++)
        {
            vertexArray->push_back(osg::Vec3f(i*parGridUnitSize,j*parGridUnitSize,0));
            (*texcoords)[i*parGridResolution + j].set(i*1.0/(parGridResolution-1.0),j*1.0/(parGridResolution-1.0));
        }

    for(size_t i =0; i<parGridResolution -1; i++)
    {
        for(size_t j =0; j<parGridResolution; j++)
        {
            faceArray->push_back(j+i*parGridResolution);
            faceArray->push_back(j+(i+1)*parGridResolution);
            faceArray->push_back((j+1)+(i+1)*parGridResolution);
            faceArray->push_back((j+1)+i*parGridResolution);
            normalArray->push_back(osg::Vec3f(0, 1, 0));
        }
    }
    osg::Geometry *geometry = new osg::Geometry();
    geometry->setVertexArray(vertexArray);
    geometry->setNormalArray(normalArray);
    geometry->addPrimitiveSet(faceArray);
    geometry->setTexCoordArray(0,texcoords);

    return geometry;

}

    osg::Geometry * grid = GenerateGrid(500, 1);
    FTerrain = new osg::Geode;
    FTerrain->addDrawable(grid);
*/

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
    
    ShaderManager::Instance().ActivateShader(FTerrain->GetNode(), FShaderId);

    osg::StateSet* brickState = FTerrain->GetNode()->getOrCreateStateSet();

    osg::Texture2D * heighmap = ResourceManager::Instance().LoadTexture("data/terrain/base/heightmap.tif");
    ShaderManager::Instance().InitUniform_Texture("heightMap",FTerrain->GetNode(), 0);
    brickState->setTextureAttributeAndModes(0, heighmap, osg::StateAttribute::ON);

    osg::Texture2D * river = ResourceManager::Instance().LoadTexture("data/terrain/base/river.bmp");
    ShaderManager::Instance().InitUniform_Texture("riverMap",FTerrain->GetNode(), 1);
    brickState->setTextureAttributeAndModes(1, river, osg::StateAttribute::ON);

    osg::Texture2D * rock = ResourceManager::Instance().LoadTexture("data/terrain/base/rock.bmp");
    ShaderManager::Instance().InitUniform_Texture("rockMap",FTerrain->GetNode(), 2);
    brickState->setTextureAttributeAndModes(2, rock, osg::StateAttribute::ON);

    osg::Texture2D * ground = ResourceManager::Instance().LoadTexture("data/terrain/base/ground.jpg");
    ShaderManager::Instance().InitUniform_Texture("ground",FTerrain->GetNode(), 3);
    brickState->setTextureAttributeAndModes(3, ground, osg::StateAttribute::ON);

    osg::Texture2D * grass = ResourceManager::Instance().LoadTexture("data/terrain/base/grass.png");
    ShaderManager::Instance().InitUniform_Texture("grass",FTerrain->GetNode(), 4);
    brickState->setTextureAttributeAndModes(4, grass, osg::StateAttribute::ON);

    osg::Texture2D * foam = ResourceManager::Instance().LoadTexture("data/terrain/base/foam.png");
    ShaderManager::Instance().InitUniform_Texture("foam",FTerrain->GetNode(), 5);
    brickState->setTextureAttributeAndModes(5, foam, osg::StateAttribute::ON);

    parNode->AddModel(FTerrain);
}
