#ifndef SCENE_OBJECT_FREE_BIRD
#define SCENE_OBJECT_FREE_BIRD


// Osg includes
#include <osg/Node>
#include <osg/Matrix>
#include <osg/MatrixTransform>
// Project includes
#include <common/singleton.h>
#include <rendering/defines.h>

// Base includes
#include <map>
#include <list>
#include <string>

class SceneObject
{
	public:		
		SceneObject(const std::string& parModelName);
		~SceneObject();	

	protected:
		SceneObject();
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

		virtual void AddChild(SceneObject * parNode);
		void SetParent(SceneObject * parNode);

		osg::MatrixTransform* GetNode() {return FModelTrans;};
    public:
		void InitObject();

	protected:
		bool FIsRoot;
		bool FIsValid;

	protected:
		std::string FModelName;
		osg::Node* FModel;
		osg::MatrixTransform* FModelTrans;

		SceneObject * FParentNode;
		std::list<SceneObject*> FSons;

};
#endif //SCENE_OBJECT_FREE_BIRD