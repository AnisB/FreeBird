#ifndef SKYBOX_FREE_BIRD
#define SKYBOX_FREE_BIRD


#include <string>
#include <graphics/root.h>

#include <osg/TextureCubeMap>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osg/ClearNode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>

class Root;

class Skybox
{
	public:
		Skybox();
		~Skybox();

		void createSkybox(std::string parFolderName,  SceneNode * parNode);	

	protected:
		osg::TextureCubeMap* LoadTextureCubeMap(std::string parFolder);
		osg::Geometry * GenerateBox();


	protected:
		int FShaderId;

};

#endif //SKYBOX_FREE_BIRD