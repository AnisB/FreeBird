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
	int CreateShaderTess(std::string parVertexShader, std::string parTSCShader, std::string parTSEShader, std::string parFragmentShader);

	void ActivateShader(osg::Node * Node, int parShaderRef);
	void DisableShader(osg::Node * Node, int parShaderRef);

	void InitUniform_Texture(std::string name, osg::Node * parGeode, int parTexID);



protected:
	std::map<int, osg::Program *> FShaders;
public:
	static int ShaderCounter;

};

#endif //SHADER_MANAGER_FREE_BIRD