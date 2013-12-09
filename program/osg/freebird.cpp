// Include du renderer
#include <renderer/renderer.h>

int main( int argc, char **argv )
{
	// Récupération du singleton
    Renderer &renderer = Renderer::Instance();
    // Init du renderer
    renderer.Init();
    // Lancement du renderer
    renderer.Run();
    return 0;
}
