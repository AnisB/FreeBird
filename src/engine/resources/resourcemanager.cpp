
// Header include
#include "resourcemanager.h"

// Osg includes
#include <osgDB/ReadFile>

//Include projet
#include <common/defines.h>



namespace CubeMapDir
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

std::string getFileName(std::string parFolder, CubeMapDir::Type parDir)
{
	std::string fullPath = parFolder;
	switch(parDir)
	{
		case CubeMapDir::POSITIVE_X:
			fullPath+="/xp.png";
		break;

		case CubeMapDir::POSITIVE_Y:
			fullPath+="/yp.png";
		break;

		case CubeMapDir::POSITIVE_Z:
			fullPath+="/zp.png";
		break;
		
		case CubeMapDir::NEGATIVE_X:
			fullPath+="/xn.png";
		break;
		
		case CubeMapDir::NEGATIVE_Y:
			fullPath+="/yn.png";
		break;
		
		case CubeMapDir::NEGATIVE_Z:
			fullPath+="/zn.png";
		break;
	};
	return fullPath;
}



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
		PRINT_ORANGE << MODEL_MANAGER << "Texture already loaded, getting  the texture from the database :) :" << parTextureName << END_PRINT_COLOR; 
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
		newTexture->setInternalFormat(GL_RGBA32F_ARB);
 	    FTextures[parTextureName] = newTexture;
 	    return newTexture;
	}
}

osg::TextureCubeMap* ResourceManager::LoadTextureCubeMap(std::string parFolder)
{
	PRINT_GREEN << MODEL_MANAGER << "Loading cubemap" << parFolder << END_PRINT_COLOR; 
	tryget(it, FCubeMaps, parFolder);
	if(it != FCubeMaps.end())
	{
		PRINT_ORANGE << MODEL_MANAGER << "CubeMap already loaded, getting cubeMap from  the database :) :" << parFolder << END_PRINT_COLOR; 
		return it->second;
	}
	else
	{
		osg::TextureCubeMap* cubemap = new osg::TextureCubeMap; 
		cubemap->setInternalFormat(GL_RGBA16F_ARB); 
		cubemap->setSourceType(GL_FLOAT); 
		cubemap->setSourceFormat(GL_RGBA); 

		osg::Image* imagePosX = osgDB::readImageFile(getFileName(parFolder,CubeMapDir::POSITIVE_X)); 
		osg::Image* imageNegX = osgDB::readImageFile(getFileName(parFolder,CubeMapDir::NEGATIVE_X)); 
		osg::Image* imagePosY = osgDB::readImageFile(getFileName(parFolder,CubeMapDir::POSITIVE_Y)); 
		osg::Image* imageNegY = osgDB::readImageFile(getFileName(parFolder,CubeMapDir::NEGATIVE_Y)); 
		osg::Image* imagePosZ = osgDB::readImageFile(getFileName(parFolder,CubeMapDir::POSITIVE_Z)); 
		osg::Image* imageNegZ = osgDB::readImageFile(getFileName(parFolder,CubeMapDir::NEGATIVE_Z)); 

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
		FCubeMaps[parFolder] = cubemap;
		return cubemap;
	}
}

osg::ref_ptr<osg::Node>  ResourceManager::LoadModel(const std::string& modelName)
{
	//PRINT_GREEN << MODEL_MANAGER << "Loading model" << modelName << END_PRINT_COLOR; 
	tryget(it, FModels, modelName);
	if(it != FModels.end())
	{
		//PRINT_ORANGE << MODEL_MANAGER << "Model already loaded, getting from the model database :) :" << modelName << END_PRINT_COLOR; 
		return it->second;
	}
	else
	{
		osg::Node* newModel = osgDB::readNodeFile(modelName);
		if(newModel)
		{
			FModels[modelName] = newModel;
			//PRINT_GREEN << MODEL_MANAGER<< "Model loaded: "<<modelName<<END_PRINT_COLOR;
			return newModel;
		}
		//PRINT_RED << MODEL_MANAGER<< "Failed to load that model: "<<modelName<<END_PRINT_COLOR;
		return NULL;
	}
}