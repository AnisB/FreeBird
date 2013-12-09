#ifndef SKYBOX_FREE_BIRD
#define SKYBOX_FREE_BIRD


#include <string>
#include <graphics/root.h>
#include <resources/resourcemanager.h>

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

		void createSkybox(std::string parFolderName,  SceneNode * parNode, Root* parRoot);	
		SceneNode* GetNode(){return FNode;};
		void Update();
		void SetRotation(const osg::Matrix& parRot);
	protected:
		osg::Geometry * GenerateBox();
		


	protected:
		SceneNode* FNode;
		int FShaderId;
		
		SceneNode* FFollowedNode;

};

#endif //SKYBOX_FREE_BIRD
