#ifndef RESOURCE_MANAGER_FREE_BIRD
#define RESOURCE_MANAGER_FREE_BIRD


// Osg includes
#include <osg/Node>
#include <osg/TextureCubeMap>
#include <osg/Texture2D>
// Project includes
#include <common/singleton.h>

// Base includes
#include <map>
#include <string>

class ResourceManager : public Singleton<ResourceManager>
{
	public:		
		ResourceManager();
		~ResourceManager();	

		osg::Node * LoadModel(const std::string& parModelName);

		osg::Texture2D* LoadTexture(const std::string& parTexture);
		osg::TextureCubeMap* LoadTextureCubeMap(std::string parFolder);
		

	protected:
		std::map<std::string, osg::Node*> FModels;
		std::map<std::string, osg::Texture2D*> FTextures;
		std::map<std::string, osg::TextureCubeMap*> FCubeMaps;

};
#endif //RESOURCE_MANAGER_FREE_BIRD