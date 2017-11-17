#include <iostream>
#include <GLUT/glut.h>
#include <cmath>
#include <vector>
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

class Ball
{
private:
    float size = 10;
    float x, y, z;
    float speedX = 1;
    float speedY = 1;
    float speedZ = 1;
    float angle = 0;
public:
    Ball() : x(50), y(50), z(50)
    {
        angle = toRadians(rand() % 360);

        if(rand() % 2 == 0)
            speedX *= -1;
        if(rand() % 2 == 0)
            speedY *= -1;
        if(rand() % 2 == 0)
            speedZ *= -1;
    }

    void update()
    {
        if(size > x ||  100 - size < x)
            speedX *= -1;
        if(size > y ||  100 - size < y)
            speedY *= -1;
        if(size > z ||  100 - size < z)
            speedZ *= -1;

        x += (cos(angle) * speedX);
        y += (sin(angle) * speedY);
        z += speedZ;
    }

    void render()
    {
        glColor3f(0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(x, y, z);
            glutSolidSphere(5, 50, 50);
        }
        glPopMatrix();

    }
};

class Cube
{
private:
    float x, y, z;
    int r;
    float size;
    float speedX = 0;
    float speedY = 0;

public:
    Cube(float _size, float _x, float _y, float _z, int _r) : size(_size), x(_x), y(_y), z(_z), r(_r)
    {

    }

    void update()
    {
        int angle = static_cast<int>(Camera::getRotateZ()) % 360;
        if(angle < 0)
            angle += 360;

        if(size / 2  > x ||  100 - (size / 2) < x)
        {
            if(size / 2 > x) { x = size / 2; }
            if(100 - (size / 2) < x) { x = 100 - size / 2; }
            speedX = 0;

        }

        if(size / 2  > y ||  100 - (size / 2) < y)
        {
            if(size / 2 > y) { y = size / 2; }
            if(100 - (size / 2) < y) { y = 100 - size / 2; }
            speedY = 0;
        }

        if(angle < 90)
        {
            speedX -= 0.7;
            speedY -= 0.7;
        }
        else if(angle < 180)
        {
            speedX -=0.7;
            speedY += 0.7;
        }
        else if(angle < 270)
        {
            speedX += 0.7;
            speedY += 0.7;
        }
        else if(angle < 360)
        {
            speedX += 0.7;
            speedY -= 0.7;
        }
        x += speedX;
        y += speedY;
    }

    void render()
    {
        switch (r)
        {
            case 1:
                glColor3f(1, 0, 0);
                break;
            case 2:
                glColor3f(0, 1, 0);
                break;
            case 3:
                glColor3f(0, 0, 1);
                break;
        }
        glPushMatrix();
        {
            glTranslatef(x, y, z);
            glutSolidCube(size);
        }
        glPopMatrix();
    }
};


const int   SPEED =  50;
const int       R =  120;

bool smooth = true;
bool culling = false;
bool depth = true;
int mouse_x = 0;
int mouse_y = 0;
vector<int> xs;


vector<Ball* > balls;
vector<Cube* > cubes;

int main(int argc, char** argv)
{
    Window window = Window::instance(argc, argv, "AdunGL", 700, 700);
    Camera camera = Camera::instance();

    cubes.push_back(new Cube(22,  11, 11, 11, 1));
    cubes.push_back(new Cube(16, 8, 8, 22 + 8, 2));
    cubes.push_back(new Cube(10,  5, 5, 22 + 16 + 5, 3));


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

        Window::instance().clear(0, 0, 0);

        glLoadIdentity();

        Camera::inCamera();

        //Camera::drawAxis();
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
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    {
        glVertex3f(0, 100, 0);

        glVertex3f(0, 100, 100);

        glVertex3f(100, 100, 100);

        glVertex3f(100, 100, 0);
    }
    glEnd();


    // 왼쪽 옆면
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_QUADS);
    {
        glVertex3f(0, 100, 0);

        glVertex3f(0, 100, 100);

        glVertex3f(0, 0, 100);

        glVertex3f(0, 0, 0);
    }
    glEnd();



    // 오른쪽 옆면
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_QUADS);
    {
        glVertex3f(100, 100, 100);

        glVertex3f(100, 0, 100);

        glVertex3f(100, 0, 0);

        glVertex3f(100, 100, 0);
    }
    glEnd();

    // 뒷면
    glColor3f(1, 1, 1);
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


    for(auto ball : balls)
        ball->render();

    for(auto cube : cubes)
        cube->render();
}

void timer(int time)
{
    for(auto ball : balls)
        ball->update();

    for(auto cube : cubes)
        cube->update();

    if(Window::isKeyPressed('s'))
        smooth = !smooth;

    if(Window::isKeyPressed('d'))
        depth = !depth;

    if(Window::isKeyPressed('c'))
        culling = !culling;

    if(Window::isKeyPressed('b'))
        if(balls.size() != 5)
            balls.push_back(new Ball());


    if(Window::isMouseButtonPressed(GLUT_LEFT_BUTTON))
    {
        Window::getMousePosition(mouse_x, mouse_y);

        xs.push_back(mouse_x);
    }

    if(!Window::isMouseButtonPressed(GLUT_LEFT_BUTTON))
    {

        xs.clear();
    }

    if(xs.size() > 3)
    {
        int x = xs[0] - xs[xs.size()-1];

        if(x > 0)
            Camera::rotateZ(3);
        else
            Camera::rotateZ(-3);
        //xs.erase(xs.begin());
    }


    /*if(mouse_x < 400)
        Camera::rotateZ(1);
    else
        Camera::rotateZ(-1);*/

    glutPostRedisplay();
    glutTimerFunc(SPEED, timer, 100);

}