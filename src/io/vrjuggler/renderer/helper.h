#ifndef MATRIX_HELPER
#define MATRIX_HELPER



osg::Matrix GmtlToOsg(const gmtl::Matrix44f& parMatrix);

osg::Matrix GmtlToOsg_TranslationOnly(const gmtl::Matrix44f& parMatrix);

osg::Matrix GmtlToOsg_RotationOnly(const gmtl::Matrix44f& parMatrix);

#endif // MATRIX_HELPER