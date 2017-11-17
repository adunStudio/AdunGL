#include <iostream>
#include <GLUT/glut.h>
#include "graphics/window.h"
#include "graphics/shader.h"
#include "maths/maths.h"
#include "utils/fileutils.h"
#include "graphics/buffers/buffer.h"
#include "graphics/buffers/indexBuffer.h"
#include "graphics/buffers/vertexArray.h"
#include "graphics/renderer2d.h"
#include "graphics/simple2drenderer.h"

using namespace std;
using namespace AdunGL;
using namespace graphics;
using namespace maths;
using namespace utils;

void update();
void render();

Shader* shader;
Simple2DRenderer* renderer;
Renderable2D* sprite1, * sprite2;


int main(int argc, char** argv)
{
    std::cout << "Hello, AdunGL!" << std::endl;

    Window window = Window::instance(argc, argv, "AdunGL", 960, 540);

    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    shader = new Shader("/Users/adun/Desktop/AdunGL/shaders/basic.vert", "/Users/adun/Desktop/AdunGL/shaders/basic.frag");
    shader->enable();
    shader->setUniformMat4("pr_matrix", ortho);
    //shader->setUniformMat4("ml_matrix", mat4::translation(vec3(3233330, -112340, 0)));
    shader->setUniform2f("light_pos", vec2 (4.0f, 1.5f));


    renderer = new Simple2DRenderer();

    sprite1 = new Renderable2D(maths::vec3(5, 5, 0), maths::vec2(4, 4), maths::vec4(1, 0, 1, 1), *shader);
    sprite2 = new Renderable2D(maths::vec3(7, 1, 0), maths::vec2(2, 3), maths::vec4(0.2, 0, 1, 1), *shader);


    window.update(update);

    glEnableClientState(GL_VERTEX_ARRAY);

    window.render([]() {
        Window::instance().clear();

        render();

        glutSwapBuffers();
    });

    window.run();
    return 1;
}

void update()
{
    int x, y;
    Window::instance().getMousePosition(x, y);
    shader->setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.f)));
    glutPostRedisplay();
}

void render()
{
    renderer->submit(sprite1);
    renderer->submit(sprite2);
    renderer->flush();
}

