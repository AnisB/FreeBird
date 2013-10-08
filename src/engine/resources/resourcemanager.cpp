
// Header include
#include "resourcemanager.h"

// Osg includes
#include <osgDB/ReadFile>

//Include projet
#include <common/defines.h>


ResourceManager::ResourceManager()
{
	
}

ResourceManager::~ResourceManager()
{
	
}

osg::Node * ResourceManager::LoadModel(const std::string& modelName)
{
	PRINT_GREEN << MODEL_MANAGER << "Loading model" << modelName << END_PRINT_COLOR; 
	tryget(it, FModels, modelName);
	if(it != FModels.end())
	{
		PRINT_BLUE << MODEL_MANAGER << "Model already loaded, getting from the model database :)" << modelName << END_PRINT_COLOR; 
		return it->second;
	}
	else
	{
		osg::Node * newModel = osgDB::readNodeFile(modelName);
		if(newModel)
		{
			FModels[modelName] = newModel;
			PRINT_GREEN << MODEL_MANAGER<< "Model loaded: "<<modelName<<END_PRINT_COLOR;
			return newModel;
		}
		PRINT_RED << MODEL_MANAGER<< "Failed to load that model: "<<modelName<<END_PRINT_COLOR;
		return NULL;
	}
}