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



    // 3차원 상의 제어점 설정
    GLfloat ctrlpoints[3][4][3] = {
            {{-200.0, 0.0, 200.0},{-100.0, 100.0, 200.0},{100.0, -100.0, 200.0} ,{200.0, 0.0, 200.0}},
            {{-200.0, 0.0, 0.0}, {-100.0, 100.0, 0.0}, {100.0, -100.0, 0.0}, {200.0, 0.0, 0.0}},
            {{-200.0, 0.0, -200.0}, {-100.0, 100.0, -200.0}, {100.0, -100.0, -200.0}, {200.0, 0.0, -200.0}}
    };
    // 곡면 제어점 설정


    glMap2f (GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 3, &ctrlpoints[0][0][0]);


    glEnable (GL_MAP2_VERTEX_3);

    glColor3f(0, 0, 0);
    // 그리드를 이용한 곡면 드로잉
    glMapGrid2f (10, 0.0, 1.0, 10, 0.0, 1.0);

    // 선을 이용하여 그리드 연결
    glEvalMesh2 (GL_LINE, 0, 10, 0, 10);
    glPointSize (5.0);



    glColor3f (0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < 3; i++ )
        for ( int j = 0; j < 4; j++ )
            glVertex3fv (ctrlpoints[i][j]);
    glEnd ();



}

void timer(int time)
{

    glutPostRedisplay();
    glutTimerFunc(SPEED, timer, 100);

}
