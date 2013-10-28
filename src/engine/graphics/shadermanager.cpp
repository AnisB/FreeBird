
#include "shadermanager.h"

#include <resources/resourcemanager.h>
#include <osgDB/ReadFile>
#include <osg/Texture2D>

int ShaderManager::ShaderCounter = 0;

ShaderManager::ShaderManager()
{

}
ShaderManager::~ShaderManager()
{

}

void ShaderManager::InitUniform_Texture(std::string name, osg::Node * parGeode, int parTexID)
{
	osg::StateSet* stateset = parGeode->getOrCreateStateSet();
	osg::Uniform* originUniform = new osg::Uniform(name.c_str(),parTexID);
	stateset->addUniform(originUniform);
} 
void ShaderManager::ActivateShader(osg::Node * Node, int parShaderRef)
{
	osg::StateSet* brickState = Node->getOrCreateStateSet();
	brickState->setAttributeAndModes(FShaders[parShaderRef], osg::StateAttribute::ON);
}
void ShaderManager::DisableShader(osg::Node * Node, int parShaderRef)
{
	osg::StateSet* brickState = Node->getOrCreateStateSet();
	brickState->setAttributeAndModes(FShaders[parShaderRef], osg::StateAttribute::OFF);
}

int ShaderManager::CreateShader(std::string parVertexShader, std::string parFragmentShader)
{
	osg::Program* program = new osg::Program;
    osg::Shader* vertexObject =  new osg::Shader( osg::Shader::VERTEX );
    osg::Shader* fragmentObject = new osg::Shader( osg::Shader::FRAGMENT );
    program->addShader( vertexObject );
    program->addShader( fragmentObject );
    vertexObject->loadShaderSourceFromFile(parVertexShader );
    fragmentObject->loadShaderSourceFromFile(parFragmentShader);

    FShaders[ShaderCounter] = program;
	ShaderCounter++;
    return (ShaderCounter-1);
}
#ifdef TESS
int ShaderManager::CreateShaderTess(std::string parVertexShader, std::string parTSCShader, std::string parTSEShader, std::string parFragmentShader)
{
    osg::Program* program = new osg::Program;
    osg::Shader* vertexObject =  new osg::Shader( osg::Shader::VERTEX );
    osg::Shader* fragmentObject = new osg::Shader( osg::Shader::FRAGMENT );
    osg::Shader* tessControlObject = new osg::Shader( osg::Shader::TESSCONTROL );
    osg::Shader* tessEvalObject = new osg::Shader( osg::Shader::TESSEVALUATION );
    program->addShader( vertexObject );
    program->addShader( fragmentObject );
    program->addShader( tessControlObject );
    program->addShader( tessEvalObject );
    vertexObject->loadShaderSourceFromFile(parVertexShader );
    fragmentObject->loadShaderSourceFromFile(parFragmentShader);
    tessControlObject->loadShaderSourceFromFile(parTSCShader);
    tessEvalObject->loadShaderSourceFromFile(parTSEShader);

    FShaders[ShaderCounter] = program;
	ShaderCounter++;
    return (ShaderCounter-1);
}
#endif

void BindTexture(osg::Node * parNode, const std::string& parVarName, const std::string& parImg, size_t parIndex)
{
    osg::StateSet* brickState = parNode->getOrCreateStateSet();
    osg::Texture2D * texture = ResourceManager::Instance().LoadTexture(parImg);
    ShaderManager::Instance().InitUniform_Texture(parVarName,parNode, parIndex);
    brickState->setTextureAttributeAndModes(parIndex, texture, osg::StateAttribute::ON);
}