//
// Created by adun on 2017. 10. 29..
//

#ifndef ADUNGL_WINDOW_H
#define ADUNGL_WINDOW_H

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <cassert>

using namespace std;

namespace AdunGL
{
    namespace graphics
    {
        class Window
        {
        private:
            static Window* instance_;

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

        private:
            int window;
            const char* name;
            int width, height;

        public:
            ~Window();

            void clear() const;

            GLvoid update() const;

            GLvoid render() const;
            GLvoid reshape(int w, int h);

            void run() const;

            bool closed() const;

            inline const unsigned char* getVersion() const { return glGetString(GL_VERSION); }

            inline int getWidth() const { return width;  }
            inline int getHeight()const { return height; }

        private:
            Window(const char* name, int width, int height);
            Window() = default;

            void init();

            static GLvoid updateCallback()
            {
                instance_->update();
            }

            static GLvoid renderCallback()
            {
                instance_->render();
            }

            static GLvoid reshapeCallback(int w, int h)
            {
                instance_->reshape(w, h);
            }
        };
    }
}
#endif //ADUNGL_WINDOW_H
