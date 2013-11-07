

uniform vec2 planePosition;

uniform float osg_FrameTime;


const float PI = 3.1415926535897932385;  // Pi

const float STEP = 0.001;
const float MAX_HEIGHT = 90.0;
const float WATER_LEVEL = 1.0;
const float WATER_STEPX = 0.0;
const float WATER_STEPY = 10.0;
const float WATER_HEIGHT = WATER_LEVEL*MAX_HEIGHT;
const float WAVE_LENGTH = 5.0;


varying vec3  transformedNormal;
varying vec4 ecPosition;


vec2 coordinates;



vec3 fnormal(in vec3 normal)
{
    //Compute the normal 
    vec3 normalTr = gl_NormalMatrix * normal;
    normalTr = normalize(normalTr);
    return normalTr;
}

void main (void)
{ 
    vec4 position = gl_Vertex;
    vec3 normal = gl_Normal;
    coordinates = gl_MultiTexCoord0.xy;
    //coordinates = vec2(gl_MultiTexCoord0.x + planePosition.x,gl_MultiTexCoord0.y+planePosition.y);
    coordinates = clamp(coordinates, 0.0, 1.0);

    // Eye-coordinate position of vertex, needed in various calculations
    ecPosition = gl_ModelViewMatrix * position;
    transformedNormal = fnormal(normal);

    // Do fixed functionality vertex transform
    gl_Position = gl_ModelViewProjectionMatrix*position;
    gl_ClipVertex = gl_ModelViewMatrix * position;

    gl_TexCoord[0].xy = coordinates; 
}
