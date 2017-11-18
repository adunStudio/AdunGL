//
// Created by adun on 2017. 10. 29..
//

#ifndef ADUNGL_WINDOW_H
#define ADUNGL_WINDOW_H

#include <iostream>
#include <GLUT/glut.h>
#include <cassert>
#include <map>

using namespace std;

namespace AdunGL
{
    namespace graphics
    {
        #define MAX_KEYS    256
        #define MAX_BUTTONS 32

        class Window
        {
        private:
            static Window* instance_;

            static bool keys[MAX_KEYS];
            static bool mouseButtons[MAX_BUTTONS];
            static map<string, bool> keyMaps;


            static double mx, my;


        public:

            static bool DEFAULT_MOUSE;

            static Window& instance()
            {
                assert(instance_ != nullptr);

                return *instance_;
            }

            static Window& instance(int argc, char** argv, const char* name, int width, int height)
            {
                if(!instance_)
                {
                    glutInit(&argc, argv);
                    instance_ = new Window(name, width, height);
                }

                return *instance_;
            }

            static bool isKeyPressed(unsigned char key);
            static bool isKeyPressed(const string& key);
            static bool isMouseButtonPressed(int button);
            static void getMousePosition(int& x, int& y);

        private:
            int window;
            const char* name;
            int width, height;

        public:
            ~Window();

            void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f) const;

            void run() const;

            bool closed() const;

            void update(void (*func)());
            void render(void (*func)());
            void reshape(void (func)(int, int));
            void timer(void (*func)(int));

            inline const unsigned char* getVersion() const { return glGetString(GL_VERSION); }
            inline const unsigned char* getGLSLVersion() const { return glGetString(GL_SHADING_LANGUAGE_VERSION); }

            inline int getWidth() const { return width;  }
            inline int getHeight()const { return height; }
            inline void setWidth(int w) { width = w; }
            inline void setHeight(int h) { height = h; }

            inline void draw() { glutSwapBuffers(); }

        private:
            Window(const char* name, int width, int height);
            Window() = default;
            void init();

            friend GLvoid keyboardDownCallback(unsigned char key, int x, int y);
            friend GLvoid keyboardUpCallback(unsigned char key, int x, int y);
            friend GLvoid specialKeyboardUpCallback(int key, int x, int y);
            friend GLvoid specialKeyboardDownCallback(int key, int x, int y);
            friend GLvoid mouseCallback(int button, int state, int x, int y);
            friend GLvoid mouseMoveCallback(int x, int y);
        };
    }
}
#endif //ADUNGL_WINDOW_H
