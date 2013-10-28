uniform sampler2D heightMap;
uniform sampler2D riverMap;
uniform sampler2D rockMap;
uniform sampler2D ground;
uniform sampler2D grass;
uniform sampler2D foam;


vec4 colorVal;
vec4 Ambient;
vec4 Diffuse;
vec4 Specular;

const float WATER_LEVEL = 0.7;


varying vec3  transformedNormal;
const float alphaFade = 1.0;
varying vec4 ecPosition;

varying float isWater;


void directionalLight(in int i, in vec3 normal)
{
   float nDotVP;         // normal . light direction
   float nDotHV;         // normal . light half vector
   float pf;             // power factor

   nDotVP = max(0.0, dot(normal, normalize(vec3(0.0, -1.0, 0.0))));
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
   attenuation = 1.0 / (gl_LightSource[i].constantAttenuation +
       gl_LightSource[i].linearAttenuation * d +
       gl_LightSource[i].quadraticAttenuation * d * d);

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
   Ambient  += gl_LightSource[i].ambient*attenuation;
   Diffuse  += gl_LightSource[i].diffuse * nDotVP * attenuation;
   Specular += gl_LightSource[i].specular * pf * attenuation;
}



void flight(in vec3 normal, in vec4 ecPosition, bool isSpec)
{
    vec4 color;
    vec3 ecPosition3;
    vec3 eye;

    ecPosition3 = (vec3 (ecPosition)) / ecPosition.w;
    eye = vec3 (0.0, 0.0, 1.0);

    // Clear the light intensity accumulators
    Ambient  = vec4 (0.0);
    Diffuse  = vec4 (0.0);
    if(isSpec)
    {
      Specular = vec4 (0.2);
    }

    directionalLight(0, normal);
    //pointLight(0, normal, eye, ecPosition3);

    color = gl_FrontLightModelProduct.sceneColor +
      Ambient  * gl_FrontMaterial.ambient +
      Diffuse  * gl_FrontMaterial.diffuse;
    color += Specular * gl_FrontMaterial.specular;
    color = clamp( color, 0.0, 1.0 );
    colorVal = color;

    //colorVal.a *= alphaFade;
}


void main (void) 
{
    if (gl_FrontFacing)
    {
      vec4 colorHeight = texture2D(heightMap,gl_TexCoord[0].st);
      vec4 colorRiver = texture2D(riverMap,gl_TexCoord[0].st);
      vec4 blendColor = texture2D(rockMap,gl_TexCoord[0].st);
      

      float x1 = mod(gl_TexCoord[0].s*50.0, 1.0);
      float y1 = mod(gl_TexCoord[0].t*50.0, 1.0);
      float x2 = mod(gl_TexCoord[0].s*20.0, 1.0);
      float y2 = mod(gl_TexCoord[0].t*20.0, 1.0);

      vec4 colorRock = texture2D(ground,vec2(x1,y1));
      vec4 colorGrass = texture2D(grass,vec2(x2,y2));

      if(colorRiver.r > 0.0 ||  isWater >= 0.5)
      {

        flight(transformedNormal, ecPosition, true);
        vec4 blue = vec4(0.2,0.6,1.0,1.0);
        gl_FragColor = colorVal*blue;
      }
      else
      {
        flight(transformedNormal, ecPosition, false);
        vec4 colorBlended = (1.0-blendColor)*colorRock + 2.0*blendColor*colorGrass;
        gl_FragColor = colorVal*colorBlended;
      }
    }
    else
    {
      gl_FragColor = vec4(0.0,0.0,0.0,0.0);
    }
}


