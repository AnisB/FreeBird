#ifndef RESOURCE_MANAGER_FREE_BIRD
#define RESOURCE_MANAGER_FREE_BIRD


// Osg includes
#include <osg/Node>
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

		osg::Node * LoadModel(const std::string& modelName);

	protected:
		std::map<std::string, osg::Node*> FModels;

};
#endif //RESOURCE_MANAGER_FREE_BIRD