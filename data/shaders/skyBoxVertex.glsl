uniform sampler2D colorMap;

varying vec3 viewDirection;
varying vec3 normalDir;
void main (void)
{
   // effectuons la base : la transformation du vertex
   gl_Position = ftransform();

   // passer correctement les coordonn�es de texture
   // La direction d'un sommet est toujours sa position en
   // coordonn�es objet si le rep�re local est centr�
   viewDirection = gl_Vertex.xyz;
}
