#include "shader_uniform.h"
#include "shader.h"

namespace AdunGL
{
	namespace graphics
	{
		ShaderUniformDeclaration::ShaderUniformDeclaration(Type type, const string& name, const Shader* shader, GLuint count)
			: m_type(type), m_name(name), m_shader(shader), m_count(count)
		{
			m_size = sizeOfUniformType(type) * count;
		}

		GLuint ShaderUniformDeclaration::getSize() const
		{
			return m_size;
		}

		int ShaderUniformDeclaration::getLocation() const
		{
			return m_location;
		}

		GLuint ShaderUniformDeclaration::sizeOfUniformType(Type type)
		{
			switch (type)
			{
				case ShaderUniformDeclaration::Type::FLOAT32:	return 4;
				case ShaderUniformDeclaration::Type::INT32:		return 4;
				case ShaderUniformDeclaration::Type::VEC2:		return 4 * 2;
				case ShaderUniformDeclaration::Type::VEC3:		return 4 * 3;
				case ShaderUniformDeclaration::Type::VEC4:		return 4 * 4;
				case ShaderUniformDeclaration::Type::MAT3:		return 4 * 3 * 3;
				case ShaderUniformDeclaration::Type::MAT4:		return 4 * 4 * 4;
				case ShaderUniformDeclaration::Type::SAMPLER2D:	return 4;
			}

			return 0;
		}
	}
}