#include <vrj/Kernel/Kernel.h>

#include <rendering/renderer.h>
#include <common/defines.h>

int main( int argc, char **argv )
{
    // VRJuggler init
    vrj::Kernel * vrKernel = vrj::Kernel::Instance();
    Renderer *renderer = new Renderer(vrKernel);

    render.Init();

    if (argc <= 2)
    {
        PRINT_RED << "Il n'y a pas de fichier de configuration qui a été donné en paramètre"<<std::endl;
    }

    vrKernel->loadConfigFile(argv[2]);


    vrKernel->start();
    vrKernel->setApplication(renderer);
    vrKernel->waitForKernelStop();


    delete renderer;
    return 0;
}
