#ifndef CAMERA_MAN_FREE_BIRD
#define CAMERA_MAN_FREE_BIRD

// OSG Includes
#include <osg/Camera>
#include "scenenode.h"

class CameraMan : public SceneNode
{
public:
	CameraMan();
	~CameraMan();


	virtual void Translate(const osg::Vec3f& parVec);
	virtual void Rotate(float parAngle, const osg::Vec3f& parAxe);

	virtual void Yaw(float parRadian, TransformationSpace::Type parTrans = TransformationSpace::TS_LOCAL);
	virtual void Pitch(float parRadian, TransformationSpace::Type parTrans = TransformationSpace::TS_LOCAL);
	virtual void Roll(float parRadian, TransformationSpace::Type parTrans = TransformationSpace::TS_LOCAL);

	void SetCamera(osg::Camera * parCamera);
	void SetNode(SceneNode* parNode);

	void Update();

protected:
	osg::Camera * FCamera;

	bool FIsValid;


};
#endif //CAMERA_MAN_FREE_BIRD