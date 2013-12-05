#include "sceneobject.h"


#include <resources/resourcemanager.h>
#include <common/defines.h>



SceneObject::SceneObject(const std::string& parModelName)
: SceneNode()
{
	FModelName = parModelName;
}

SceneObject::~SceneObject()
{
}

void SceneObject::InitObject()
{
	FModel = ResourceManager::Instance().LoadModel(FModelName);
	if(FModel != NULL)
	{
		FIsValid = true;
		FModelTrans = new osg::MatrixTransform();
		FModelTrans->addChild(FModel.get());
	}
	else
	{
		PRINT_RED<<"Erreur de chargement de modèle, crash imminent"<<END_PRINT_COLOR;
	}
}
