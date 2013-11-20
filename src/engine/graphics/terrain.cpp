#include "terrain.h"

#include <common/defines.h>
#include "shadermanager.h"
#include <resources/resourcemanager.h>


#include <terrain/const.h>
#include <terrain/helper.h>



#include <fstream>
#include <osg/Geometry>
#include <osg/BlendFunc>


Terrain::Terrain()
: FShaderId(-1)
{

}

Terrain::~Terrain()
{

}


void Terrain::UpdateVR(osg::Matrixd parRotationMatrix, float parDisplacement)
{
    FTerrain->Rotate(parRotationMatrix);
	osg::Matrix currentMatrix = FTerrain->GetNode()->getMatrix();
	currentMatrix.postMult(osg::Matrix::translate(osg::Vec3f(0.0,0.0,parDisplacement)));
	FTerrain->GetNode()->setMatrix(currentMatrix);

	osg::Matrix currentWaterMatrix = FWaterVR->GetNode()->getMatrix();
	currentWaterMatrix.postMult(parRotationMatrix);
	currentWaterMatrix.postMult(osg::Matrix::translate(osg::Vec3f(0.0,0.0,parDisplacement)));
	FWaterVR->GetNode()->setMatrix(currentWaterMatrix);

	osg::Matrix currentDecorsMatrix = FDecors->GetNode()->getMatrix();
	currentDecorsMatrix.postMult(parRotationMatrix);
	currentDecorsMatrix.postMult(osg::Matrix::translate(osg::Vec3f(0.0,0.0,parDisplacement)));
	FDecors->GetNode()->setMatrix(currentDecorsMatrix);

	osg::Vec3f scale = currentWaterMatrix.getScale();
	osg::Vec3f transPrime = -(osg::Matrix::inverse(currentWaterMatrix).getTrans());
	osg::Vec3f waterHeight(0.0,transPrime.y(),0.0);
	osg::Quat rotation = currentWaterMatrix.getRotate();
	osg::Matrix finalMatrix(rotation);
	finalMatrix.preMult(osg::Matrix::translate(waterHeight));
	finalMatrix.preMult(osg::Matrix::scale(scale));
	FWater->GetNode()->setMatrix(finalMatrix);

    osg::Vec2f relativePos = ComputeRelativePosition(-transPrime);
    InjectVec2(FWater->GetNode(), relativePos, "planePosition");
  
}

void Terrain::InitVR()
{
	
}

void Terrain::Update(osg::Vec3f parAirplanePos)
{
    osg::Vec3f TerrainPos(parAirplanePos.x(),TerrainConst::WaterHeight, parAirplanePos.z());
    FWater->SetPosition(TerrainPos);
    osg::Vec2f relativePos = ComputeRelativePosition(TerrainPos);
    InjectVec2(FWater->GetNode(), relativePos, "planePosition");
}


void Terrain::LoadTerrain()
{
    FTerrain = new SceneObject(TERRAIN_MODEL);
    FTerrain->InitObject();
    FTerrain->SetDynamic();
    #ifdef VRJUGGLER
    FTerrain->Pitch(MathTools::PI);
    FTerrain->Translate(osg::Vec3f(0.0,100,0.0));
    #else
    FTerrain->Scale(osg::Vec3f(TerrainConst::WorldScale,TerrainConst::WorldScale,TerrainConst::WorldScale));
    FTerrain->Translate(osg::Vec3f(0.0,120,0.0));
    #endif
}

void Terrain::LoadShader()
{
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
}

void Terrain::LoadDecors()
{
    FDecors = new SceneNode();
    FDecors->InitObject();
#ifdef VRJUGGLER
    PalmiersVR();
    HouseVR();

#else
    Palmiers();
    House();

#endif

    FPorteAvion = new SceneObject(PORTE_AVION);
    FPorteAvion->InitObject();

#ifdef VRJUGGLER
    FPorteAvion->Translate(osg::Vec3f(TerrainConst::PorteAvionX,-TerrainConst::WaterHeight,TerrainConst::PorteAvionZ));
    FPorteAvion->Pitch(-MathTools::PI/2);
    FPorteAvion->Scale(osg::Vec3f(20,20,20));
#else
    FPorteAvion->Translate(osg::Vec3f(TerrainConst::PorteAvionX,TerrainConst::WaterHeight,TerrainConst::PorteAvionZ));
    FPorteAvion->Pitch(MathTools::PI/2);
    FPorteAvion->Scale(osg::Vec3f(200,200,200));
#endif

    LoadBaseShader(FPorteAvion->GetNode());
    FDecors->AddChild(FPorteAvion);

}


void Terrain::LoadWater()
{
    FWater = new SceneObject(WATER_MODEL);
    FWater->InitObject();
    #ifdef VRJUGGLER
    FWater->Pitch(MathTools::PI);
    FWater->Translate(osg::Vec3f(0.0,TerrainConst::WaterHeight,0.0));
    FWaterVR = new SceneNode();
    FWaterVR->InitObject();
    FWaterVR->GetNode()->setMatrix(FWater->GetNode()->getMatrix());
    #else
    FWater->Scale(osg::Vec3f(5,5,5));
    #endif
}

void Terrain::LoadWaterShader()
{
    FWaterShaderId = ShaderManager::Instance().CreateShader("data/shaders/waterVertex.glsl","data/shaders/waterFragment.glsl");
    ShaderManager::Instance().ActivateShader(FWater->GetNode(), FWaterShaderId);
    BindCubeMap(FWater->GetNode(), "skybox","data/skybox/sky4",0);
    BindTexture(FWater->GetNode(), "normalMap","data/terrain/base/water.jpg",1);
}


void Terrain::createTerrain(std::string parFolderName, Root * parNode)
{
    //Chargment du terrain
    LoadTerrain();
    LoadShader();
    parNode->AddModel(FTerrain);
    
    LoadDecors();
    parNode->AddModel(FDecors);

    LoadWater();
    LoadWaterShader();
    parNode->AddModel(FWater);
}

void Terrain::Palmiers()
{
    std::ifstream infile("data/terrain/base/palmiers.txt");
    int a, b, c;
    while (infile >> a >> b >> c)
    {
        PRINT_ORANGE<<"Un nouveau palmier à "<< a<<" "<<b<<" "<<c<<" "<<END_PRINT_COLOR;
        SceneObject* palmier = new SceneObject(PALMIER);
        palmier->InitObject();
        palmier->Translate(osg::Vec3f((c-1024)*4.9,(1.0-(float)b/255.0)*1080+120,-(a-1024)*4.9));
        palmier->Pitch(MathTools::PI/2);
        float randVal = (float)(rand() % 5 +5);
        randVal /=20;
        palmier->Roll(1*randVal);
        palmier->Scale(osg::Vec3f(randVal,randVal,randVal));

        FDecors->AddChild(palmier);
    }
}
void Terrain::House()
{
    std::ifstream infile("data/terrain/base/maisons.txt");
    int a, b, c;
    while (infile >> a >> b >> c)
    {
        PRINT_ORANGE<<"Une  maison à "<< a<<" "<<b<<" "<<c<<" "<<END_PRINT_COLOR;
        SceneObject* maison = new SceneObject(HOUSE);
        maison->InitObject();
        maison->Translate(osg::Vec3f((c-1024)*4.9,(1.0-(float)b/255.0)*1080+125,-(a-1024)*4.9));
        maison->Pitch(MathTools::PI/2);
        float randVal = (float)(rand() % 5 +5);
        randVal /=10;
        maison->Roll(1*randVal);
        maison->Scale(osg::Vec3f(2,2,2));
        FDecors->AddChild(maison);
    }
}

void Terrain::PalmiersVR()
{
    std::ifstream infile("data/terrain/base/palmiers.txt");
    int a, b, c;
    while (infile >> a >> b >> c)
    {
        PRINT_ORANGE<<"Un nouveau palmier à "<< a<<" "<<b<<" "<<c<<" "<<END_PRINT_COLOR;
        SceneObject* palmier = new SceneObject(PALMIER);
        palmier->InitObject();
        palmier->Translate(osg::Vec3f(-(c-1024)/2.0,-((1.0-(float)b/255.0))*TerrainConst::WaterHeight,-(a-1024)/2.0));
        palmier->Pitch(-MathTools::PI/2);
        float randVal = (float)(rand() % 5 +5);
        randVal /=100;
        palmier->Roll(1*randVal);
        palmier->Scale(osg::Vec3f(randVal,randVal,randVal));

        FDecors->AddChild(palmier);
    }
}
void Terrain::HouseVR()
{
    std::ifstream infile("data/terrain/base/maisons.txt");
    int a, b, c;
    while (infile >> a >> b >> c)
    {
        PRINT_ORANGE<<"Une  maison à "<< a<<" "<<b<<" "<<c<<" "<<END_PRINT_COLOR;
        SceneObject* maison = new SceneObject(HOUSE);
        maison->InitObject();
        maison->Translate(osg::Vec3f(-(c-1024)/2.0,-((1.0-(float)b/255.0))*TerrainConst::WaterHeight,-(a-1024)/2.0));
        maison->Pitch(-MathTools::PI/2);
        float randVal = (float)(rand() % 5 +5);
        randVal /=10;
        maison->Roll(1*randVal);
        maison->Scale(osg::Vec3f(0.5,0.5,0.5));
        FDecors->AddChild(maison);
    }
}

