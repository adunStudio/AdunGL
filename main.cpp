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

Shader* shader;

Timer timer;
float current_time = 0;
unsigned int frame = 0;

#define BATCH_RENDERER 1

#if BATCH_RENDERER

BatchRenderer2D* renderer;
Sprite* sprite1, * sprite2;
std::vector<Sprite*> sprites;

#else

Simple2DRenderer* renderer;
StaticSprite* sprite1, * sprite2;

#endif

int main(int argc, char** argv)
{
    std::cout << "Hello, AdunGL!" << std::endl;

    srand(time(NULL));



    Window window = Window::instance(argc, argv, "AdunGL", 960, 540);

    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    shader = new Shader("/Users/adun/Desktop/AdunGL/AdunGL-Core/shaders/basic.vert", "/Users/adun/Desktop/AdunGL/AdunGL-Core/shaders/basic.frag");
    shader->enable();
    shader->setUniformMat4("pr_matrix", ortho);
    shader->setUniform2f("light_pos", vec2 (4.0f, 1.5f));

#if BATCH_RENDERER


    renderer = new BatchRenderer2D();

    //sprite1 = new Sprite(5, 5, 4, 4, maths::vec4(1, 0, 1, 1)  );
    //sprite2 = new Sprite(7, 1, 2, 3, maths::vec4(0.2, 0, 1, 1));

    for(float y = 0; y < 9.0f; y += 0.05)
    {
        for(float x = 0; x < 16.0f; x += 0.05)
        {
            sprites.push_back(new Sprite(x, y, 0.04f, 0.04f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
        }
    }

#else

    renderer = new Simple2DRenderer();

    sprite1 = new StaticSprite(5, 5, 4, 4, maths::vec4(1, 0, 1, 1)  , *shader);
    sprite2 = new StaticSprite(7, 1, 2, 3, maths::vec4(0.2, 0, 1, 1), *shader);

#endif

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

#if BATCH_RENDERER

    renderer->begin();

     for(int i = 0; i < sprites.size(); ++i)
        renderer->submit(sprites[i]);

    renderer->end();

    renderer->flush();

#else

    renderer->submit(sprite1);
    renderer->submit(sprite2);
    renderer->flush();

#endif

    frame++;

    if(timer.elapsed() - current_time > 1000.0f)
    {
        current_time += 1000.0f;
        cout << frame << " fps" << endl;
        frame = 0;
    }
}

