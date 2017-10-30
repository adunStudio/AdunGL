//
// Created by adun on 2017. 10. 30..
//

#include "shader.h"

namespace AdunGL
{
    namespace graphics
    {


        Shader::Shader(const char* vertPath, const char* fragPath)
        : vertPath(vertPath), fragPath(fragPath)
        {
            shaderID = load();
        }

        Shader::~Shader()
        {
            glDeleteShader(shaderID);
        }

        GLuint Shader::load()
        {
            GLuint program = glCreateProgram();
            GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
            GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

            /* Read */
            std::string vertSourceString = FileUtils::read_file(vertPath);
            std::string fragSourceString = FileUtils::read_file(fragPath);

            const char* vertSource = vertSourceString.c_str();
            const char* fragSource = fragSourceString.c_str();

            GLint result;


            /* Vertex */
            glShaderSource(vertex, 1, &vertSource, NULL);
            glCompileShader(vertex);

            glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

            if(result == GL_FALSE)
            {
                GLint length;

                glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);

                std::vector<char> error(length);

                glGetShaderInfoLog(vertex, length, &length, &error[0]);

                std::cout << "Failed to vertex shader compile! " << std::endl << &error[0] << std::endl;

                glDeleteShader(vertex);

                return 0;
            }


            /* Fragment */
            glShaderSource(fragment, 1, &fragSource, NULL);
            glCompileShader(fragment);

            glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

            if(result == GL_FALSE)
            {

                GLint length;

                glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);

                std::vector<char> error(length);

                glGetShaderInfoLog(fragment, length, &length, &error[0]);

                std::cout << "Failed to fragment shader compile! " << std::endl << &error[0] << std::endl;

                glDeleteShader(fragment);

                return 0;
            }


            /* Attach */
            glAttachShader(program, vertex);
            glAttachShader(program, fragment);

            glLinkProgram(program);
            glValidateProgram(program);

            glDeleteShader(vertex);
            glDeleteShader(fragment);

            return program;
        }

        void Shader::enable() const
        {
            glUseProgram(shaderID);
        }

        void Shader::disable() const
        {
           glUseProgram(0);
        }

    }
}