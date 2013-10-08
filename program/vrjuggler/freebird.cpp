#include <vrj/Kernel/Kernel.h>

#include <renderer/renderer.h>
#include <common/defines.h>

int main( int argc, char **argv )
{
    // VRJuggler init
    vrj::Kernel * vrKernel = vrj::Kernel::instance();
    Renderer *renderer = new Renderer(vrKernel);

    if (argc < 2)
    {
        PRINT_RED << "Il n'y a pas de fichier de configuration qui a été donné en paramètre"<< "Le nombre de fichiers est"<<argc<<END_PRINT_COLOR;
	exit(1);
    }
    vrKernel->loadConfigFile(argv[1]);


    vrKernel->start();
    vrKernel->setApplication(renderer);
    vrKernel->waitForKernelStop();


    delete renderer;
    return 0;
}
