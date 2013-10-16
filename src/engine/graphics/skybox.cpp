#include "skybox.h"


#include "shadermanager.h"
 

#define SKYBOXSIZE 10000

namespace SkyboxDir
{
	enum Type
	{
		POSITIVE_X,
		POSITIVE_Y,
		POSITIVE_Z,
		NEGATIVE_X,
		NEGATIVE_Y,
		NEGATIVE_Z
	};
}

std::string getFileName(std::string parFolder, SkyboxDir::Type parDir)
{
	std::string fullPath = parFolder;
	switch(parDir)
	{
		case SkyboxDir::POSITIVE_X:
			fullPath+="/xp.png";
		break;

		case SkyboxDir::POSITIVE_Y:
			fullPath+="/yp.png";
		break;

		case SkyboxDir::POSITIVE_Z:
			fullPath+="/zp.png";
		break;
		
		case SkyboxDir::NEGATIVE_X:
			fullPath+="/xn.png";
		break;
		
		case SkyboxDir::NEGATIVE_Y:
			fullPath+="/yn.png";
		break;
		
		case SkyboxDir::NEGATIVE_Z:
			fullPath+="/zn.png";
		break;
	};
	return fullPath;
}

Skybox::Skybox()
: FShaderId(-1)
{

}

Skybox::~Skybox()
{

}

osg::Geometry * Skybox::GenerateBox()
{
	osg::Vec3Array *vertexArray = new osg::Vec3Array();
	vertexArray->push_back(osg::Vec3f(-SKYBOXSIZE, SKYBOXSIZE,-SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f(-SKYBOXSIZE, SKYBOXSIZE,SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f(SKYBOXSIZE, SKYBOXSIZE,SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f(SKYBOXSIZE, SKYBOXSIZE,-SKYBOXSIZE));


	vertexArray->push_back(osg::Vec3f(SKYBOXSIZE, -SKYBOXSIZE,-SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f(SKYBOXSIZE, -SKYBOXSIZE,SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f(-SKYBOXSIZE,-SKYBOXSIZE,SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f(-SKYBOXSIZE, -SKYBOXSIZE,-SKYBOXSIZE));


	// FACE DE DROITE (X POS)
	vertexArray->push_back(osg::Vec3f(SKYBOXSIZE,-SKYBOXSIZE,-SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f(SKYBOXSIZE,-SKYBOXSIZE, SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f(SKYBOXSIZE, SKYBOXSIZE,-SKYBOXSIZE));

	// FACE DE GAUCHE (X NEG)
	vertexArray->push_back(osg::Vec3f(-SKYBOXSIZE,-SKYBOXSIZE,-SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f(-SKYBOXSIZE,-SKYBOXSIZE, SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f(-SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f(-SKYBOXSIZE, SKYBOXSIZE,-SKYBOXSIZE));


	// FACE DU HAUT (Z POS)
	vertexArray->push_back(osg::Vec3f(-SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f(-SKYBOXSIZE,-SKYBOXSIZE, SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f( SKYBOXSIZE,-SKYBOXSIZE, SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f( SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE));        

	// FACE DU BAS (Z NEG)
	vertexArray->push_back(osg::Vec3f(-SKYBOXSIZE,-SKYBOXSIZE,-SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f(-SKYBOXSIZE, SKYBOXSIZE,-SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f( SKYBOXSIZE, SKYBOXSIZE,-SKYBOXSIZE));
	vertexArray->push_back(osg::Vec3f( SKYBOXSIZE,-SKYBOXSIZE,-SKYBOXSIZE));  


	// face array
	osg::DrawElementsUInt *faceArray = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	 
	// bottom
	faceArray->push_back(0); // face 1
	faceArray->push_back(1);
	faceArray->push_back(2);
	faceArray->push_back(3);

	
	faceArray->push_back(4);  //face 3
	faceArray->push_back(5);
	faceArray->push_back(6);
	faceArray->push_back(7);

	// left
	faceArray->push_back(8);  //face 5
	faceArray->push_back(9);
	faceArray->push_back(10);
	faceArray->push_back(11);

	// right
	faceArray->push_back(12);  //face 7
	faceArray->push_back(13);
	faceArray->push_back(14);
	faceArray->push_back(15);

	// front
	faceArray->push_back(16);  //face 9
	faceArray->push_back(17);
	faceArray->push_back(18);
	faceArray->push_back(19);

	// back
	faceArray->push_back(20);  //face 11
	faceArray->push_back(21);
	faceArray->push_back(22);
	faceArray->push_back(23);
	
	// normal array
	osg::Vec3Array *normalArray = new osg::Vec3Array();
	normalArray->push_back(osg::Vec3f(0, -1, 0));
	normalArray->push_back(osg::Vec3f(0, 1, 0));
	normalArray->push_back(osg::Vec3f(-1, 0, 0));
	normalArray->push_back(osg::Vec3f(1, 0, 0));
	normalArray->push_back(osg::Vec3f(0, 0, 1));
	normalArray->push_back(osg::Vec3f(0, 0, -1));

	osg::Geometry *geometry = new osg::Geometry();
	geometry->setVertexArray(vertexArray);
	geometry->setNormalArray(normalArray);
	geometry->addPrimitiveSet(faceArray);

	return geometry;

}
void Skybox::createSkybox(std::string parFolderName, SceneNode * parNode)
{
     osg::TextureCubeMap* skymap = LoadTextureCubeMap(parFolderName);
 
 
    osg::Geometry* box = GenerateBox();
 
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable(box);
    FShaderId = ShaderManager::Instance().CreateShader("data/shaders/skyBoxVertex.glsl","data/shaders/skyBoxFragments.glsl");

	osg::StateSet* brickState = geode->getOrCreateStateSet();
    brickState->setTextureAttributeAndModes(0, skymap, osg::StateAttribute::ON);
    ShaderManager::Instance().ActivateShader(geode, FShaderId);
 
    parNode->GetNode()->addChild(geode);
 
}


osg::TextureCubeMap* Skybox::LoadTextureCubeMap(std::string parFolder)
{
	osg::TextureCubeMap* cubemap = new osg::TextureCubeMap; 
	cubemap->setInternalFormat(GL_RGBA16F_ARB); 
	cubemap->setSourceType(GL_FLOAT); 
	cubemap->setSourceFormat(GL_RGBA); 

	osg::Image* imagePosX = osgDB::readImageFile(getFileName(parFolder,SkyboxDir::POSITIVE_X)); 
	osg::Image* imageNegX = osgDB::readImageFile(getFileName(parFolder,SkyboxDir::NEGATIVE_X)); 
	osg::Image* imagePosY = osgDB::readImageFile(getFileName(parFolder,SkyboxDir::POSITIVE_Y)); 
	osg::Image* imageNegY = osgDB::readImageFile(getFileName(parFolder,SkyboxDir::NEGATIVE_Y)); 
	osg::Image* imagePosZ = osgDB::readImageFile(getFileName(parFolder,SkyboxDir::POSITIVE_Z)); 
	osg::Image* imageNegZ = osgDB::readImageFile(getFileName(parFolder,SkyboxDir::NEGATIVE_Z)); 

	if (imagePosX && imageNegX && imagePosY && imageNegY && imagePosZ && imageNegZ) 
	{ 
		cubemap->setImage(osg::TextureCubeMap::POSITIVE_X, imagePosX); 
		cubemap->setImage(osg::TextureCubeMap::NEGATIVE_X, imageNegX); 
		cubemap->setImage(osg::TextureCubeMap::POSITIVE_Y, imagePosY); 
		cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Y, imageNegY); 
		cubemap->setImage(osg::TextureCubeMap::POSITIVE_Z, imagePosZ); 
		cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Z, imageNegZ); 

		cubemap->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE); 
		cubemap->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE); 
		cubemap->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE); 

		cubemap->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR); 
		cubemap->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR); 
	} 
	return cubemap;
}
