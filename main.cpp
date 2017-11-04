#include <iostream>
#include <GLUT/glut.h>
#include "graphics/window.h"
#include "graphics/shader.h"
#include "maths/maths.h"
#include "utils/fileutils.h"

using namespace std;
using namespace AdunGL;
using namespace graphics;
using namespace maths;
using namespace utils;

int main(int argc, char** argv)
{
    std::cout << "Hello, AdunGL!" << std::endl;

    Window window = Window::instance(argc, argv, "AdunGL", 800, 600);

    printf("Supported OpenGL version is %s.\n", window.getVersion());
    printf("Supported GLSL version is %s.\n", window.getGLSLVersion());

    GLuint vbo;

    GLfloat vertices[] =
            {
                    -0.5f, -0.5f, 0.0f,
                    -0.5f,  0.5f, 0.0f,
                     0.5f,  0.5f, 0.0f,
                     0.5f,  0.5f, 0.0f,
                     0.5f, -0.5f, 0.0f,
                    -0.5f, -0.5f, 0.0f,
            };


    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    Shader shader("/Users/adun/Desktop/AdunGL/shaders/basic.vert", "/Users/adun/Desktop/AdunGL/shaders/basic.frag");

    shader.enable();

    window.update([]() {

    });

    window.render([]() {
        Window::instance().clear();

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glutSwapBuffers();
    });

    window.run();
    return 1;
}
