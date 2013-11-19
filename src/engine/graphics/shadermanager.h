#ifndef SHADER_MANAGER_FREE_BIRD
#define SHADER_MANAGER_FREE_BIRD


#include <osg/Shader>
#include <osg/MatrixTransform>
#include <osg/Program>

#include <common/singleton.h>
#include <map>

class ShaderManager : public Singleton<ShaderManager>
{
public:
	ShaderManager();
	~ShaderManager();

public:
	int CreateShader(std::string parVertexShader, std::string parFragmentShader);
#ifdef TESS
	int CreateShaderTess(std::string parVertexShader, std::string parTSCShader, std::string parTSEShader, std::string parFragmentShader);
#endif
	void ActivateShader(osg::Node * Node, int parShaderRef);
	void DisableShader(osg::Node * Node, int parShaderRef);
	void InitUniform_Texture(std::string name, osg::Node * parGeode, int parTexID);
protected:
	std::map<int, osg::Program *> FShaders;
public:
	static int ShaderCounter;

};

void LoadBaseShader(osg::Node * parNode);
void BindTexture(osg::Node * parNode, const std::string& parVarName, const std::string& parImg, size_t parIndex);
void BindCubeMap(osg::Node * parNode, const std::string& parVarName, const std::string& parImg, size_t parIndex);
void InjectVec3(osg::Node * parNode, osg::Vec3f parPosition, const std::string& parVarName);
void InjectVec2(osg::Node * parNode, osg::Vec2f parPosition, const std::string& parVarName);
#endif //SHADER_MANAGER_FREE_BIRD
