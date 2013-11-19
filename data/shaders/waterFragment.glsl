
uniform sampler2D normalMap;
uniform samplerCube skybox;


vec4 colorVal;

vec4 Ambient;
vec4 Diffuse;
vec4 Specular;

vec4 MaterialSpec;

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


void directionalLight(in int i, in vec3 normal)
{
   float nDotVP;         // normal . light direction
   float nDotHV;         // normal . light half vector
   float pf;             // power factor

   nDotVP = max(0.0, dot(normal, normalize(vec3 (gl_LightSource[i].position))));
   nDotHV = max(0.0, dot(normal, vec3 (gl_LightSource[i].halfVector)));

   if (nDotVP == 0.0)
   {
       pf = 0.0;
   }
   else
   {
       pf = pow(nDotHV, gl_FrontMaterial.shininess);

   }
   Ambient  += gl_LightSource[i].ambient;
   Diffuse  += gl_LightSource[i].diffuse * nDotVP;
   Specular += gl_LightSource[i].specular * pf;
}


float ffog(in float ecDistance)
{
    return(abs(ecDistance));
}

void flight(in vec3 normal, in vec4 ecPosition)
{
    vec4 color;
    vec3 ecPosition3;
    vec3 eye;

    ecPosition3 = (vec3 (ecPosition)) / ecPosition.w;
    eye = vec3 (0.0, 0.0, 1.0);

    // Clear the light intensity accumulators
    Ambient  = vec4 (0.0);
    Diffuse  = vec4 (0.0);
    Specular = vec4 (0.0);


    directionalLight(0, normal);

    color = gl_FrontLightModelProduct.sceneColor +
      Ambient  * gl_FrontMaterial.ambient +
      Diffuse  * gl_FrontMaterial.diffuse;
    color += Specular * MaterialSpec;
    color = clamp( color, 0.0, 1.0 );
    colorVal = color;
}
void main (void) 
{
    if (gl_FrontFacing)
    {
        vec2 lol = vec2(mod(planePosition.x + gl_TexCoord[0].x, 1.0), mod(planePosition.y +gl_TexCoord[0].y, 1.0));
        vec4 normal = texture2D(normalMap,lol);
        vec4 blue = vec4(0.3,0.4,0.6,1.0);
        vec3 inci = normalize(-ecPosition.xyz);
        vec3 n = -fnormal(normal.yzx);
        vec3 r = inci-2.0*(dot(inci,n)*n);
        vec4 skyboxMap = textureCube(skybox,-r);
        vec4 color =blue;
        MaterialSpec = vec4(0.3,0.6,1.0,1.0);
        vec3 normal2 = -fnormal(normal.yzx);
        flight( normal2, ecPosition);
        gl_FragColor = colorVal*color+skyboxMap;
    }
    else
    {
      gl_FragColor = vec4(0.0,0.0,0.0,0.0);
    }
}


