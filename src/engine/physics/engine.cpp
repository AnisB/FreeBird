#include "engine.h"


#include <terrain/helper.h>
#include <terrain/const.h>

#include <common/defines.h>

PhysicsEngine::PhysicsEngine()
{
	FTerrainHeight = ResourceManager::Instance().LoadTexture("data/terrain/base/heightmap.png")->getImage();
}
PhysicsEngine::~PhysicsEngine()
{

}


bool PhysicsEngine::IsLandCollision(const osg::Vec3f& planePosition)
{
	// On convertit la position de l'avion en coordonnées texture centralisée
	osg::Vec2f position = ComputeRelativePosition(planePosition);
	//PRINT_ORANGE<<"Position centralisé "<<position.x()<<" "<position.y()<<END_PRINT_COLOR;
	//PRINT_ORANGE<<"Position centralisé "<<VEC2_TO_STREAM(position)<<END_PRINT_COLOR;
	//PRINT_ORANGE<<"Hateur de l'objet "<<planePosition.y()<<END_PRINT_COLOR;
	if(position.x()>0.5 || position.y()>0.5 || position.x()<-0.5 || position.y()<-0.5)
	{
		// on est en decors de la map de base, il suffit de tester la hauteur
		#ifndef VRJUGGLER
		if( planePosition.y()>TerrainConst::WaterHeight)
		#else
		if( (-planePosition.y())>TerrainConst::WaterHeight)
		#endif
		{
			PRINT_ORANGE<<"Collision eau"<<END_PRINT_COLOR;
			return true;
		}
	}  
	
    else
	{
		// On convertit en coordonnées texture opengl
		#ifndef VRJUGGLER
		float sCoord = (position.x()+0.5)*2048;
		float tCoord = (position.y()+0.5)*2048;
		#else
		float sCoord = (position.x()+0.5)*2048;
		float tCoord = (-position.y()+0.5)*2048;
		#endif
		// On récupère la hauteur
		double height = FTerrainHeight->getColor(sCoord,tCoord).r();
		// On convertit la hauteur en coordonnées réelle
		#ifndef VRJUGGLER
		height *=1000.0;
		height = TerrainConst::WaterHeight-height;
		#else
		height*=TerrainConst::WaterHeight;
		height = height-TerrainConst::WaterHeight+1;
		#endif

		
		double compareTo = planePosition.y();
		//PRINT_ORANGE<<"Compare " <<compareTo<<" VS "<<height<<END_PRINT_COLOR;
		// Sommes nous en dessous du terrain?
		#ifdef VRJUGGLER
		if((height) > compareTo)
		#else
		if((height) < compareTo)
		#endif
		{
			//PRINT_ORANGE<<"Collision sol"<<END_PRINT_COLOR;
			// Collision
			return true;
		}
	}

	return false;
}

bool PhysicsEngine::IsTooFarCollision(const osg::Vec3f& parObjectPos, const osg::Vec3f& parPlane)
{
	osg::Vec3f distance = parObjectPos - parPlane;
	//PRINT_ORANGE<<distance.length()<<END_PRINT_COLOR;
	if((distance.length())>TerrainConst::TailleBoite)
	{
		//PRINT_ORANGE<<"Collision boite"<<END_PRINT_COLOR;
		return true;
	}
	return false;
}
