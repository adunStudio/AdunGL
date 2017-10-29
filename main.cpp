#include <iostream>
#include <GL/glut.h>
#include "graphics/window.h"
#include "graphics/shader.h"
#include "maths/maths.h"
#include "utils/fileutils.h"

using namespace std;
using namespace AdunGL;
using namespace graphics;
using namespace maths;
using namespace utils;

GLuint vao;

int main(int argc, char** argv)
{


    std::cout << "Hello, AdunGL!" << std::endl;

    Window window = Window::instance(argc, argv, "AdunGL", 800, 600);

    cout << "OpenGL Version: " << window.getVersion() << endl;

    cout << "window width: " << window.getWidth()  << endl;
    cout << "window height:" << window.getHeight() << endl;

    glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArrayAPPLE(vao);

    window.update([]() {

    });

    window.render([]() {
        Window::instance().clear();



        glutSwapBuffers();
    });

    window.run();

    return 1;
}
