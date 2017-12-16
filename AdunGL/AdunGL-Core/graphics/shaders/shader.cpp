//
// Created by adun on 2017. 10. 30..
//

#include "shader.h"

namespace AdunGL
{
	namespace graphics
	{


		Shader::Shader(const string& name, const string& source)
			: m_name(name), m_source(source)
		{
			string** shaders = new string*[2];
			shaders[0] = &m_vertexSource;
			shaders[1] = &m_fragmentSource;

			preProcess(source, shaders);
			m_shaderID = load(m_vertexSource, m_fragmentSource);
			resolveUniforms();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_shaderID);
		}

		Shader* Shader::FromFile(const string& name, const string& filepath)
		{
			string shader = FileUtils::read_file(filepath);

			return new Shader(name, shader);
		}

		Shader* Shader::FromSource(const string& name, const string& source)
		{
			return new Shader(name, source);
		}

		GLuint Shader::load(const string& vertSrc, const string& fragSrc)
		{
			const char* vertexSource = vertSrc.c_str();
			const char* fragmentSource = fragSrc.c_str();

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
			glShaderSource(vertex, 1, &vertexSource, NULL);

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
			glShaderSource(fragment, 1, &fragmentSource, NULL);
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

		void Shader::preProcess(const string& source, string** shaders)
		{
			ShaderType type = ShaderType::UNKNOWN;

			std::vector<string> lines = utils::split_string(source, '\n');
			for (GLuint i = 0; i < lines.size(); i++)
			{
				const char* str = lines[i].c_str();
				if (strstr(str, "#shader"))
				{
					if (strstr(str, "vertex"))
						type = ShaderType::VERTEX;
					else if (strstr(str, "fragment"))
						type = ShaderType::FRAGMENT;
				}
				else if (type != ShaderType::UNKNOWN)
				{
					shaders[(int)type - 1]->append(str);
					shaders[(int)type - 1]->append("\n");
				}
			}
			parseUniforms(lines);
		}

		void Shader::parseUniforms(const std::vector<string>& lines)
		{
			for (GLuint i = 0; i < lines.size(); i++)
			{
				const char* str = lines[i].c_str();
				if (strstr(str, "uniform"))
				{
					std::vector<string> line = utils::split_string(str, ' ');
					for (GLuint i = 0; i < line.size(); i++)
					{
						// TODO: Precision
						string& token = line[i];
						ShaderUniformDeclaration::Type type = getUniformTypeFromString(token);
						if (type != ShaderUniformDeclaration::Type::NONE)
						{
							string& nextToken = line[i + 1];
							string name = nextToken;
							if (name[name.size() - 1] == ';')
								name = nextToken.substr(0, nextToken.size() - 1);

							GLuint count = 1;

							// Uniform arrays
							GLuint arrayToken = nextToken.find('[');
							if (arrayToken != string::npos)
							{
								name = name.substr(0, arrayToken - 1);
								GLuint arrayEnd = nextToken.find(']');
								count = atoi(nextToken.substr(arrayToken + 1, arrayEnd - arrayToken - 1).c_str());
							}

							ShaderUniformDeclaration* uniform = new ShaderUniformDeclaration(type, name, this, count);
							m_uniforms.push_back(uniform);
							break;
						}
					}
				}
			}
		}

		ShaderUniformDeclaration::Type Shader::getUniformTypeFromString(const string& token)
		{
			if (token == "float") return ShaderUniformDeclaration::Type::FLOAT32;
			if (token == "int") return ShaderUniformDeclaration::Type::INT32;
			if (token == "vec2") return ShaderUniformDeclaration::Type::VEC2;
			if (token == "vec3") return ShaderUniformDeclaration::Type::VEC3;
			if (token == "vec4") return ShaderUniformDeclaration::Type::VEC4;
			if (token == "mat3") return ShaderUniformDeclaration::Type::MAT3;
			if (token == "mat4") return ShaderUniformDeclaration::Type::MAT4;
			if (token == "sampler2D") return ShaderUniformDeclaration::Type::SAMPLER2D;

			return ShaderUniformDeclaration::Type::NONE;
		}

		void Shader::resolveUniforms()
		{
			GLuint offset = 0;
			for (GLuint i = 0; i < m_uniforms.size(); i++)
			{
				ShaderUniformDeclaration* uniform = m_uniforms[i];
				uniform->m_offset = offset;
				uniform->m_location = getUniformLocation(uniform->m_name);

				offset += uniform->getSize();
			}
		}

		GLint Shader::getUniformLocation(const string& name)
		{
			GLint result = glGetUniformLocation(m_shaderID, name.c_str());
			if (result == -1)
				ADUNGL_ERROR("%s: could not find uniform $s in shader!", m_name, name);

			return result;
		}
		

		void Shader::setUniform1f(const string& name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform1fv(const string& name, float* value, int count)
		{
			glUniform1fv(getUniformLocation(name), count, value);
		}

		void Shader::setUniform1i(const string& name, int value)
		{
			glUniform1i(getUniformLocation(name), value);

		}

		void Shader::setUniform1iv(const string& name, int* value, int count)
		{
			glUniform1iv(getUniformLocation(name), count, value);
		}

		void Shader::setUniform2f(const string& name, const maths::vec2& vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::setUniform3f(const string& name, const maths::vec3& vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniform4f(const string& name, const maths::vec4& vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::setUniformMat4(const string& name, const maths::mat4& matrix)
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

		void Shader::setUniform1f(GLuint location, float value)
		{
			glUniform1f(location, value);
		}

		void Shader::setUniform1fv(GLuint location, float* value, int count)
		{
			glUniform1fv(location, count, value);
		}

		void Shader::setUniform1i(GLuint location, int value)
		{
			glUniform1i(location, value);
		}

		void Shader::setUniform1iv(GLuint location, int* value, int count)
		{
			glUniform1iv(location, count, value);
		}

		void Shader::setUniform2f(GLuint location, const maths::vec2& vector)
		{
			glUniform2f(location, vector.x, vector.y);
		}

		void Shader::setUniform3f(GLuint location, const maths::vec3& vector)
		{
			glUniform3f(location, vector.x, vector.y, vector.z);
		}

		void Shader::setUniform4f(GLuint location, const maths::vec4& vector)
		{
			glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::setUniformMat4(GLuint location, const maths::mat4& matrix)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, matrix.elements);
		}

		void Shader::resolveAndSetUniforms(unsigned char* data, GLuint size)
		{
			const std::vector<ShaderUniformDeclaration*>& uniforms = m_uniforms;

			for (GLuint i = 0; i < uniforms.size(); i++)
				resolveAndSetUniform(uniforms[i], data);
		}

		void Shader::resolveAndSetUniform(ShaderUniformDeclaration* uniform, unsigned char* data)
		{
			switch (uniform->getType())
			{
			case ShaderUniformDeclaration::Type::FLOAT32:
				setUniform1f(uniform->getLocation(), *(float*)&data[uniform->getOffset()]);
				break;
			case ShaderUniformDeclaration::Type::SAMPLER2D:
			case ShaderUniformDeclaration::Type::INT32:
				setUniform1i(uniform->getLocation(), *(int*)&data[uniform->getOffset()]);
				break;
			case ShaderUniformDeclaration::Type::VEC2:
				setUniform2f(uniform->getLocation(), *(maths::vec2*)&data[uniform->getOffset()]);
				break;
			case ShaderUniformDeclaration::Type::VEC3:
				setUniform3f(uniform->getLocation(), *(maths::vec3*)&data[uniform->getOffset()]);
				break;
			case ShaderUniformDeclaration::Type::VEC4:
				setUniform4f(uniform->getLocation(), *(maths::vec4*)&data[uniform->getOffset()]);
				break;
			case ShaderUniformDeclaration::Type::MAT3:
				// TODO: SetUniformMat3(uniform->GetLocation(), *(maths::mat3*)&data[uniform->GetOffset()]);
				break;
			case ShaderUniformDeclaration::Type::MAT4:
				setUniformMat4(uniform->getLocation(), *(maths::mat4*)&data[uniform->getOffset()]);
				break;
			default:
				ADUNGL_ERROR("Unknown type!");
			}
		}
	}
}