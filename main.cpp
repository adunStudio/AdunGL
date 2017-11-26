#include <iostream>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
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

Group* group;
TileLayer* layer;

Label* fps;

int main(int argc, char** argv)
{
    std::cout << "Hello, AdunGL!" << std::endl;

    srand(time(NULL));

    Window window = Window::instance(argc, argv, "AdunGL", 960, 540);

    cout << window.getVersion() << endl;
    cout << window.getGLSLVersion() << endl;
    cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

    shader  = new Shader("/Users/adun/Desktop/AdunGL/AdunGL-Core/shaders/basic.vert", "/Users/adun/Desktop/AdunGL/AdunGL-Core/shaders/basic.frag");

    shader->enable();
    shader->setUniform2f("light_pos", vec2 (4.0f, 1.5f));


    layer = new TileLayer(shader);

    Texture* textures[] =
            {
                    new Texture("/Users/adun/Desktop/AdunGL/asset/test.png"),
                    new Texture("/Users/adun/Desktop/AdunGL/asset/tb.png"),
                    new Texture("/Users/adun/Desktop/AdunGL/asset/tc.png")
            };


    for(float y = -9.0; y < 9.0; ++y)
    {
        for(float x = -16.0; x < 16.0; ++x)
        {
            if (rand() % 4 == 0)
                layer->add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
            else
                layer->add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
        }
    }

    group = new Group(maths::mat4::translation(maths::vec3(-15.8f, 7.0f, 0.0f)));

    fps = new Label("", 0.4f, 0.4f, maths::vec4(1, 1, 1, 1));

    group->add(new Sprite(0, 0, 5, 1.5f, maths::vec4(0.3f, 0.3f, 0.3f, 0.9f)));
    group->add(fps);

    layer->add(group);

    GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };


    shader->enable();
    shader->setUniform1iv("textures", texIDs, 10);
    shader->setUniformMat4("pr_matrix", maths::mat4::orthographic(-16, 16, -9, 9, -1, 1));

    window.update(update);

    window.render([]() {
        Window::instance().clear();

        render();

        glutSwapBuffers();
    });

    window.run();

    for(int i = 0; i < 3; i++)
        delete textures[i];

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
    layer->render();

    frame++;

    if(timer.elapsed() - current_time > 1000.0f)
    {
        current_time += 1000.0f;
        fps->text = std::to_string(frame) + " fps";
        cout << frame << " fps" << endl;
        frame = 0;
    }
}
