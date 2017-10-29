//
// Created by adun on 2017. 10. 30..
//

#ifndef ADUNGL_SHADER_H
#define ADUNGL_SHADER_H

#include <iostream>
#include <vector>
#include <GL/glut.h>

#include "../utils/fileutils.h"

namespace AdunGL
{
    namespace graphics
    {
        using namespace AdunGL::utils;

        class Shader
        {
        private:
            GLuint shaderID;
            const char* vertPath, * fragPath;

        public:
            Shader(const char* vertPath, const char* fragPath);
            ~Shader();

            void enable() const;
            void disable() const;

        private:
            GLuint load();
        };
    }
}
#endif //ADUNGL_SHADER_H
