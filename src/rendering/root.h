#ifndef ROOT_FREE_BIRD
#define ROOT_FREE_BIRD

#include "sceneobject.h"


class Root : public SceneObject
{
	public:		
		Root();
		~Root();

		void InitRoot();

		osg::Group* GetRoot(){ return FRoot;}

		void AddModel(SceneObject * parNode);
		void AddLight();


	protected:
		osg::Group*   FRoot;
		osg::Group*	  mModelGroup;
		osg::Group*	  mLightGroup;
};
#endif //ROOT_FREE_BIRD