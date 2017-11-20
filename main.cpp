#include <iostream>
#include <GLUT/glut.h>
#include <vector>
#include "AdunGL-Core/src.h"

#include <FreeImage.h>

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

#define TEST_ADUN 0

#if 0
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

#if TEST_ADUN

    for(float y = -9.0; y < 9.0; y += 0.1)
    {
        for(float x = -16.0; x < 16.0; x += 0.1)
        {
            layer->add(new Sprite(x, y, 0.08, 0.04, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
        }
    }

#else

    mat4 transform = mat4::translation(vec3(-15, 5, 0)) * mat4::rotation(45, vec3(0, 0, 1));
    Group* group = new Group(transform);
    group->add(new Sprite(0, 0, 6, 3, vec4(1, 1, 1, 1)));

    Group* button = new Group(mat4::translation(vec3(0.5, 0.5, 0)));
    button->add(new Sprite(0, 0, 5, 2, vec4(1, 0, 1, 1)));
    button->add(new Sprite(0.5, 0.5, 3, 1, vec4(0.2, 0.3, 0.8, 1)));

    group->add(button);

    layer->add(group);

#endif


    layer2 = new TileLayer(shader2);

    layer2->add(new Sprite(-2, -2, 4, 4, maths::vec4(1, 0, 1, 1)));

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
    shader2->enable();
    shader2->setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.f)));

    glutPostRedisplay();
}

void render()
{
    layer->render();
    //layer2->render();

    frame++;

    if(timer.elapsed() - current_time > 1000.0f)
    {
        current_time += 1000.0f;
        cout << frame << " fps" << endl;
        frame = 0;
    }
}

#endif

int main()
{
    const char* filename = "/Users/adun/Desktop/AdunGL/test.png";

    //image format
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    //pointer to the image, once loaded
    FIBITMAP *dib(0);
    //pointer to the image data
    BYTE* bits(0);
    //image width and height
    unsigned int width(0), height(0);
    //OpenGL's image ID to map to
    GLuint gl_texID;

    //check the file signature and deduce its format
    fif = FreeImage_GetFileType(filename, 0);
    //if still unknown, try to guess the file format from the file extension
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);
    //if still unkown, return failure
    if (fif == FIF_UNKNOWN)
        return false;

    //check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_Load(fif, filename);
    //if the image failed to load, return failure
    if (!dib)
        return false;

    //retrieve the image data
    bits = FreeImage_GetBits(dib);
    unsigned int bitsPerPixel = FreeImage_GetBPP(dib);
    unsigned int pitch = FreeImage_GetPitch(dib);
    //get the image width and height

    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);
    //if this somehow one of these failed (they shouldn't), return failure
    if ((bits == 0) || (width == 0) || (height == 0))
        return false;

    for (int y = height; y > 0; y--)
    {
        BYTE *pixel = (BYTE*)bits;
        for (int x = 0; x < width; x++)
        {
            std::cout << +pixel[FI_RGBA_RED] << " " << +pixel[FI_RGBA_GREEN] << " " << +pixel[FI_RGBA_BLUE] << std::endl;
            pixel += 3;
        }
        // next line
        bits += pitch;
    }
    FreeImage_Unload(dib);

    return 1;
}