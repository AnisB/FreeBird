

uniform vec2 planePosition;


varying vec3  transformedNormal;
varying vec4 ecPosition;


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
    gl_TexCoord[0].xy = gl_MultiTexCoord0.xy;; 

    // Eye-coordinate position of vertex, needed in various calculations
    ecPosition = gl_ModelViewMatrix * position;
    transformedNormal = fnormal(normal);

    // Do fixed functionality vertex transform
    gl_Position = gl_ModelViewProjectionMatrix*position;

}
