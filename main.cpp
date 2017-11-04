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

    Window window = Window::instance(argc, argv, "AdunGL", 960, 540);

    printf("Supported OpenGL version is %s.\n", window.getVersion());
    printf("Supported GLSL version is %s.\n", window.getGLSLVersion());

    GLuint vbo;

    GLfloat vertices[] =
            {
                    4, 3, 0,
                    12, 3, 0,
                    4, 6 , 0,
                    4, 6 , 0,
                    12, 6 , 0,
                    12, 3 , 0
            };


    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    Shader shader("/Users/adun/Desktop/AdunGL/shaders/basic.vert", "/Users/adun/Desktop/AdunGL/shaders/basic.frag");
    shader.enable();


    glUniformMatrix4fv(glGetUniformLocation(shader.shaderID, "pr_matrix"), 1, GL_FALSE, ortho.elements);
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
