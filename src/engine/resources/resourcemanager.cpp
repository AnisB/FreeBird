
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
osg::Texture2D *ResourceManager::LoadTexture(const std::string& parTextureName)
{
	PRINT_GREEN << MODEL_MANAGER << "Loading texture" << parTextureName << END_PRINT_COLOR; 
	tryget(it, FTextures, parTextureName);
	if(it != FTextures.end())
	{
		PRINT_ORANGE << MODEL_MANAGER << "Model already loaded, getting from the texture database :) :" << parTextureName << END_PRINT_COLOR; 
		return it->second;
	}
	else
	{
		osg::Texture2D* newTexture = new osg::Texture2D;

		newTexture->setDataVariance(osg::Object::DYNAMIC); 

		osg::Image* image = osgDB::readImageFile(parTextureName);
	    if (!image)
	    {
			PRINT_RED << MODEL_MANAGER<< "Failed to load that texture: "<<parTextureName<<END_PRINT_COLOR;
	        
			return NULL;
		}
		PRINT_GREEN << MODEL_MANAGER<< "Texture loaded: "<<parTextureName<<END_PRINT_COLOR;
 	    newTexture->setImage(image);
 	    newTexture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
 	    newTexture->setWrap(osg::Texture2D::WRAP_S,osg::Texture2D::REPEAT); 
		newTexture->setWrap(osg::Texture2D::WRAP_T,osg::Texture2D::REPEAT); 
 	    FTextures[parTextureName] = newTexture;
 	    return newTexture;
	}
}

osg::Node * ResourceManager::LoadModel(const std::string& modelName)
{
	PRINT_GREEN << MODEL_MANAGER << "Loading model" << modelName << END_PRINT_COLOR; 
	tryget(it, FModels, modelName);
	if(it != FModels.end())
	{
		PRINT_ORANGE << MODEL_MANAGER << "Model already loaded, getting from the model database :) :" << modelName << END_PRINT_COLOR; 
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