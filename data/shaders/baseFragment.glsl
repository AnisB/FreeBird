uniform sampler2D diffMap;
void main (void) 
{
    gl_FragColor = texture2D(diffMap, gl_TexCoord[0].xy)*0.5;
}


