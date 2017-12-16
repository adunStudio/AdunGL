#pragma once

#include <string>

using namespace std;

namespace AdunGL
{
	namespace graphics
	{
		class ShaderUniformDeclaration
		{
		public:
			enum class Type
			{
				NONE, FLOAT32, INT32, VEC2, VEC3, VEC4, MAT3, MAT4, SAMPLER2D
			};

		private:
			friend class Shader;

			Type   m_type;
			string m_name;
			GLuint m_size;
			GLuint m_count;
			GLuint m_offset;

			const Shader* m_shader;
			mutable int m_location;

		public:
			ShaderUniformDeclaration(Type type, const string& name, const Shader* shader, GLuint count = 1);

			GLuint getSize() const;
			int    getLocation() const;

			inline int getOffset() const { return m_offset;  }
			inline const string& getName() const { return m_name;  }
			inline Type getType() const { return m_type;  }

		private:
			GLuint sizeOfUniformType(Type type);
		};
	}
}