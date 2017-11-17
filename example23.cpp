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



int main(int argc, char** argv)
{
    Window window = Window::instance(argc, argv, "AdunGL", 700, 700);
    Camera camera = Camera::instance();

    camera.rotateX(30);
    camera.rotateY(-45);

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

        if(Window::isKeyPressed("up"))
            Camera::transY(5);

        if(Window::isKeyPressed("down"))
            Camera::transY(-5);

        if(Window::isKeyPressed("left"))
            Camera::transX(5);

        if(Window::isKeyPressed("right"))
            Camera::transX(-5);

        if(Window::isKeyPressed('q'))
            exit(0);


        glutPostRedisplay();
    });

    window.render([]() {

        Window::instance().clear(1, 1, 1);

        glLoadIdentity();


        Camera::inCamera();

        Camera::drawAxis();
        glTranslatef(-50, -50, -50);

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







const int   SPEED =  50;
const int       R =  120;

bool smooth = true;
bool culling = false;
bool depth = true;

bool open_top = false;
bool open_bottom = false;


int top_y = 100;
int top_z = 100;


int bottom_y = 0;
int bottom_z = 100;


void draw()
{

    if(smooth)
        glShadeModel(GL_SMOOTH);
    else
        glShadeModel(GL_FLAT);

    if(culling)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    if(depth)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    // 윗면
    glBegin(GL_QUADS);
    {
        glColor4f(0, 1, 0, 1);
        glVertex3f(0, 100, 0);

        glColor4f(1, 1, 0, 1);
        glVertex3f(0, top_y, top_z);

        glColor4f(0, 1, 1, 1);
        glVertex3f(100, top_y, top_z);

        glColor4f(1, 1, 1, 1);
        glVertex3f(100, 100, 0);
    }
    glEnd();


    // 왼쪽 옆면
    glBegin(GL_QUADS);
    {
        glColor4f(0, 1, 0, 1);
        glVertex3f(0, 100, 0);

        glColor4f(1, 1, 0, 1);
        glVertex3f(0, 100, 100);

        glColor4f(0, 0, 1, 1);
        glVertex3f(0, 0, 100);

        glColor4f(0, 0, 0, 1);
        glVertex3f(0, 0, 0);
    }
    glEnd();

    // 앞면
    glBegin(GL_QUADS);
    {
        glColor4f(1, 1, 0, 1);
        glVertex3f(0, 100, 100);

        glColor4f(0, 0, 1, 1);
        glVertex3f(0, bottom_y, bottom_z);

        glColor4f(1, 0, 1, 1);
        glVertex3f(100, bottom_y, bottom_z);

        glColor4f(0, 1, 1, 1);
        glVertex3f(100, 100, 100);
    }
    glEnd();

    // 오른쪽 옆면
    glBegin(GL_QUADS);
    {
        glColor4f(0, 1, 1, 1);
        glVertex3f(100, 100, 100);

        glColor4f(1, 0, 1, 1);
        glVertex3f(100, 0, 100);

        glColor4f(1, 0, 0, 1);
        glVertex3f(100, 0, 0);

        glColor4f(1, 1, 1, 1);
        glVertex3f(100, 100, 0);
    }
    glEnd();

    // 뒷면
    glBegin(GL_QUADS);
    {
        glColor4f(0, 1, 0, 1);
        glVertex3f(0, 100, 0);

        glColor4f(0, 0, 0, 1);
        glVertex3f(0, 0, 0);

        glColor4f(1, 0, 0, 1);
        glVertex3f(100, 0, 0);

        glColor4f(1, 1, 1, 1);
        glVertex3f(100, 100, 0);
    }
    glEnd();


    // 아랫면
    glBegin(GL_QUADS);
    {
        glColor4f(0, 0, 0, 1);
        glVertex3f(0, 0, 0);

        glColor4f(0, 0, 1, 1);
        glVertex3f(0, 0, 100);

        glColor4f(1, 0, 1, 1);
        glVertex3f(100, 0, 100);

        glColor4f(1, 0, 0, 1);
        glVertex3f(100, 0, 0);
    }
    glEnd();
}

void timer(int time)
{

    Camera::rotateY(1);

    if(open_top)
    {
        top_y = std::min(200, top_y + 10);
        top_z = std::max(0, top_z - 10);
    }
    else
    {
        top_y = std::max(100, top_y - 10);
        top_z = std::min(100, top_z + 10);
    }

    if(open_bottom)
    {
        bottom_y = std::min(100, bottom_y + 10);
        bottom_z = std::min(200, bottom_z + 10);
    }
    else
    {
        bottom_y = std::max(0, bottom_y -10);
        bottom_z = std::max(100, bottom_z -10);
    }

    if(Window::isKeyPressed('t'))
        open_top = !open_top;

    if(Window::isKeyPressed('b'))
        open_bottom = !open_bottom;

    if(Window::isKeyPressed('s'))
        smooth = !smooth;

    if(Window::isKeyPressed('d'))
        depth = !depth;

    if(Window::isKeyPressed('c'))
        culling = !culling;

    glutPostRedisplay();
    glutTimerFunc(SPEED, timer, 100);

}
