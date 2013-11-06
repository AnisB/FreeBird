
uniform sampler2D normalMap;
uniform samplerCube skybox;


vec4 colorVal;
vec4 Ambient;
vec4 Diffuse;
vec4 Specular;

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
    if (gl_FrontFacing)
    {
        vec2 lol = vec2(mod(planePosition.x + gl_TexCoord[0].x, 1.0), mod(planePosition.y +gl_TexCoord[0].y, 1.0));
        vec4 normal = texture2D(normalMap,lol);
        vec4 blue = vec4(0.4,0.6,0.8,1.0);
        vec3 inci = normalize(-ecPosition.xyz);
        vec3 n = fnormal(normal.xyz);
        vec3 r = inci-2.0*(dot(inci,n)*n);
        vec4 skyboxMap = textureCube(skybox,-r);
        gl_FragColor = skyboxMap*blue;
    }
    else
    {
      gl_FragColor = vec4(0.0,0.0,0.0,0.0);
    }
}


