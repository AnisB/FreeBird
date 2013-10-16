#ifndef RESOURCE_MANAGER_FREE_BIRD
#define RESOURCE_MANAGER_FREE_BIRD


// Osg includes
#include <osg/Node>
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

	protected:
		std::map<std::string, osg::Node*> FModels;
		std::map<std::string, osg::Texture2D*> FTextures;

};
#endif //RESOURCE_MANAGER_FREE_BIRD