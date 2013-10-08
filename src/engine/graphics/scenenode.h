#ifndef SCENE_NODE_FREE_BIRD
#define SCENE_NODE_FREE_BIRD


// Osg includes
#include <osg/Node>
#include <osg/Matrix>
#include <osg/MatrixTransform>
// Project includes
#include <common/singleton.h>
#include <graphics/defines.h>

// Base includes
#include <map>
#include <list>
#include <string>

class SceneNode
{
	public:		
		SceneNode();
		~SceneNode();	

	public:
		void Translate(const osg::Vec3f& parVec);
		void Rotate(float parAngle, const osg::Vec3f& parAxe);

		void Yaw(float parRadian, TransformationSpace::Type parTrans = TransformationSpace::TS_LOCAL);
		void Pitch(float parRadian, TransformationSpace::Type parTrans = TransformationSpace::TS_LOCAL);
		void Roll(float parRadian, TransformationSpace::Type parTrans = TransformationSpace::TS_LOCAL);

		osg::Vec3f GetPosition(TransformationSpace::Type parTrans = TransformationSpace::TS_LOCAL);
		osg::Matrix GetTransformation(TransformationSpace::Type parTrans = TransformationSpace::TS_LOCAL);

		osg::Matrix GetLocalTransformation();
		osg::Matrix GetParentRelativeTransformation();
		osg::Matrix GetAbsoluteTransformation();

		virtual void AddChild(SceneNode * parNode);
		void SetParent(SceneNode * parNode);

		osg::MatrixTransform* GetNode() {return FModelTrans;};
    public:
		void InitObject();

	protected:
		bool FIsRoot;
		bool FIsValid;

	protected:
		osg::MatrixTransform* FModelTrans;

		SceneNode * FParentNode;
		std::list<SceneNode*> FSons;

};
#endif //SCENE_NODE_FREE_BIRD
