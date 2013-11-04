uniform sampler2D heightMap;
uniform sampler2D normalMap;
uniform sampler2D riverMap;
uniform sampler2D rockMap;
uniform sampler2D ground;
uniform sampler2D grass;


const float PI = 3.1415926535897932385;  // Pi

const float STEP = 0.001;
const float MAX_HEIGHT = 100.0;

varying vec3  transformedNormal;
varying vec4 ecPosition;

varying vec4 colorVal;

vec2 coordinates;


vec3 fnormal(in vec3 normal)
{
    //Compute the normal 
    vec3 normalTr = gl_NormalMatrix * normal;
    normalTr = normalize(normalTr);
    return normalTr;
}


void animation(inout vec4 position, inout vec3 normal)
{ 
    vec4 heightColor = texture2D(heightMap,coordinates.xy);
    // Déformation sur l'axe des X selon la position X
    float deltaPos = heightColor.r * MAX_HEIGHT;

    position += vec4(0.0, 1.0-deltaPos,0.0,0.0);
    normal = (texture2D(normalMap,coordinates.xy).xyz-0.5)*2.0;
}


void main (void)
{ 
    vec4 position = gl_Vertex;
    vec3 normal = gl_Normal;

    coordinates = vec2(gl_MultiTexCoord0.x ,gl_MultiTexCoord0.y);
    // Transformation du vertex selon le temps
    animation(position, normal);

    // Eye-coordinate position of vertex, needed in various calculations
    ecPosition = gl_ModelViewMatrix * position;
    transformedNormal = fnormal(normal);

    // Do fixed functionality vertex transform
    gl_Position = gl_ModelViewProjectionMatrix*position;
    gl_ClipVertex = gl_ModelViewMatrix * position;

    gl_TexCoord[0].xy = coordinates; 
}