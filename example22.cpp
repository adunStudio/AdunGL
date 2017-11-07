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

        Window::instance().clear(0.196078, 0.6, 0.8);

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

const int   SPEED =  50;
const int       R =  120;

float angle_airplane  = 0;
float angle_propeller = 0;

float scale_boost1 = 5;
float scale_boost2 = 3;

void draw()
{
    glTranslatef(sin(toRadians(angle_airplane)) * R, 0, cos(toRadians(angle_airplane)) * R);

    glRotatef(angle_airplane, 0, 1, 0);

    // 프로펠러
    glColor3f(0.90, 0.91, 0.98);
    glPushMatrix();
    {
        glRotatef(angle_propeller, 1, 0, 0);
        glScalef(1, 15, 1);
        glutSolidCube(3);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glRotatef(angle_propeller, 1, 0, 0);
        glScalef(1, 1, 15);
        glutSolidCube(3);
    }
    glPopMatrix();

    // 몸체
    glColor3f(0.85, 0.85, 0.10);
    glPushMatrix();
    {
        glTranslatef(-35, 0, 0);
        glRotatef(90, 0, 1, 0);
        glScalef(1, 0.3, 1);
        glutSolidCone(9, 45, 10, 10);
    }
    glPopMatrix();

    // 조종석
    glColor3f(1, 1, 1);
    glPushMatrix();
    {
        glTranslatef(-15, 1, 0);
        glRotatef(90, 0, 1, 0);
        glScalef(1, 0.7, 1);
        glutSolidCone(4, 10, 10, 10);
    }
    glPopMatrix();

    // 날개쪽 머시기
    glColor3f(1, 1, 1);
    glPushMatrix();
    {
        glTranslatef(-35, 1, 0);
        glRotatef(90, 0, 1, 0);
        glScalef(1, 0.7, 1);
        glutSolidCube(4);
    }
    glPopMatrix();

    // 날개
    glColor3f(0.35, 0.85, 0.50);
    glPushMatrix();
    {
        glTranslatef(-32, 0, 0);
        glScalef(3, 1, 15);
        glutSolidCube(3);
    }
    glPopMatrix();

    // 부스터 1
    glColor3f(1, 1, 1);
    glPushMatrix();
    {
        glColor3f(1, 0, 0);
        glTranslatef(-40, 0, 15);
        glutSolidSphere(scale_boost1, 10, 10);
        glColor3f(0, 1, 0);
        glTranslatef(-7, 0, 0);
        glutSolidSphere(scale_boost2, 10, 10);
        glColor3f(0, 0, 1);
        glTranslatef(-7, 0, 0);
        glScalef(13, 1, 1);
        glutSolidSphere(1, 10, 10);
    }
    glPopMatrix();

    // 부스터 2
    glColor3f(1, 1, 1);
    glPushMatrix();
    {
        glColor3f(1, 0, 0);
        glTranslatef(-40, 0, -15);
        glutSolidSphere(scale_boost1, 10, 10);
        glColor3f(0, 1, 0);
        glTranslatef(-7, 0, 0);
        glutSolidSphere(scale_boost2, 10, 10);
        glColor3f(0, 0, 1);
        glTranslatef(-7, 0, 0);
        glScalef(13, 1, 1);
        glutSolidSphere(1, 10, 10);
    }
    glPopMatrix();

}

void timer(int time)
{
    angle_propeller += 15;

    angle_airplane  += 5;

    if(rand() % 5 == 2)
    {
        scale_boost1 = scale_boost1 == 5 ? 9 : 5;
        scale_boost2 = scale_boost2 == 3 ? 6 : 3;
    }

    glutPostRedisplay();
    glutTimerFunc(SPEED, timer, 1);

}
