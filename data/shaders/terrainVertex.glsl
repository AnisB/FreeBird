uniform sampler2D heightMap;
uniform sampler2D riverMap;
uniform sampler2D rockMap;
uniform sampler2D ground;
uniform sampler2D grass;
uniform sampler2D foam;


uniform float osg_FrameTime;


const float PI = 3.1415926535897932385;  // Pi

const float STEP = 0.001;
const float MAX_HEIGHT = 100.0;
const float WATER_LEVEL = 0.65;
const float WATER_STEPX = 10.0;
const float WATER_STEPY = 10.0;
const float WATER_HEIGHT = WATER_LEVEL*MAX_HEIGHT;
const float WAVE_LENGTH = 2.0;
varying vec3  transformedNormal;
varying vec4 ecPosition;

varying float isWater;



vec3 fnormal(in vec3 normal)
{
    //Compute the normal 
    vec3 normalTr = gl_NormalMatrix * normal;
    normalTr = normalize(normalTr);
    return normalTr;
}


void animation(inout vec4 position, inout vec3 normal)
{ 
  float deltaPos,deltaPosPX,deltaPosNX,deltaPosPY,deltaPosNY;    // Variation de la hauteur du vertex

  vec4 heightColor = texture2D(heightMap,gl_MultiTexCoord0.xy);
  isWater = 0.0;

  vec4 heightColorPX = texture2D(heightMap,gl_MultiTexCoord0.xy+vec2(STEP,0));
  vec4 heightColorNX = texture2D(heightMap,gl_MultiTexCoord0.xy+vec2(-STEP,0));
  vec4 heightColorPY = texture2D(heightMap,gl_MultiTexCoord0.xy+vec2(0,STEP));
  vec4 heightColorNY = texture2D(heightMap,gl_MultiTexCoord0.xy+vec2(0,-STEP));



  // Déformation sur l'axe des X selon la position X

  deltaPos = heightColor.r * MAX_HEIGHT;
  deltaPosPX = heightColorPX.r * MAX_HEIGHT;
  deltaPosNX = heightColorNX.r * MAX_HEIGHT;
  deltaPosPY = heightColorPY.r * MAX_HEIGHT;
  deltaPosNY = heightColorNY.r * MAX_HEIGHT;

  vec3 positionPX ;
  vec3 positionNX ;
  vec3 positionPY ;
  vec3 positionNY;
  if(heightColor.r >= WATER_LEVEL)
  {
    float currentTime = mod(osg_FrameTime,2.0*PI);
    const float waterStepRadX = WATER_STEPX*2.0*PI;
    const float waterStepRadY = WATER_STEPY*2.0*PI;

    deltaPos = WATER_HEIGHT + WAVE_LENGTH*cos( currentTime + gl_MultiTexCoord0.y*waterStepRadY + gl_MultiTexCoord0.x*waterStepRadX);

    deltaPosPX = WATER_HEIGHT + WAVE_LENGTH*cos( currentTime + gl_MultiTexCoord0.y*waterStepRadY + (gl_MultiTexCoord0.x+STEP)*waterStepRadX);
    deltaPosNX = WATER_HEIGHT + WAVE_LENGTH*cos( currentTime + gl_MultiTexCoord0.y*waterStepRadY + (gl_MultiTexCoord0.x-STEP)*waterStepRadX);
    deltaPosPY = WATER_HEIGHT + WAVE_LENGTH*cos( currentTime + (gl_MultiTexCoord0.y+STEP)*waterStepRadY + gl_MultiTexCoord0.x*waterStepRadX);
    deltaPosNY = WATER_HEIGHT + WAVE_LENGTH*cos( currentTime + (gl_MultiTexCoord0.y-STEP) *waterStepRadY + gl_MultiTexCoord0.x*waterStepRadX);
    isWater = 1.0;
    positionPX = gl_Vertex.xyz+ + vec3(1, 0.0,-deltaPosPX);
    positionNX = gl_Vertex.xyz + vec3(-1, 0.0,-deltaPosNX);
    positionPY = gl_Vertex.xyz + vec3(0.0, 1,-deltaPosPY);
    positionNY = gl_Vertex.xyz + vec3(0.0, -1,-deltaPosNY);
  }
  else
  {
    positionPX = gl_Vertex.xyz+ + vec3(1, 0.0,-deltaPosPX);
    positionNX = gl_Vertex.xyz + vec3(-1, 0.0,-deltaPosNX);
    positionPY = gl_Vertex.xyz + vec3(0.0, 1,-deltaPosPY);
    positionNY = gl_Vertex.xyz + vec3(0.0, -1,-deltaPosNY);
  }

  position += vec4(0.0, 0.0,-deltaPos,0.0);

  vec3 vecPX = normalize(position.xyz-positionPX);
  vec3 vecNX = normalize(position.xyz-positionNX);
  vec3 vecPY = normalize(position.xyz-positionPY);
  vec3 vecNY = normalize(position.xyz-positionNY);

  vec3 tgPX = cross(vecPX, vec3(0.0,0.0,1.0));
  vec3 tgNX = cross(vecNX,  vec3(0.0,0.0,1.0));
  vec3 tgPY = cross(vecPY,  vec3(0.0,0.0,1.0));
  vec3 tgNY = cross(vecNY,  vec3(0.0,0.0,1.0));


  vec3 normalPX = cross(tgPX, vecPX);
  vec3 normalNX = cross(tgNX, vecNX);
  vec3 normalPY = cross(tgPY, vecPY);
  vec3 normalNY = cross(tgNY, vecNY);

  normal = (normalPX+normalNX+normalPY+normalNY)/4.0;
  normal = -normalize(normal);
}


void main (void)
{
    vec4 position = gl_Vertex;
    vec3 normal = gl_Normal;

    // Transformation du vertex selon le temps
    animation(position, normal);


    // Eye-coordinate position of vertex, needed in various calculations
    ecPosition = gl_ModelViewMatrix * position;
    transformedNormal = fnormal(normal);

    // Do fixed functionality vertex transform
    gl_Position = gl_ModelViewProjectionMatrix*position;
    gl_ClipVertex = gl_ModelViewMatrix * position;

    gl_TexCoord[0] = gl_MultiTexCoord0; 
    gl_TexCoord[1] = gl_MultiTexCoord1; 
}