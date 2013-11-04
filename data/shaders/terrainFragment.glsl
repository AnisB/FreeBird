uniform sampler2D heightMap;
uniform sampler2D normalMap;
uniform sampler2D riverMap;
uniform sampler2D ground;
uniform sampler2D grass;
uniform sampler2D snow;
uniform sampler2D sand;
uniform samplerCube skybox;


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
      vec4 grassMap = texture2D(riverMap,gl_TexCoord[0].st);
      float x1 = mod(gl_TexCoord[0].s*10.0, 1.0);
      float y1 = mod(gl_TexCoord[0].t*10.0, 1.0);
      float x2 = mod(gl_TexCoord[0].s*50.0, 1.0);
      float y2 = mod(gl_TexCoord[0].t*50.0, 1.0);

      vec4 grassColor = texture2D(riverMap,gl_TexCoord[0].st);
      vec4 snow = texture2D(snow,vec2(x2,y2));
      vec4 grassTex = texture2D(grass,vec2(x2,y2));
      vec4 sandTex = texture2D(sand,vec2(x2,y2));

      vec4 colorRock = texture2D(ground,vec2(x1,y1));
      if(grassColor.r > 0.2 || grassColor.g > 0.2 || grassColor.b > 0.2 )
      {
        vec4 colorHeight = texture2D(normalMap,gl_TexCoord[0].st);
        vec3 inci = normalize(-ecPosition.xyz);
        vec3 n = -colorHeight.xyz;
        n = fnormal(n);
        vec3 r = inci-2.0*(dot(inci,n)*n);
        vec4 skyboxMap = textureCube(skybox,r);
        gl_FragColor = grassColor.b*snow*skyboxMap*2.0+grassColor.g*grassTex+grassColor.r*sandTex*skyboxMap*2.0;
      }
      else
      {
        gl_FragColor = colorRock*0.5;
      }
    }
    else
    {
      gl_FragColor = vec4(0.0,0.0,0.0,0.0);
    }
}


