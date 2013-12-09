#include "terrain.h"

#include <common/defines.h>
#include "shadermanager.h"
#include <resources/resourcemanager.h>


#include <terrain/const.h>
#include <terrain/helper.h>
#include <physics/engine.h>
#include <entities/house.h>


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

    osg::Vec2f relativePos = ComputeRelativePosition2(-transPrime);
    InjectVec2(FWater->GetNode(), relativePos, "planePosition");	
}
void Terrain::Animation(float parTime)
{
	osg::Matrix mat = FBirds[0]->GetNode()->getMatrix();
	mat.postMult(osg::Matrix::rotate(0.1*parTime, osg::Vec3f(0.0,1.0,0.0)));
	FBirds[0]->GetNode()->setMatrix(mat);

	osg::Matrix mat2 = FBirds[1]->GetNode()->getMatrix();
	mat2.postMult(osg::Matrix::rotate(-0.05*parTime, osg::Vec3f(0.0,1.0,0.0)));
	FBirds[1]->GetNode()->setMatrix(mat2);

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
    HouseGeneration();

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

	SceneObject * bird =  new SceneObject("data/models/bird/birds.3ds");
	bird->InitObject();
	bird->Translate(osg::Vec3f(200,0.0,200.0));
	FDecors->AddChild(bird);
	FBirds.push_back(bird);
	SceneObject * bird2 =  new SceneObject("data/models/bird/eagle.obj");
	bird2->InitObject();
	bird2->Translate(osg::Vec3f(200,0.0,400.0));
	bird2->Scale(osg::Vec3f(10,10,10));
	FDecors->AddChild(bird2);
	FBirds.push_back(bird2);
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
    parNode->AddStaticModel(FWater);
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
void Terrain::HouseGeneration()
{
    std::ifstream infile("data/terrain/base/maisons.txt");
    int a, b, c;
    while (infile >> a >> b >> c)
    {
        PRINT_ORANGE<<"Une  maison à "<< a<<" "<<b<<" "<<c<<" "<<END_PRINT_COLOR;
		House* maison = new House();
        maison->Init(osg::Vec3f((c-1024)*4.9,(1.0-(float)b/255.0)*1080+125,-(a-1024)*4.9));
		SceneNode* node = maison->GetNode();
        node->Pitch(MathTools::PI/2);
        float randVal = (float)(rand() % 5 +5);
        randVal /=10;
        node->Roll(1*randVal);
        node->Scale(osg::Vec3f(2,2,2));
		PhysicsEngine::Instance().AddHouse(maison);
        FDecors->AddChild(node);
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
        House* maison = new House();
        maison->Init(osg::Vec3f(-(c-1024)/2.0,-((1.0-(float)b/255.0))*TerrainConst::WaterHeight,-(a-1024)/2.0));
        SceneNode* node = maison->GetNode();
		//maison->Translate(osg::Vec3f(-(c-1024)/2.0,-((1.0-(float)b/255.0))*TerrainConst::WaterHeight,-(a-1024)/2.0));
        node->Pitch(-MathTools::PI/2);
        float randVal = (float)(rand() % 5 +5);
        randVal /=10;
        node->Roll(1*randVal);
        node->Scale(osg::Vec3f(0.5,0.5,0.5));
		PhysicsEngine::Instance().AddHouse(maison);
        FDecors->AddChild(node);
    }
}

