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

    glEnable(GL_DEPTH_TEST);

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

        glPushMatrix();
        glTranslatef(-50, -50, -50);

        draw();

        Window::instance().draw();
    });

    window.reshape([](int w, int h) {

        glViewport (0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective (60.0f, w/h, 1.0, 1000.0);
        glTranslatef (0.0, 0.0, -150);
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

bool culling = false;
bool front_open = false;
int front_y = 0;

int robot_x = 0;
int robot_y = 0;
int robot_z = 0;

bool robot_move = false;
bool robot_jump = false;

float robot_rotate = 0;

float left_rotate = 0;
float right_rotate = 0;

bool left_up  = true;
bool right_up = false;


void draw()
{


    if(culling)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);



    // 윗면
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    {
        glVertex3f(0, 100, 0);

        glVertex3f(0, 100, 100);

        glVertex3f(100, 100, 100);

        glVertex3f(100, 100, 0);
    }
    glEnd();


    // 왼쪽 옆면
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    {
        glVertex3f(0, 100, 0);

        glVertex3f(0, 100, 100);

        glVertex3f(0, 0, 100);

        glVertex3f(0, 0, 0);
    }
    glEnd();

    // 앞면
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    {
        glVertex3f(0, front_y + 100, 100);

        glVertex3f(0, front_y + 0, 100);

        glVertex3f(100, front_y + 0, 100);

        glVertex3f(100, front_y + 100, 100);
    }
    glEnd();

    // 오른쪽 옆면
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    {
        glVertex3f(100, 100, 100);

        glVertex3f(100, 0, 100);

        glVertex3f(100, 0, 0);

        glVertex3f(100, 100, 0);
    }
    glEnd();

    // 뒷면
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    {
        glVertex3f(0, 100, 0);

        glVertex3f(0, 0, 0);

        glVertex3f(100, 0, 0);

        glVertex3f(100, 100, 0);
    }
    glEnd();


    // 아랫면
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    {
        glVertex3f(0, 0, 0);

        glVertex3f(0, 0, 100);

        glVertex3f(100, 0, 100);

        glVertex3f(100, 0, 0);
    }
    glEnd();


    glPopMatrix();
    ///////////////////////////


    glTranslatef(robot_x, robot_y, robot_z);


    glTranslatef(0, -12, 0);

    glRotatef(robot_rotate, 0, 1, 0);


    // 대가리
    glPushMatrix();
    {
        glColor3f(1, 0.5, 0.1);
        glutSolidCube(10);
        glTranslatef(0, -1, 5);
        glColor3f(1, 0, 0);
        glScalef(1, 1, 3);
        glutSolidCube(2);
    }
    glPopMatrix();

    // 몸통
    glPushMatrix();
    {
        glColor3f(1, 0.1, 0.1);
        glTranslatef(0, -17, 0);
        glScalef(1, 2, 1);
        glutSolidCube(10);
    }
    glPopMatrix();

    // 왼팔
    glPushMatrix();
    {
        glColor3f(0, 0.5, 1);
        glTranslatef(-9, -16, 0);
        glTranslatef(0, 4, 0);
        glRotatef(left_rotate, 1, 0, 0);
        glTranslatef(0, -4, 0);
        glScalef(1, 4, 1);
        glutSolidCube(4);
    }
    glPopMatrix();

    // 오른팔
    glPushMatrix();
    {
        glColor3f(0, 1, 0.5);
        glTranslatef(9, -16, 0);
        glTranslatef(0, 4, 0);
        glRotatef(right_rotate, 1, 0, 0);
        glTranslatef(0, -4, 0);
        glScalef(1, 4, 1);
        glutSolidCube(4);
    }
    glPopMatrix();

    // 왼다리
    glPushMatrix();
    {
        glColor3f(0, 0.5, 1);
        glTranslatef(-2, -33, 0);
        glTranslatef(0, 4, 0);
        glRotatef(left_rotate, 1, 0, 0);
        glTranslatef(0, -4, 0);
        glScalef(1, 3, 1);
        glutSolidCube(3);
    }
    glPopMatrix();

    // 오른다리
    glPushMatrix();
    {
        glColor3f(0, 1, 0.5);
        glTranslatef(2, -33, 0);
        glTranslatef(0, 4, 0);
        glRotatef(right_rotate, 1, 0, 0);
        glTranslatef(0, -4, 0);
        glScalef(1, 3, 1);
        glutSolidCube(3);
    }
    glPopMatrix();
}

void timer(int time)
{
    if(robot_jump)
    {
        robot_y ++;

        if(robot_y > 10)
            robot_jump = 0;
    }
    else
    {
        robot_y = max(0, robot_y - 1);
    }
    if(robot_move)
    {
        if(left_up)
        {
            left_rotate += 3;
            if(left_rotate >45)
                left_up = false;
        }
        else
        {
            left_rotate -= 3;
            if(left_rotate < -45)
                left_up = true;
        }

        if(right_up)
        {
            right_rotate += 3;
            if(right_rotate > 45)
                right_up = false;
        }
        else
        {
            right_rotate -= 3;
            if(right_rotate < -45)
                right_up = true;
        }
    }


    if (front_open)
    {
        front_y = std::min(100, front_y + 10);
    }

    if(Window::isKeyPressed('i'))
    {
        front_open = false;
        front_y = 0;
        robot_x = 0;
        robot_y = 0;
        robot_z = 0;

        robot_move = false;
        robot_jump = false;

        robot_rotate = 0;

        left_rotate = 0;
        right_rotate = 0;

        left_up  = true;
        right_up = false;
    }

    robot_move = false;

    if(Window::isKeyPressed('w'))
    {
        robot_move = true;

        robot_rotate = 180;
        robot_z = max(-40, robot_z -2);
    }

    if(Window::isKeyPressed('s'))
    {
        robot_move = true;

        robot_rotate = 0;
        robot_z = min(40, robot_z +2);
    }

    if(Window::isKeyPressed('a'))
    {
        robot_move = true;

        robot_rotate = 270;
        robot_x = max(-40, robot_x -2);
    }

    if(Window::isKeyPressed('d'))
    {
        robot_move = true;

        robot_rotate = 90;
        robot_x = min(40, robot_x +2);
    }

    if(Window::isKeyPressed('j'))
        robot_jump = true;

    if(Window::isKeyPressed('o'))
        front_open = true;

    if(Window::isKeyPressed('c'))
        culling = !culling;

    glutPostRedisplay();
    glutTimerFunc(SPEED, timer, 100);

}
