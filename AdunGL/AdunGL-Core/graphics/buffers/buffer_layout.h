#pragma once

#include <vector>
#include "../../maths/maths.h"
#include <GL/freeglut.h>
#include <string>

using namespace std;

namespace AdunGL
{
	namespace graphics
	{
		struct BufferLayoutType
		{
			string name;
			GLuint type;
			GLuint size;
			GLuint count;
			GLuint offset;
			bool normalized;
		};

		class BufferLayout
		{
		private:
			GLuint m_size;
			vector<BufferLayoutType> m_layout;

		public:
			BufferLayout();

			template<typename T>
			void push(const string& name, GLuint count = 1, bool normalized = false)
			{

			};

			template<> void push<float>(const string& name, GLuint count, bool normalized) { push(name, GL_FLOAT, sizeof(float) * count, count, normalized); }
			template<> void push<GLuint>(const string& name, GLuint count, bool normalized) { push(name, GL_UNSIGNED_INT, sizeof(GLuint) * count, count, normalized); }
			template<> void push<unsigned char>(const string& name, GLuint count, bool normalized) { push(name, GL_UNSIGNED_BYTE, sizeof(unsigned char) * count, count, normalized); }
			template<> void push<maths::vec2>(const string& name, GLuint count, bool normalized) { push(name, GL_FLOAT, sizeof(maths::vec2) * count, 2 * count, normalized); }
			template<> void push<maths::vec3>(const string& name, GLuint count, bool normalized) { push(name, GL_FLOAT, sizeof(maths::vec3) * count, 3 * count, normalized); }
			template<> void push<maths::vec4>(const string& name, GLuint count, bool normalized) { push(name, GL_FLOAT, sizeof(maths::vec4) * count, 4 * count, normalized); }

			inline const std::vector<BufferLayoutType>& getLayout() const { return m_layout; }
			inline GLuint getStride() const { return m_size; }

		private:
			void push(const string& name, GLuint type, GLuint size, GLuint count, bool normalized);

		};
	}
}