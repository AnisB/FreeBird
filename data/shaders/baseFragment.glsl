varying vec4 ecPosition;

uniform sampler2D diffMap;
void main (void) 
{
    vec4 color = texture2D(diffMap, gl_TexCoord[0].xy)*0.5;
	float fog;
	fog = (gl_Fog.end - gl_FogFragCoord) * gl_Fog.scale;
	fog = clamp(fog, 0.0, 1.0);
	color = vec4(mix( vec3(gl_Fog.color), vec3(color), fog), color.a);
	gl_FragColor = color;
}


