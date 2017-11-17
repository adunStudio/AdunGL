//
// Created by adun on 2017. 10. 29..
//

#include "window.h"

namespace AdunGL
{
    namespace graphics
    {
        GLvoid keyboardDownCallback(unsigned char key, int x, int y);
        GLvoid keyboardUpCallback(unsigned char key, int x, int y);
        GLvoid specialKeyboardDownCallback(int key, int x, int y);
        GLvoid specialKeyboardUpCallback(int key, int x, int y);
        GLvoid mouseCallback(int button, int state, int x, int y);
        GLvoid mouseMoveCallback(int x, int y);

        bool Window::DEFAULT_MOUSE = true;

        Window* Window::instance_ = nullptr;

        bool Window::keys[MAX_KEYS] = { false };
        bool Window::mouseButtons[MAX_BUTTONS] = { false };
        map<string, bool> Window::keyMaps = {{"up", false}, {"down", false}, {"left", false}, {"right", false}};

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
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
            glutInitWindowPosition(100, 100);
            glutInitWindowSize(width, height);

            window = glutCreateWindow(name);
            //glEnable(GL_DEPTH_TEST);

            //glutIdleFunc(updateCallback);
            //glutDisplayFunc(renderCallback);
            //glutReshapeFunc(reshapeCallback);
            glutKeyboardFunc(keyboardDownCallback);
            glutKeyboardUpFunc(keyboardUpCallback);
            glutSpecialFunc(specialKeyboardDownCallback);
            glutSpecialUpFunc(specialKeyboardUpCallback);
            if(DEFAULT_MOUSE)
                glutMouseFunc(mouseCallback);
            glutPassiveMotionFunc(mouseMoveCallback);
            glutMotionFunc(mouseMoveCallback);
        }

        void Window::update(void (*func)())
        {
            glutIdleFunc(func);
        }

        void Window::render(void (*func)())
        {
            glutDisplayFunc(func);
        }

        void Window::reshape(void (*func)(int, int))
        {
            glutReshapeFunc(func);
        }

        void Window::timer(void (*func)(int))
        {
            glutTimerFunc(0, func, 0);
        }
        void Window::run() const
        {
            glutMainLoop();
        }

        bool Window::closed() const
        {
            return glutGetWindow();
        }

        void Window::clear(float r, float g, float b) const
        {
            glClearColor(r, g, b, 1.0f);
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            glColor4f(1, 1, 1, 1);
        }

        GLvoid keyboardDownCallback(unsigned char key, int x, int y)
        {
            Window::keys[static_cast<int>(key)] = true;
        }

        GLvoid keyboardUpCallback(unsigned char key, int x, int y)
        {
            Window::keys[static_cast<int>(key)] = false;
        }

        GLvoid specialKeyboardDownCallback(int key, int x, int y)
        {
            if(key == GLUT_KEY_UP)
                Window::keyMaps["up"]    = true;
            if(key == GLUT_KEY_DOWN)
                Window::keyMaps["down"]  = true;
            if(key == GLUT_KEY_LEFT)
                Window::keyMaps["left"]  = true;
            if(key == GLUT_KEY_RIGHT)
                Window::keyMaps["right"] = true;
        }

        GLvoid specialKeyboardUpCallback(int key, int x, int y)
        {
            if(key == GLUT_KEY_UP)
                Window::keyMaps["up"]    = false;
            if(key == GLUT_KEY_DOWN)
                Window::keyMaps["down"]  = false;
            if(key == GLUT_KEY_LEFT)
                Window::keyMaps["left"]  = false;
            if(key == GLUT_KEY_RIGHT)
                Window::keyMaps["right"] = false;
        }

        GLvoid mouseCallback(int button, int state, int x, int y)
        {
            Window::mouseButtons[button] = (state == GLUT_DOWN);
        }

        GLvoid mouseMoveCallback(int x, int y)
        {
            Window::mx =  x; // - Window::instance().width / 2;
            Window::my =  y;//(y - Window::instance().height / 2) * -1 ;
        }

        bool Window::isKeyPressed(unsigned char key)
        {
            // TODO: Log this!
            if(static_cast<int>(key) >= MAX_KEYS)
                return false;

            return keys[static_cast<int>(key)];
        }

        bool Window::isKeyPressed(const string& key)
        {
            return keyMaps[key];
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