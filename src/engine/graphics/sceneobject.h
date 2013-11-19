#ifndef SCENE_OBJECT_FREE_BIRD
#define SCENE_OBJECT_FREE_BIRD


// Osg includes
#include <osg/Node>
#include <osg/Matrix>
#include <osg/MatrixTransform>
// Project includes
#include <common/singleton.h>
#include <graphics/defines.h>
#include "scenenode.h"

// Base includes
#include <map>
#include <list>
#include <string>


class SceneObject : public SceneNode
{
	public:		
		SceneObject(const std::string& parModelName);
		virtual ~SceneObject();	
    public:
		void InitObject();

		osg::Node* GetModel() {return FModel.get();}

		void SetDynamic() 
		{
		    FModel->setDataVariance(osg::Object::DYNAMIC);
		}


	protected:
		std::string FModelName;
		osg::ref_ptr<osg::Node> FModel;

};
#endif //SCENE_OBJECT_FREE_BIRD
