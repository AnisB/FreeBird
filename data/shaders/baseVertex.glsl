
varying vec4 ecPosition;

float ffog(in float ecDistance)
{
    return(abs(ecDistance));
}


void main (void)
{ 

    ecPosition = gl_ModelViewMatrix * gl_Vertex;

    gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
    gl_TexCoord[0]= gl_MultiTexCoord0; 
    gl_FogFragCoord = ffog(ecPosition.z);
}
