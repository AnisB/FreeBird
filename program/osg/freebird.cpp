#include <renderer/renderer.h>

int main( int argc, char **argv )
{
    Renderer &renderer = Renderer::Instance();
    renderer.Init();
    renderer.Run();
    return 0;
}
