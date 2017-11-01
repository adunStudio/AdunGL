//
// Created by adun on 2017. 10. 29..
//

#ifndef ADUNGL_WINDOW_H
#define ADUNGL_WINDOW_H

#include <iostream>
#include <GL/freeglut.h>

#include <cassert>

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

            static double mx, my;

        public:
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
            static bool isMouseButtonPressed(int button);
            static void getMousePosition(int& x, int& y);

        private:
            int window;
            const char* name;
            int width, height;

        public:
            ~Window();

            void clear() const;

            void run() const;

            bool closed() const;

            void update(void (*func)());
            void render(void (*func)());

            inline const unsigned char* getVersion() const { return glGetString(GL_VERSION); }

            inline int getWidth() const { return width;  }
            inline int getHeight()const { return height; }

        private:
            Window(const char* name, int width, int height);
            Window() = default;
            void init();


            //friend GLvoid updateCallback();
            //friend GLvoid renderCallback();
            friend GLvoid reshapeCallback(int w, int h);
            friend GLvoid keyboardDownCallback(unsigned char key, int x, int y);
            friend GLvoid keyboardUpCallback(unsigned char key, int x, int y);
            friend GLvoid specialKeyboardCallback(int key, int x, int y);
            friend GLvoid mouseCallback(int button, int state, int x, int y);
            friend GLvoid mouseMoveCallback(int x, int y);
        };
    }
}
#endif //ADUNGL_WINDOW_H
