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

    Camera::rotateX(30);

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

        //Camera::drawAxis();

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

float wire_angle = 0;

int max_height = 100;
int height = max_height;
int torus_height = 22;
int c = 0;



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


    glPushMatrix();
    {
        glTranslatef(0, -10, 0);
        glColor3f(0, 1, 0);
        glScalef(1, 0.01, 1);
        glutSolidCube(300);
    }
    glPopMatrix();


    glPushMatrix();
    {
        glColor4f(1, 0, 0, 1);
        glLineWidth(3);
        glBegin(GL_LINES);
        {
            glVertex3f(0, 0, 0);
            glVertex3f(0, max_height, 0);
        }
        glEnd();
    }
    glPopMatrix();

    for(int i = 0; i < c; ++i)
    {
        glPushMatrix();
        {
            glTranslatef(0, i * torus_height, 0);
            glColor4f(1, 1, 0, 0);
            glRotatef(90, 1 , 0, 0);
            glutWireTorus(10, 40, 30, 30);
        }
        glPopMatrix();
    }


    glPushMatrix();
    {
        glTranslatef(0, height, 0);
        glColor4f(1, 1, 0, 0);
        glRotatef(90, 1 , 0, 0);
        glRotatef(wire_angle, 0, 0, 1);
        glTranslatef(22, 0, 0);
        glutWireTorus(10, 40, 30, 30);
    }
    glPopMatrix();




}

void timer(int time)
{
    height -= 2;

    if(height < c * torus_height)
    {
        height = max_height;
        c++;
    }

    if(c == 6)
    {
        c = 0;
    }

    wire_angle += 35;

    if(Window::isKeyPressed('s'))
        smooth = !smooth;

    if(Window::isKeyPressed('d'))
        depth = !depth;

    if(Window::isKeyPressed('c'))
        culling = !culling;

    glutPostRedisplay();
    glutTimerFunc(SPEED, timer, 100);

}
