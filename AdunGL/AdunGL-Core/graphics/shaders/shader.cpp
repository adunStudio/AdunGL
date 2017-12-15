//
// Created by adun on 2017. 10. 30..
//

#include "shader.h"

namespace AdunGL
{
	namespace graphics
	{


		Shader::Shader(const char* name, const char* vertSrc, const char* fragSrc)
			: m_name(name), m_vertSrc(vertSrc), m_fragSrc(fragSrc)
		{
			m_shaderID = load(m_vertSrc, m_fragSrc);
		}

		Shader::Shader(const char* vertPath, const char* fragPath)
			: vertPath(vertPath), fragPath(fragPath)
		{
			std::string vertSourceString = FileUtils::read_file(vertPath);
			std::string fragSourceString = FileUtils::read_file(fragPath);

			m_vertSrc = vertSourceString.c_str();
			m_fragSrc = fragSourceString.c_str();

			m_shaderID = load(m_vertSrc, m_fragSrc);
		}

		Shader* Shader::FromFile(const char* vertPath, const char* fragPath)
		{
			return new Shader(vertPath, fragPath);
		}

		Shader* Shader::FromSource(const char* vertSrc, const char* fragSrc)
		{
			return new Shader(vertSrc, vertSrc, fragSrc);
		}
		Shader* Shader::FromSource(const char* name, const char* vertSrc, const char* fragSrc)
		{
			return new Shader(name, vertSrc, fragSrc);
		}


		Shader::~Shader()
		{
			glDeleteShader(m_shaderID);
		}

		GLuint Shader::load(const char* vertSrc, const char* fragSrc)
		{
			/*
			* ���α׷�(���̴��� ����) �����̳ʸ� ���� ��ü�� �����Ѵ�.
			* �� �Լ��� �����̳ʿ� ���� �ڵ��� ��ȯ�Ѵ�.
			* GLuint glCreateProgram(void);
			*/
			GLuint program = glCreateProgram();

			/*
			* ���̴� �����̳ʷν� �����ϴ� ������Ʈ(���̴� �ڵ�)�� ��ȯ�Ѵ�.
			* �� �Լ��� ���̴��� �ڵ��� ��ȯ�Ѵ�.
			* GLuint glCreateShader(GLenum shaderType);
			* Parameter:
			* shaderType - GL_VERTEX_SHADER �Ǵ� GL_FRAGMENT_SHADER
			*/
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			GLint result;


			/* Vertex */

			/*
			* Ư���� �ҽ� �ڵ带 �߰��Ѵ�. �ҽ��ڵ�� ���� �迭�̴�.
			* void glShaderSource(GLuint shader, int numOfString. const char** strings, int *lenOfStrings);
			* Parameters:
			* shader - ���̴��� �ڵ�
			* numOfStrings - ���� �迭�� ���� ��� ��
			* strings - ���� �迭
			* lenOfStrings - �� ���ڿ��� ���̸� ������ �迭 �Ǵ� NUL��(���ڿ����� NULL�� ����)
			*/
			glShaderSource(vertex, 1, &vertSrc, NULL);

			/*
			* ���̴� �ڵ带 �������Ѵ�.
			* void glCompileShader(GLuint shader);
			* Parameters:
			* shader - ���̴��� �ڵ�
			*/
			glCompileShader(vertex);

			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE)
			{
				GLint length;

				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);

				std::vector<char> error(length);

				glGetShaderInfoLog(vertex, length, &length, &error[0]);

				ADUNGL_ERROR("[shader.cpp 86] Failed to compile vertex shader!", NULL);
				ADUNGL_FATAL("%s", &error[0]);

				glDeleteShader(vertex);

				return 0;
			}


			/* Fragment */
			glShaderSource(fragment, 1, &fragSrc, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE)
			{

				GLint length;

				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);

				std::vector<char> error(length);

				glGetShaderInfoLog(fragment, length, &length, &error[0]);

				ADUNGL_ERROR("[shader.cpp 112] Failed to compile fragment shader!", NULL);
				ADUNGL_FATAL("%s", &error[0]);

				glDeleteShader(fragment);

				return 0;
			}



			/* Attach */

			/*
			* ������ ���̴��� ���α׷� �����̳ʿ� ���δ�.
			* void glAttachShader(GLuint program, GLuint shader);
			* Parameters:
			* Program - ���α׷� �����̳� �ڵ�
			* shader - ���α׷� �����̳ʿ� ���̰��� �ϴ� ���̴��� �ڵ�
			*/
			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glBindAttribLocation(program, 0, "position");
			glBindAttribLocation(program, 1, "uv");
			glBindAttribLocation(program, 2, "mask_uv");
			glBindAttribLocation(program, 3, "tid");
			glBindAttribLocation(program, 4, "mid");
			glBindAttribLocation(program, 5, "color");

			glBindFragDataLocation(program, 0, "color");
			/*
			* ���α׷��� ��ũ�Ѵ�. �� �ܰ踦 �����ϱ� ���ؼ� ���̴��� �ݵ�� ������ �Ǿ��־���Ѵ�.
			* void glLinkProgram(GLuint program);
			* Parameters:
			* program - ���α׷� �����̳��� �ڵ�
			*/
			glLinkProgram(program);

			glValidateProgram(program);

			GLint a = glGetAttribLocation(program, "position");
			GLint b = glGetAttribLocation(program, "uv");
			GLint c = glGetAttribLocation(program, "mask_uv");
			GLint d = glGetAttribLocation(program, "tid");
			GLint e = glGetAttribLocation(program, "mid");
			GLint f = glGetAttribLocation(program, "color");

			ADUNGL_INFO("[shader.cpp 152] : Attribute Location: position(%d), uv(%d), mask_uv(%d), tid(%d), mid(%d) color(%d)", a, b, c, d, e, f);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		GLint Shader::getUniformLocation(const GLchar* name)
		{
			return glGetUniformLocation(m_shaderID, name);
		}

		void Shader::setUniform1f(const GLchar* name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform1fv(const GLchar* name, float* value, int count)
		{
			glUniform1fv(getUniformLocation(name), count, value);
		}

		void Shader::setUniform1i(const GLchar* name, int value)
		{
			glUniform1i(getUniformLocation(name), value);

		}

		void Shader::setUniform1iv(const GLchar* name, int* value, int count)
		{
			glUniform1iv(getUniformLocation(name), count, value);
		}

		void Shader::setUniform2f(const GLchar* name, const maths::vec2& vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::setUniform3f(const GLchar* name, const maths::vec3& vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniform4f(const GLchar* name, const maths::vec4& vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}

		void Shader::enable() const
		{
			glUseProgram(m_shaderID);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}

	}
}