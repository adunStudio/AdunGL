//
// Created by adun on 2017. 10. 29..
//

#ifndef ADUNGL_WINDOW_H
#define ADUNGL_WINDOW_H

#include <iostream>
#include "../opengl.h"
#include <cassert>
#include <map>
#include <functional>
#include "font_manager.h"

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
            static bool keys[MAX_KEYS];
            static bool mouseButtons[MAX_BUTTONS];
            static map<string, bool> keyMaps;


            static double mx, my;


        public:
            static bool isKeyPressed(unsigned char key);
            static bool isKeyPressed(const string& key);
            static bool isMouseButtonPressed(int button);
            static void getMousePosition(int& x, int& y);

        private:
            int window;
            const char* name;
            int width, height;

        public:
            Window(const char* name, int width, int height);

            ~Window();

            void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f) const;

            bool closed() const;

            void update();
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
            Window() = default;
            void init();

            friend GLvoid keyboardDownCallback(unsigned char key, int x, int y);
            friend GLvoid keyboardUpCallback(unsigned char key, int x, int y);
            friend GLvoid specialKeyboardUpCallback(int key, int x, int y);
            friend GLvoid specialKeyboardDownCallback(int key, int x, int y);
            friend GLvoid mouseCallback(int button, int state, int x, int y);
            friend GLvoid mouseMoveCallback(int x, int y);
            friend GLvoid renderCallback();
        };
    }
}
#endif //ADUNGL_WINDOW_H
