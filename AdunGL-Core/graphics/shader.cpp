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
            /*
             * 프로그램(쉐이더에 대한) 컨테이너를 위한 객체를 생성한다.
             * 이 함수는 컨테이너에 대한 핸들을 반환한다.
             * GLuint glCreateProgram(void);
             */
            GLuint program = glCreateProgram();

            /*
             * 쉐이더 컨테이너로써 수행하는 오브젝트(쉐이더 핸들)를 반환한다.
             * 이 함수는 쉐이더의 핸들을 반환한다.
             * GLuint glCreateShader(GLenum shaderType);
             * Parameter:
             * shaderType - GL_VERTEX_SHADER 또는 GL_FRAGMENT_SHADER
             */
            GLuint vertex   = glCreateShader(GL_VERTEX_SHADER);
            GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

            /* Read */
            std::string vertSourceString = FileUtils::read_file(vertPath);
            std::string fragSourceString = FileUtils::read_file(fragPath);

            const char* vertSource = vertSourceString.c_str();
            const char* fragSource = fragSourceString.c_str();

            GLint result;


            /* Vertex */

            /*
             * 특정한 소스 코드를 추가한다. 소스코드는 문자 배열이다.
             * void glShaderSource(GLuint shader, int numOfString. const char** strings, int *lenOfStrings);
             * Parameters:
             * shader - 쉐이더의 핸들
             * numOfStrings - 문자 배열의 구성 요소 수
             * strings - 문자 배열
             * lenOfStrings - 각 문자열의 길이를 가지는 배열 또는 NUL값(문자열들이 NULL로 끝남)
             */
            glShaderSource(vertex, 1, &vertSource, NULL);

            /*
             * 쉐이더 코드를 컴파일한다.
             * void glCompileShader(GLuint shader);
             * Parameters:
             * shader - 쉐이더의 핸들
             */
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

            /*
             * 생성한 쉐이더를 프로그램 컨테이너에 붙인다.
             * void glAttachShader(GLuint program, GLuint shader);
             * Parameters:
             * Program - 프로그램 컨테이너 핸들
             * shader - 프로그램 컨테이너에 붙이고자 하는 쉐이더의 핸들
             */
            glAttachShader(program, vertex);
            glAttachShader(program, fragment);

            glBindAttribLocation(program, 0, "position");
            glBindAttribLocation(program, 1, "coloror");

            /*
             * 프로그램을 링크한다. 이 단계를 수행하기 위해서 쉐이더는 반드시 컴파일 되어있어야한다.
             * void glLinkProgram(GLuint program);
             * Parameters:
             * program - 프로그램 컨테이너의 핸들
             */
            glLinkProgram(program);

            glValidateProgram(program);




            //GLint a = glGetAttribLocation(program, "position");
            //GLint b = glGetAttribLocation(program, "coloror");


            glDeleteShader(vertex);
            glDeleteShader(fragment);

            return program;
        }

        GLint Shader::getUniformLocation(const GLchar* name)
        {
            return glGetUniformLocation(shaderID, name);
        }

        void Shader::setUniform1f(const GLchar* name, float value)
        {
            glUniform1f(getUniformLocation(name), value);
        }

        void Shader::setUniform1i(const GLchar* name, int value)
        {
            glUniform1i(getUniformLocation(name), value);

        }

        void Shader::setUniform2f(const GLchar* name, const maths::vec2& vector)
        {
            glUniform2f(getUniformLocation(name), vector.x, vector.y);
        }

        void Shader::setUniform3f(const GLchar* name, const maths::vec3& vector)
        {
            glUniform3f(getUniformLocation(name), vector.x , vector.y, vector.z);
        }

        void Shader::setUniform4f(const GLchar* name, const maths::vec4& vector)
        {
            glUniform4f(getUniformLocation(name), vector.x , vector.y, vector.z, vector.w);
        }

        void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix)
        {
            glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
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