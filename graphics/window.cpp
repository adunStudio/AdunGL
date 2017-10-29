//
// Created by adun on 2017. 10. 29..
//

#include "window.h"

namespace AdunGL
{
    namespace graphics
    {
        GLvoid reshapeCallback(int w, int h);
        GLvoid updateCallback();
        GLvoid renderCallback();


        Window* Window::instance_ = nullptr;

        Window::Window(const char* name, int width, int height)
                : name(name), width(width), height(height)
        {
            this->init();
        }

        Window::~Window() {
            glutDestroyWindow(window);
        }

        void Window::init()
        {

            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
            glutInitWindowPosition(100, 100);
            glutInitWindowSize(width, height);

            window = glutCreateWindow(name);

            glutIdleFunc(updateCallback);
            glutDisplayFunc(renderCallback);
            glutReshapeFunc(reshapeCallback);
        }

        void Window::run() const
        {
            glutMainLoop();
        }

        bool Window::closed() const
        {
            return glutGetWindow();
        }

        void Window::clear() const
        {
            glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            glColor4f(1, 1, 1, 1);
        }

        GLvoid reshapeCallback(int w, int h)
        {
            Window::instance().width = w;
            Window::instance().height= h;
            glViewport (0, 0, w, h);
            glLoadIdentity();
        }

        GLvoid updateCallback()
        {

        }

        GLvoid renderCallback()
        {
            Window::instance().clear();

            glBegin(GL_TRIANGLES);
            {
                glVertex2f(-0.5, -0.5);
                glVertex2f(-0.0, 0.5);
                glVertex2f(0.5, -0.5);
            }
            glEnd();

            glutSwapBuffers();
        }
    }
}