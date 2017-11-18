//
// Created by adun on 2017. 10. 30..
//

#ifndef ADUNGL_SHADER_H
#define ADUNGL_SHADER_H

#include <iostream>
#include <vector>
#include <GLUT/glut.h>
#include "../utils/fileutils.h"
#include "../maths/maths.h"

namespace AdunGL
{
    namespace graphics
    {
        using namespace AdunGL::utils;

        class Shader
        {
        private:
            const char* vertPath, * fragPath;

        public:
            GLuint shaderID;

            Shader(const char* vertPath, const char* fragPath);
            ~Shader();

            void setUniform1f(const GLchar* name, float value);
            void setUniform1i(const GLchar* name, int value);
            void setUniform2f(const GLchar* name, const maths::vec2& vector);
            void setUniform3f(const GLchar* name, const maths::vec3& vector);
            void setUniform4f(const GLchar* name, const maths::vec4& vector);
            void setUniformMat4(const GLchar* name, const maths::mat4& matrix);

            void enable() const;
            void disable() const;

        private:
            GLuint load();
            GLint getUniformLocation(const GLchar* name);
        };
    }
}
#endif //ADUNGL_SHADER_H
