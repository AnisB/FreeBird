// Includes vrjuggler
#include <vrj/Kernel/Kernel.h>

// Includes projet
#include <renderer/renderer.h>
#include <common/defines.h>

int main( int argc, char **argv )
{
    // VRJuggler init
    vrj::Kernel * vrKernel = vrj::Kernel::instance();
    // Création du renderer
    Renderer *renderer = new Renderer(vrKernel);
    //Vérification des paramèters
    if (argc < 2)
    {
        PRINT_RED << "Il n'y a pas de fichier de configuration qui a été donné en paramètre"<< "Le nombre de fichiers est"<<argc<<END_PRINT_COLOR;
    }
    else
    {
        // Passage des autres arguments
		vrKernel->loadConfigFile(argv[1]);
		for ( int i = 2; i < argc; ++i )
		{
			vrKernel->loadConfigFile( argv[i] );
		}
    }
    // Lancement du kernel vrj
    vrKernel->start();
    vrKernel->setApplication(renderer);
    vrKernel->waitForKernelStop();

    // Suppression et fin
    delete renderer;
    return 0;
}
