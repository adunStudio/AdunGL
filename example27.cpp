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
GLvoid mouseCallback(int button, int state, int x, int y);

int main(int argc, char** argv)
{
    Window::DEFAULT_MOUSE = false;
    Window window = Window::instance(argc, argv, "AdunGL", 700, 700);
    Camera camera = Camera::instance();

    glEnable(GL_DEPTH_TEST);
    glEnable (GL_MAP1_VERTEX_3);

    window.update([]() {


        if(Window::isKeyPressed('q'))
            exit(0);



        glutPostRedisplay();
    });

    window.render([]() {

        Window::instance().clear(1, 1, 1);


        //Camera::inCamera();

        //Camera::drawAxis();


        draw();

        Window::instance().draw();
    });

    window.reshape([](int w, int h) {

        glViewport (0, 0, w, h);
        glOrtho(0, w, h, 0, -1, 1);



        Window::instance().setWidth(w);
        Window::instance().setHeight(h);

    });

    glutMouseFunc(mouseCallback);

    window.timer(timer);

    window.run();
}


struct Point
{
    int x, y;
};

vector<Point> points;

const int   SPEED =  50;
GLfloat ctrlpoints[100][3];
int pre = 0;
int cur = 0;

void draw()
{
    {
        for(int i = 0; i < points.size(); ++i)
        {
            ctrlpoints[i][0] = points[i].x;
            ctrlpoints[i][1] = points[i].y;
            ctrlpoints[i][2] = 0;
        }
    }

    glColor3f(0, 0, 0);


    int n = 0;

    if(points.size() > 0 )
    {
        // 3n + 1 = points.size()
        n = (points.size() - 1) / 3;


        for(int i = 0; i < n; ++i)
        {
            glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[i * 3][0]);

            glMapGrid1f(100.0, 0.0, 1.0);
            glEvalMesh1(GL_LINE, 0, 100);
        }
    }


    if(3 * n + 1 < points.size())
    {
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, points.size() - (3 * n) , &ctrlpoints[3 * n][0]);

        glMapGrid1f(100.0, 0.0, 1.0);
        glEvalMesh1(GL_LINE, 0, 100);

    }


    {
        glPointSize (5.0);
        glColor3f (0.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        for (int i = 0; i < points.size(); i++ )
            glVertex3f(points[i].x, points[i].y, 1);
        glEnd ();

    }
}

void timer(int time)
{
    if(Window::isKeyPressed('r'))
        points.clear();

    glutPostRedisplay();
    glutTimerFunc(SPEED, timer, 100);
}

GLvoid mouseCallback(int button, int state, int x, int y)
{
    if(state == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        Point point;
        point.x = x;
        point.y = y;
        points.push_back(point);
    }
}
