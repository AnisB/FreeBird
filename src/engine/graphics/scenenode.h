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

namespace NodeType
{
	enum Type
	{
		NORMAL,
		ROOT
	};
}


class SceneNode
{
	public:		
		SceneNode(NodeType::Type parType = NodeType::NORMAL);
		~SceneNode();	

	public:
		virtual void Translate(const osg::Vec3f& parVec);
		virtual void Rotate(float parAngle, const osg::Vec3f& parAxe);

		virtual void Yaw(float parRadian, TransformationSpace::Type parTrans = TransformationSpace::TS_LOCAL);
		virtual void Pitch(float parRadian, TransformationSpace::Type parTrans = TransformationSpace::TS_LOCAL);
		virtual void Roll(float parRadian, TransformationSpace::Type parTrans = TransformationSpace::TS_LOCAL);

		virtual osg::Vec3f GetPosition(TransformationSpace::Type parTrans = TransformationSpace::TS_LOCAL);
		virtual osg::Matrix GetTransformation(TransformationSpace::Type parTrans = TransformationSpace::TS_LOCAL);

		virtual osg::Matrix GetLocalTransformation();
		virtual osg::Matrix GetParentRelativeTransformation();
		virtual osg::Matrix GetAbsoluteTransformation();

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