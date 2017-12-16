#pragma once

//
// Created by adun on 2017. 10. 30..
//


#include <iostream>
#include <vector>
#include <string>
#include <GL/freeglut.h>
#include "../../utils/fileutils.h"
#include "../../maths/maths.h"
#include "../../utils/log.h"
#include "../../utils/stringutils.h"
#include "shader_uniform.h"

namespace AdunGL
{
	namespace graphics
	{

#define SHADER_VERTEX_INDEX   0
#define SHADER_UV_INDEX       1
#define SHADER_MASK_UV_INDEX  2
#define SHADER_TID_INDEX      3
#define SHADER_MID_INDEX      4
#define SHADER_COLOR_INDEX    5

		using namespace std;
		using namespace AdunGL::utils;

		class Shader
		{

		private:
			enum class ShaderType
			{
				UNKNOWN,
				VERTEX,
				FRAGMENT
			};

		private:
			string m_name;
			string m_path;
			string m_source;
			string m_vertexSource;
			string m_fragmentSource;
			GLuint m_shaderID;

			vector<ShaderUniformDeclaration*> m_uniforms;

		public:

			Shader(const string& name, const string& source);
			~Shader();

			void setUniform1f  (const string& name, float value);
			void setUniform1fv (const string& name, float* value, int count);
			void setUniform1i  (const string& name, int value);
			void setUniform1iv (const string& name, int* value, int count);
			void setUniform2f  (const string& name, const maths::vec2& vector);
			void setUniform3f  (const string& name, const maths::vec3& vector);
			void setUniform4f  (const string& name, const maths::vec4& vector);
			void setUniformMat4(const string& name, const maths::mat4& matrix);

			void resolveAndSetUniforms(unsigned char* data, GLuint size);

			void enable() const;
			void disable() const;

			inline const vector<ShaderUniformDeclaration*> getUniformDeclarations() const { return m_uniforms; }

		private:
			void preProcess(const string& source, string** shaders);
			void parseUniforms(const std::vector<string>& lines);
			ShaderUniformDeclaration::Type getUniformTypeFromString(const string& token);
			void resolveUniforms();
			GLuint load(const string& vertSrc, const string& fragSrc);
			GLint getUniformLocation(const string& name);

			void resolveAndSetUniform(ShaderUniformDeclaration* uniform, unsigned char* data);

			void setUniform1f(GLuint location, float value);
			void setUniform1fv(GLuint location, float* value, int count);
			void setUniform1i(GLuint location, int value);
			void setUniform1iv(GLuint location, int* value, int count);
			void setUniform2f(GLuint location, const maths::vec2& vector);
			void setUniform3f(GLuint location, const maths::vec3& vector);
			void setUniform4f(GLuint location, const maths::vec4& vector);
			void setUniformMat4(GLuint location, const maths::mat4& matrix);


		public:
			static Shader* FromFile(const string& name, const string& filepath);
			static Shader* FromSource(const string& name, const string& source);
		};
	}
}