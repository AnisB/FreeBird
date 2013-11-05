#include "skybox.h"


#include "shadermanager.h"
 

#define SKYBOXSIZE 7000

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
     osg::TextureCubeMap* skymap = ResourceManager::Instance().LoadTextureCubeMap(parFolderName);
 
 
    osg::Geometry* box = GenerateBox();
 
    osg::Geode * node = new osg::Geode();
    node->addDrawable(box);
    FShaderId = ShaderManager::Instance().CreateShader("data/shaders/skyBoxVertex.glsl","data/shaders/skyBoxFragments.glsl");

    osg::StateSet* brickState = node->getOrCreateStateSet();
    brickState->setTextureAttributeAndModes(0, skymap, osg::StateAttribute::ON);
    ShaderManager::Instance().ActivateShader(node, FShaderId);
    //FNode = new SceneNode();
    //FNode->GetNode()->addChild(node);
    parNode->GetNode()->addChild(node);
 
}
