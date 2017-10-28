#include <iostream>
#include "graphics/window.h"

using namespace std;
using namespace AdunGL;
using namespace graphics;

int main(int argc, char** argv)
{
    std::cout << "Hello, AdunGL!" << std::endl;

    Window window = Window::instance(argc, argv, "AdunGL", 800, 600);

    cout << "OpenGL Verison: " << window.getVersion() << endl;

    cout << "window width: " << window.getWidth()  << endl;
    cout << "window height:" << window.getHeight() << endl;

    window.run();

    return 1;
}
