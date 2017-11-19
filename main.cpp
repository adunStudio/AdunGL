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
Shader* shader2;

TileLayer* layer;
TileLayer* layer2;


int main(int argc, char** argv)
{
    std::cout << "Hello, AdunGL!" << std::endl;

    srand(time(NULL));

    Window window = Window::instance(argc, argv, "AdunGL", 960, 540);

    shader  = new Shader("/Users/adun/Desktop/AdunGL/AdunGL-Core/shaders/basic.vert", "/Users/adun/Desktop/AdunGL/AdunGL-Core/shaders/basic.frag");
    shader2 = new Shader("/Users/adun/Desktop/AdunGL/AdunGL-Core/shaders/basic.vert", "/Users/adun/Desktop/AdunGL/AdunGL-Core/shaders/basic.frag");

    shader->enable();
    shader2->enable();
    shader->setUniform2f("light_pos", vec2 (4.0f, 1.5f));
    shader2->setUniform2f("light_pos", vec2 (4.0f, 1.5f));

    layer = new TileLayer(shader);

    for(float y = -9.0; y < 9.0; y += 0.1)
    {
        for(float x = -16.0; x < 16.0; x += 0.1)
        {
            layer->add(new Sprite(x, y, 0.08, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
        }
    }

    layer2 = new TileLayer(shader2);

    layer2->add(new Sprite(-2, -2, 4, 4, maths::vec4(1, 0, 1, 1)));


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

    shader->enable();
    shader->setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.f)));
    shader2->enable();
    shader2->setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.f)));

    glutPostRedisplay();
}

void render()
{
    layer->render();
    layer2->render();

    frame++;

    if(timer.elapsed() - current_time > 1000.0f)
    {
        current_time += 1000.0f;
        cout << frame << " fps" << endl;
        frame = 0;
    }
}

