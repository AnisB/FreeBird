uniform sampler2D colorMap;

varying vec3 viewDirection;
varying vec3 normalDir;
void main (void)
{
   // effectuons la base : la transformation du vertex
   gl_Position = ftransform();

   // passer correctement les coordonnées de texture
   // La direction d'un sommet est toujours sa position en
   // coordonnées objet si le repère local est centré
   viewDirection = gl_Vertex.xyz;
}
