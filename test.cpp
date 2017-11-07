#include <iostream>
#include <GLUT/glut.h>
#include <cmath>
#include "graphics/window.h"
#include "graphics/shader.h"
#include "maths/maths.h"
#include "utils/fileutils.h"
#include "graphics/buffers/buffer.h"
#include "graphics/buffers/indexBuffer.h"
#include "graphics/buffers/vertexArray.h"
#include "graphics/camera.h"

using namespace std;
using namespace AdunGL;
using namespace graphics;
using namespace maths;
using namespace utils;

void draw();
void timer(int);

const float RADIAN  = static_cast<float>(3.14159/180);

int main(int argc, char** argv)
{
    Window window = Window::instance(argc, argv, "AdunGL", 500, 500);
    Camera camera = Camera::instance();

    window.update([]() {

        if(Window::isKeyPressed('r'))
            Camera::reset();

        if(Window::isKeyPressed('x'))
            Camera::rotateX(5);
        if(Window::isKeyPressed('X'))
            Camera::rotateX(-5);

        if(Window::isKeyPressed('y'))
            Camera::rotateY(5);
        if(Window::isKeyPressed('Y'))
            Camera::rotateY(-5);

        if(Window::isKeyPressed('z'))
            Camera::rotateZ(5);
        if(Window::isKeyPressed('Z'))
            Camera::rotateZ(-5);

        if(Window::isKeyPressed('+'))
            Camera::transZ(5);
        if(Window::isKeyPressed('-'))
            Camera::transZ(-5);

        if(Window::isKeyPressed('q'))
            exit(0);

        glutPostRedisplay();
    });

    window.render([]() {

        Window::instance().clear();

        glLoadIdentity();

        Camera::inCamera();

        Camera::drawAxis();

        draw();

        Window::instance().draw();
    });

    window.reshape([](int w, int h) {

        glViewport (0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective (60.0f, w/h, 1.0, 1000.0);
        glTranslatef (0.0, 0.0, -300);
        glMatrixMode(GL_MODELVIEW);
        gluLookAt (0, 0, 0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
        Window::instance().setWidth(w);
        Window::instance().setHeight(h);

    });

    window.timer(timer);

    window.run();
}


void draw()
{



}

void timer(int time)
{
    glutPostRedisplay();
    //glutTimerFunc(SPEED, timer, 1);
}
