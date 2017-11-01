//
// Created by adun on 2017. 10. 29..
//

#include "window.h"
#include <functional>

namespace AdunGL
{
    namespace graphics
    {
        GLvoid reshapeCallback(int w, int h);
        GLvoid updateCallback();
        GLvoid renderCallback();
        GLvoid keyboardDownCallback(unsigned char key, int x, int y);
        GLvoid keyboardUpCallback(unsigned char key, int x, int y);
        GLvoid specialKeyboardCallback(int key, int x, int y);
        GLvoid mouseCallback(int button, int state, int x, int y);
        GLvoid mouseMoveCallback(int x, int y);

        Window* Window::instance_ = nullptr;

        bool Window::keys[MAX_KEYS] = { false };
        bool Window::mouseButtons[MAX_BUTTONS] = { false };

        double Window::mx;
        double Window::my;

        Window::Window(const char* name, int width, int height)
                : name(name), width(width), height(height)
        {
            this->init();
        }

        Window::~Window()
        {
            glutDestroyWindow(window);
        }

        void Window::init()
        {
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
            glutInitWindowPosition(100, 100);
            glutInitWindowSize(width, height);
            window = glutCreateWindow(name);

            //glutIdleFunc(updateCallback);
            //glutDisplayFunc(renderCallback);
            glutReshapeFunc(reshapeCallback);
            glutKeyboardFunc(keyboardDownCallback);
            glutKeyboardUpFunc(keyboardUpCallback);
            glutSpecialFunc(specialKeyboardCallback);
            glutMouseFunc(mouseCallback);
            glutPassiveMotionFunc(mouseMoveCallback);

            //printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
        }

        void Window::update(void (*func)())
        {
            glutIdleFunc(func);
        }

        void Window::render(void (*func)())
        {
            glutDisplayFunc(func);
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

        /*GLvoid updateCallback()
        {

        }*/

        /*GLvoid renderCallback()
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
        }*/

        GLvoid keyboardDownCallback(unsigned char key, int x, int y)
        {
            Window::keys[static_cast<int>(key)] = true;
        }

        GLvoid keyboardUpCallback(unsigned char key, int x, int y)
        {
            Window::keys[static_cast<int>(key)] = false;
        }

        GLvoid specialKeyboardCallback(int key, int x, int y)
        {

        }

        GLvoid mouseCallback(int button, int state, int x, int y)
        {
            Window::mouseButtons[button] = (state == GLUT_LEFT_BUTTON);
        }

        GLvoid mouseMoveCallback(int x, int y)
        {
            Window::mx = x;
            Window::my = y;
        }

        bool Window::isKeyPressed(unsigned char key)
        {
            // TODO: Log this!
            if(static_cast<int>(key) >= MAX_KEYS)
                return false;

            return keys[static_cast<int>(key)];
        }

        bool Window::isMouseButtonPressed(int button)
        {
            // TODO: Log this!
            if(button >= MAX_BUTTONS)
                return false;

            return mouseButtons[button];
        }

        void Window::getMousePosition(int& x, int& y)
        {
            x = mx;
            y = my;
        }

    }
}