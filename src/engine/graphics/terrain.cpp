#include "terrain.h"

#include <common/defines.h>
#include "shadermanager.h"
#include <resources/resourcemanager.h>


#include <osg/Geometry>
#include <osg/BlendFunc>

 

#define TERRAIN_MODEL "data/terrain/base/terrain.obj"
#define GET_HEIGHTMAP(textureName, parFolderName) std::string textureName = parFolderName; textureName+="/heightmap.png";


Terrain::Terrain()
: FShaderId(-1)
{

}

Terrain::~Terrain()
{

}


osg::Geometry * GenerateLower()
{
    osg::Vec3Array *vertexArray = new osg::Vec3Array();

    vertexArray->push_back(osg::Vec3f(10000.0, 0.0,-10000.0));
    vertexArray->push_back(osg::Vec3f(10000.0, 0.0,10000.0));
    vertexArray->push_back(osg::Vec3f(-10000.0, 0.0,10000.0));
    vertexArray->push_back(osg::Vec3f(-10000.0, 0.0,-10000.0));


    // face array
    osg::DrawElementsUInt *faceArray = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
     
    // bottom
    faceArray->push_back(0); // face 1
    faceArray->push_back(1);
    faceArray->push_back(2);
    faceArray->push_back(3);

    // normal array
    osg::Vec3Array *normalArray = new osg::Vec3Array();
    normalArray->push_back(osg::Vec3f(0, 1, 0));
    osg::Vec2Array* texcoords = new osg::Vec2Array(4);
    (*texcoords)[0].set(0.0,0.0);
    (*texcoords)[1].set(0.0,10.0);
    (*texcoords)[2].set(10.0,10.0);
    (*texcoords)[3].set(10.0,0.0);

    osg::Geometry *geometry = new osg::Geometry();
    geometry->setVertexArray(vertexArray);
    geometry->setNormalArray(normalArray);
    geometry->addPrimitiveSet(faceArray);
    geometry->setTexCoordArray(0,texcoords);

    return geometry;

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
    

    osg::Geometry * grid = GenerateLower();
    osg::Geode *node = new osg::Geode;
    node->addDrawable(grid);
    FLowerTerrain = new SceneNode();
    FLowerTerrain->InitObject();
    FLowerTerrain->GetNode()->addChild(node);
    FLowerTerrain->Translate(osg::Vec3f(0,1000,0));
    BindTexture(node, "ground","data/terrain/base/ground.jpg",0);


    parNode->AddModel(FLowerTerrain);
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

    BindTexture(FTerrain->GetNode(), "heightMap","data/terrain/base/heightmap.png",0);
    BindTexture(FTerrain->GetNode(), "riverMap","data/terrain/base/river.bmp",1);
    BindTexture(FTerrain->GetNode(), "rockMap","data/terrain/base/rock.bmp",2);
    BindTexture(FTerrain->GetNode(), "ground","data/terrain/base/ground.jpg",3);
    BindTexture(FTerrain->GetNode(), "grass","data/terrain/base/grass.png",4);
    BindTexture(FTerrain->GetNode(), "foam","data/terrain/base/foam.png",5);

    osg::BlendFunc *fuct = new osg::BlendFunc(); 
    fuct->setFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    FTerrain->GetNode()->getStateSet()->setAttributeAndModes(fuct); 
    // osg::StateSet* ss = FTerrain->GetNode()->getOrCreateStateSet(); 
    // ss->setMode(GL_BLEND, osg::StateAttribute:Shocked); 
    // ss->setRenderingHint(osg::StateSet::TRANSPARENT_BIN); 
    // ss->setRenderBinDetails(1, "DepthSortedBin"); 
    //FTerrain->GetNode()->getOrCreateStateSet()->setMode( GL_CULL_FACE, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
    parNode->AddModel(FTerrain);



}
