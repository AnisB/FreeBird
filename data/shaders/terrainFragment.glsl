uniform sampler2D heightMap;
uniform sampler2D normalMap;
uniform sampler2D ground;
uniform sampler2D grass;
uniform sampler2D snow;
uniform sampler2D sand;
uniform samplerCube skybox;


varying vec4 ecPosition;

vec4 colorVal;

vec4 Ambient;
vec4 Diffuse;
vec4 Specular;

vec4 MaterialSpec;



void pointLight(in int i, in vec3 normal, in vec3 eye, in vec3 ecPosition3)
{
   float nDotVP;       // normal . light direction
   float nDotHV;       // normal . light half vector
   float pf;           // power factor
   float attenuation;  // computed attenuation factor
   float d;            // distance from surface to light source
   vec3  VP;           // direction from surface to light position
   vec3  halfVector;   // direction of maximum highlights

   // Compute vector from surface to light position
   VP = vec3 (gl_LightSource[i].position) - ecPosition3;

   // Compute distance between surface and light position
   d = length(VP);

   // Normalize the vector from surface to light position
   VP = normalize(VP);

   // Compute attenuation


   halfVector = normalize(VP + eye);

   nDotVP = max(0.0, dot(normal, VP));
   nDotHV = max(0.0, dot(normal, halfVector));

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
    //pointLight(0, normal,eye,ecPosition3);

    color = gl_FrontLightModelProduct.sceneColor +
      Ambient  * gl_FrontMaterial.ambient +
      Diffuse  * gl_FrontMaterial.diffuse;
    color += Specular * MaterialSpec;
    color = clamp( color, 0.0, 1.0 );
    colorVal = color;
}


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
      vec4 grassMap = texture2D(heightMap,gl_TexCoord[0].st);
      float x2 = mod(gl_TexCoord[0].s*30.0, 1.0);
      float y2 = mod(gl_TexCoord[0].t*30.0, 1.0);

      vec4 snow = texture2D(snow,vec2(x2,y2));
      vec4 grassTex = texture2D(grass,vec2(x2,y2));
      vec4 sandTex = texture2D(sand,vec2(x2,y2));

      vec4 colorRock = texture2D(ground,vec2(x2,y2));
      vec3 normal = texture2D(normalMap,gl_TexCoord[0].st).xzy;
      normal = -fnormal(normal);
      if(grassMap.r >= 0.70 )
      {
        MaterialSpec = vec4(1.0,1.0,1.0,1.0);
        flight( normal, ecPosition);
        gl_FragColor = colorVal*snow;
      }
      else if(grassMap.r < 0.70 && grassMap.r > 0.45 )
      {
        MaterialSpec = vec4(0.8,0.8,0.8,1.0);
        flight( normal, ecPosition);
        gl_FragColor = colorVal*colorRock;
      }
      else if(grassMap.r < 0.45 && grassMap.r > 0.10 )
      {
        MaterialSpec = vec4(0.8,0.8,1.0,1.0);
        flight( normal, ecPosition);
        gl_FragColor = colorVal*grassTex;
      }
      else if(grassMap.r < 0.10 )
      {
        MaterialSpec = vec4(1.0,1.0,1.0,1.0);
        flight( normal, ecPosition);
        gl_FragColor = colorVal*sandTex;
      }
    }
    else
    {
      gl_FragColor = vec4(0.0,0.0,0.0,0.0);
    }
}


