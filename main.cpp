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
Shader* shader;
int main(int argc, char** argv)
{

    std::cout << "Hello, AdunGL!" << std::endl;

    Window window = Window::instance(argc, argv, "AdunGL", 800, 600);

    cout << "OpenGL Version: " << window.getVersion() << endl;

    cout << "window width: " << window.getWidth()  << endl;
    cout << "window height:" << window.getHeight() << endl;

    glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArrayAPPLE(vao);

    shader = new Shader(
            "/Users/adun/Desktop/AdunGL/shaders/basic.vert",
            "/Users/adun/Desktop/AdunGL/shaders/basic.frag"
    );


    window.update([]() {

    });

    window.render([]() {
        Window::instance().clear();

        glBegin(GL_TRIANGLES);
        {
            glVertex2f(-0.5, -0.5);
            glVertex2f(-0.0, 0.5);
            glVertex2f(0.5, -0.5);
        }
        glEnd();

        glutSwapBuffers();
    });

    window.run();

    return 1;
}
