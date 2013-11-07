uniform sampler2D heightMap;
uniform sampler2D normalMap;
uniform sampler2D rockMap;
uniform sampler2D ground;
uniform sampler2D grass;


const float MAX_HEIGHT = 100.0;

varying vec4 ecPosition;

vec2 coordinates;


void animation(inout vec4 position)
{ 
    vec4 heightColor = texture2D(heightMap,coordinates.xy);
    // Déformation sur l'axe des X selon la position X
    float deltaPos = heightColor.r * MAX_HEIGHT;
    position += vec4(0.0, 1.0-deltaPos,0.0,0.0);
}


void main (void)
{ 
    coordinates = vec2(gl_MultiTexCoord0.x ,gl_MultiTexCoord0.y);


    vec4 position = gl_Vertex;

    // Transformation du vertex selon le temps
    animation(position);

    // Eye-coordinate position of vertex, needed in various calculations
    ecPosition = gl_ModelViewMatrix * position;

    // Do fixed functionality vertex transform
    gl_Position = gl_ModelViewProjectionMatrix*position;
    gl_ClipVertex = gl_ModelViewMatrix * position;

    gl_TexCoord[0].xy = coordinates; 
}