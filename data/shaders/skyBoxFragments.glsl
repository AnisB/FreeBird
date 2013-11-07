uniform samplerCube colorMap;

varying vec3 viewDirection;

void main (void) 
{
    // Écrire le nuanceur de fragments du Skybox.
    // ATTENTION !... un skybox N'EST PAS soumis à l'éclairage OpenGL
    // la texture qui y est appliquée est en mode REPLACE.
    // aucun éclairage ne doit survenir.
	// On récupère le pixel à afficher avec la direction interpolée par la pipeline 
	vec4 color = textureCube(colorMap,viewDirection.xyz);
	gl_FragColor = color*1.5;
}
