// Include header
#include "engine.h"

// Include projet
#include <terrain/helper.h>
#include <terrain/const.h>
#include <common/defines.h>

// Constantes utiles
#define MASS_VOL 1.2
#define SURFACE 15


// Helpers utiles
inline float clamp(float x, float a, float b)
{
    return x < a ? a : (x > b ? b : x);
}

inline float CoefPortance(float parAngle)
{
	return 0.1*parAngle+0.5;
}

PhysicsEngine::PhysicsEngine()
: FDetruit (0)
{
	FTerrainHeight = ResourceManager::Instance().LoadTexture("data/terrain/base/heightmap.png")->getImage();
}
PhysicsEngine::~PhysicsEngine()
{
	
}

Intersect PhysicsEngine::IsLandCollision(const osg::Vec3f& planePosition)
{
	Intersect intersection;
	intersection.isValid = false;
	// On convertit la position de l'avion en coordonnées texture centralisée
	osg::Vec2f position = ComputeRelativePosition(planePosition);

	// On est au delas des limites du terrain c-a-d dans l'eau
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
			intersection.isValid = true;
			intersection.position = osg::Vec3f(planePosition.x(),TerrainConst::WaterHeight,planePosition.z());
			return intersection;
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
		height = height-TerrainConst::WaterHeight;
		#endif

		
		double compareTo = planePosition.y();
		// Sommes nous en dessous du terrain?
		#ifdef VRJUGGLER
		if((height) > compareTo)
		#else
		if((height) < compareTo)
		#endif
		{
			// Collision sol
			intersection.isValid = true;
			intersection.position = osg::Vec3f(planePosition.x(),height,planePosition.z());
			return intersection;
		}
	}

	return intersection;
}

Intersect PhysicsEngine::IsTooFarCollision(const osg::Vec3f& parObjectPos, const osg::Vec3f& parPlane)
{
	osg::Vec3f distance = parObjectPos - parPlane;
	Intersect intersection;
	intersection.isValid = false;
	if((distance.length())>TerrainConst::TailleBoite)
	{
		//PRINT_ORANGE<<"Collision boite"<<END_PRINT_COLOR;
		intersection.isValid = true;
	}
	return intersection;
}

bool PhysicsEngine::Degats(int parCible, float parVal)
{
	bool retVal = FHouses[parCible]->Degats(parVal);
	if(retVal)
		FDetruit++;
	return retVal;
}

void PhysicsEngine::AddHouse(House* parHouse)
{
	FHouses.push_back(parHouse);
}

int PhysicsEngine::IsHouseCollision(const osg::Vec3f& planePosition)
{
	int counter = 0;
	foreach(house,FHouses)
	{
		if((*house)->IsIntersect(planePosition))
		{
			return counter;
		}
		counter++;
	}
	return -1;
}

void PhysicsEngine::DestroyHouse(int parHouse)
{
	FHouses[parHouse]->Destroy();
}

// Equation physique de l'avion, non utilisée pour l'instant
osg::Vec3f PhysicsEngine::ComputeNewSpeed(const osg::Vec3f& parCurrentPlaneSpeed, const osg::Matrix& parTransform, const osg::Quat& parQuat, double parDelta)
{
	osg::Vec3f finalSpeed = parCurrentPlaneSpeed;
	// Conversion du quaternion en angles
	float q0,q1,q2,q3;
	q0 = parQuat.x();
	q1 = parQuat.y();
	q2 = parQuat.z();
	q3 = parQuat.w();
	double teta = atan(2*(q0*q1+q2*q3)/(1-2*q1*q1+q2*q2))-5;
	double gho = asin(2*(q0*q2-q3*q1));
	double phi = atan(2*(q0*q3+q1*q2)/(1-2*q3*q3+q2*q2)) - 5;
	
	teta*=180/3.14; 
	PRINT_ORANGE<<"Les trois angles sont: "<<teta<<" "<<gho<<" "<<phi<<END_PRINT_COLOR;
	// Limitation des angles dans l'intervalle de la portance
	teta = clamp(teta,-5,25*180/3.14);
	gho = clamp(gho,-5,25);
	phi = clamp(phi,-5,25);	
	PRINT_ORANGE<<"Les angles clampés sont: "<<teta<<" "<<gho<<" "<<phi<<END_PRINT_COLOR;
	osg::Vec3f poids(0.0,5,0.0);
	poids = poids*parTransform;
	osg::Vec3f acceleration = poids;
	PRINT_ORANGE<<"Le vecteur poids est: "<<VEC3_TO_STREAM(acceleration)<<END_PRINT_COLOR;
	//acceleration.x() += ( MASS_VOL*parCurrentPlaneSpeed.length2()*SURFACE*CoefPortance(teta)/2.0)*0.1;
	acceleration.y() -= ( MASS_VOL*parCurrentPlaneSpeed.length2()*SURFACE*CoefPortance(teta)/2.0)*0.1;
	//acceleration.z() += ( MASS_VOL*parCurrentPlaneSpeed.length2()*SURFACE*CoefPortance(phi)/2.0)*0.1;
	acceleration*=0.1;
	PRINT_ORANGE<<"Le vecteur acceleration est: "<<VEC3_TO_STREAM(acceleration)<<END_PRINT_COLOR;
	finalSpeed += acceleration*parDelta*0.5;

	return finalSpeed;
}
