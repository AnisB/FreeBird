// Include du header
#include "helper.h"

osg::Matrix GmtlToOsg(const gmtl::Matrix44f& parMatrix)
{
   	osg::Matrix osgMatrix( parMatrix(0,0), parMatrix(1,0), parMatrix(2,0), parMatrix(3,0),
                                parMatrix(0,1), parMatrix(1,1), parMatrix(2,1), parMatrix(3,1),
                                parMatrix(0,2), parMatrix(1,2), parMatrix(2,2), parMatrix(3,2),
                                parMatrix(0,3), parMatrix(1,3), parMatrix(2,3), parMatrix(3,3) );
   	return osgMatrix;
}

osg::Matrix GmtlToOsg_TranslationOnly(const gmtl::Matrix44f& parMatrix)
{
   	osg::Matrix osgMatrix( 0.0, 0.0, 0.0, 0.0,
                               0.0, 0.0, 0.0, 0.0,
                               0.0, 0.0, 0.0, 0.0,
                               parMatrix(0,3), parMatrix(1,3), parMatrix(2,3), parMatrix(3,3) );
   	return osgMatrix;
}


osg::Matrix GmtlToOsg_RotationOnly(const gmtl::Matrix44f& parMatrix)
{
   	osg::Matrix osgMatrix( parMatrix(0,0), parMatrix(1,0), parMatrix(2,0), parMatrix(3,0),
                                parMatrix(0,1), parMatrix(1,1), parMatrix(2,1), parMatrix(3,1),
                                parMatrix(0,2), parMatrix(1,2), parMatrix(2,2), parMatrix(3,2),
                               	0.0, 0.0, 0.0, 1.0);
   	return osgMatrix;
}
