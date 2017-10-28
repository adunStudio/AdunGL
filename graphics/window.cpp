//
// Created by adun on 2017. 10. 29..
//

#include "window.h"

namespace AdunGL
{
    namespace graphics
    {
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

            glutIdleFunc(Window::updateCallback);
            glutDisplayFunc(Window::renderCallback);
            glutReshapeFunc(Window::reshapeCallback);
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

        void Window::update() const
        {

        }


        void Window::render() const
        {
            clear();

            glBegin(GL_TRIANGLES);
            {
                glVertex2f(-0.5, -0.5);
                glVertex2f(-0.0, 0.5);
                glVertex2f(0.5, -0.5);
            }
            glEnd();

            glutSwapBuffers();
        }

        void Window::reshape(int w, int h)
        {
            width = w;
            height= h;
            glViewport (0, 0, w, h);
            glLoadIdentity();
            //glOrtho(0, w, 0, h, -1, 1);
        }
    }
}