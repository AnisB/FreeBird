#ifndef DEFINES_RENDER
#define DEFINES_RENDER



#ifndef GL_TESS_CONTROL_SHADER
    #define GL_TESS_CONTROL_SHADER 0x00008e88
#endif
#ifndef GL_TESS_EVALUATION_SHADER
    #define GL_TESS_EVALUATION_SHADER 0x00008e87
#endif
#ifndef GL_PATCHES
    #define GL_PATCHES 0x0000000e
#endif


namespace TransformationSpace
{
	enum Type
	{
		TS_LOCAL,
		TS_PARENT,
		TS_WORLD
	};
}

#endif // DEFINES_RENDER