#include <iostream>
#include <GLUT/glut.h>
#include <vector>
#include "AdunGL-Core/src.h"

using namespace std;
using namespace AdunGL;
using namespace graphics;
using namespace maths;
using namespace utils;

void update();
void render();


Timer timer;
float current_time = 0;
unsigned int frame = 0;

Shader* shader;
Texture* texture;

int main(int argc, char** argv)
{
    std::cout << "Hello, AdunGL!" << std::endl;

    srand(time(NULL));

    Window window = Window::instance(argc, argv, "AdunGL", 960, 540);

    shader  = new Shader("/Users/adun/Desktop/AdunGL/AdunGL-Core/shaders/tex.vert", "/Users/adun/Desktop/AdunGL/AdunGL-Core/shaders/tex.frag");

    shader->enable();
    shader->setUniform2f("light_pos", vec2 (4.0f, 1.5f));

    glActiveTexture(GL_TEXTURE0);
    texture = new Texture("/Users/adun/Desktop/AdunGL/test.png");
    texture->bind();

    std::cout << "width: " << texture->getWidth() << ", height: " << texture->getHeight() << std::endl;

    shader->enable();
    shader->setUniform1i("tex", 0);
    shader->setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

    window.update(update);

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

    shader->enable();
    shader->setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.f)));

    glutPostRedisplay();
}

void render()
{

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 0);
        glVertex2f(0, 0);

        glTexCoord2f(0, 1);
        glVertex2f(0, 4);

        glTexCoord2f(1, 1);
        glVertex2f(4, 4);

        glTexCoord2f(1, 0);
        glVertex2f(4, 0);
    }
    glEnd();

    /* 프레임 */
    frame++;

    if(timer.elapsed() - current_time > 1000.0f)
    {
        current_time += 1000.0f;
        cout << frame << " fps" << endl;
        frame = 0;
    }
}
