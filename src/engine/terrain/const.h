#ifndef CONST_TERRAIN
#define CONST_TERRAIN



//Modeles 
#define TERRAIN_MODEL "data/terrain/base/terrain.obj"
#define WATER_MODEL "data/terrain/base/water.obj"
#define PORTE_AVION "data/porteavion/porteavion.3ds"
#define PALMIER "data/models/tree/palmier/palmier.obj"
#define HOUSE "data/models/house/house.3ds"



namespace TerrainConst
{
#ifdef VRJUGGLER
	const double WorldScale = 1.0;
	const double TerrainSize = 1000.0;
	const double WaterHeight = 101.0;
	const double PorteAvionX = 600.0;
	const double PorteAvionZ = 0.0;
#else
	const double WorldScale = 10.0;
	const double TerrainSize = 10000.0;
	const double WaterHeight = 1200;
	const double PorteAvionX = 6000.0;
	const double PorteAvionZ = 0.0;
#endif
}


#endif