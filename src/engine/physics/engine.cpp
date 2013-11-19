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
	if(position.x()>0.5 || position.y()>0.5 || position.x()<-0.5 || position.y()<-0.5)
	{
		// on est en decors de la map de base, il suffit de tester la hauteur
		if( planePosition.y()>TerrainConst::WaterHeight)
		{
			return true;
		}
	}  
	else
	{
		// On convertit en coordonnées texture opengl
		float sCoord = (position.x()+0.5)*2048;
		float tCoord = (position.y()+0.5)*2048;
		// On récupère la hauteur
		double height = FTerrainHeight->getColor(sCoord,tCoord).r();
		// On convertit la hauteur en coordonnées réelle
		height *=1000.0; 
		height = 1200-height;
		// Sommes nous en dessous du terrain?
		if((height) < planePosition.y())
		{
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
	if((distance.length())>5000)
	{
		PRINT_ORANGE<<"Collision"<<END_PRINT_COLOR;
		return true;
	}
	return false;
}