uniform samplerCube colorMap;

varying vec3 viewDirection;

void main (void) 
{
    // �crire le nuanceur de fragments du Skybox.
    // ATTENTION !... un skybox N'EST PAS soumis � l'�clairage OpenGL
    // la texture qui y est appliqu�e est en mode REPLACE.
    // aucun �clairage ne doit survenir.
	// On r�cup�re le pixel � afficher avec la direction interpol�e par la pipeline 
	vec4 color = textureCube(colorMap,viewDirection.xyz);
	gl_FragColor = color*1.5;
}
