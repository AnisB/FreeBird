#include "helper.h"

osg::Matrix GmtlToOsg(const gmtl::Matrix44f& parMatrix)
{
	   	osg::Matrix osgMatrix( wandMatrix_Trh(0,0), wandMatrix_Trh(1,0), wandMatrix_Trh(2,0), wandMatrix_Trh(3,0),
                                        wandMatrix_Trh(0,1), wandMatrix_Trh(1,1), wandMatrix_Trh(2,1), wandMatrix_Trh(3,1),
                                        wandMatrix_Trh(0,2), wandMatrix_Trh(1,2), wandMatrix_Trh(2,2), wandMatrix_Trh(3,2),
                                        wandMatrix_Trh(0,3), wandMatrix_Trh(1,3), wandMatrix_Trh(2,3), wandMatrix_Trh(3,3) );
	   	return osgMatrix;
}

osg::Matrix GmtlToOsg_TranslationOnly(const gmtl::Matrix44f& parMatrix)
{
	   	osg::Matrix osgMatrix( 0.0, 0.0, 0.0, 0.0,
                               0.0, 0.0, 0.0, 0.0,
                               0.0, 0.0, 0.0, 0.0,
                               wandMatrix_Trh(0,3), wandMatrix_Trh(1,3), wandMatrix_Trh(2,3), wandMatrix_Trh(3,3) );
	   	return osgMatrix;
}


osg::Matrix GmtlToOsg_RotationOnly(const gmtl::Matrix44f& parMatrix)
{
	   	osg::Matrix osgMatrix( wandMatrix_Trh(0,0), wandMatrix_Trh(1,0), wandMatrix_Trh(2,0), wandMatrix_Trh(3,0),
                                wandMatrix_Trh(0,1), wandMatrix_Trh(1,1), wandMatrix_Trh(2,1), wandMatrix_Trh(3,1),
                                wandMatrix_Trh(0,2), wandMatrix_Trh(1,2), wandMatrix_Trh(2,2), wandMatrix_Trh(3,2),
                               	0.0, 0.0, 0.0, 0.0);
	   	return osgMatrix;
}