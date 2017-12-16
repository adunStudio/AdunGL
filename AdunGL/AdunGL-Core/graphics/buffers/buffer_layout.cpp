#include "buffer_layout.h"

namespace AdunGL
{
	namespace graphics
	{
		BufferLayout::BufferLayout()
		{
		}

		void BufferLayout::push(const string& name, GLuint type, GLuint size, GLuint count, bool normalized)
		{
			m_layout.push_back({ name, type, size, count, 0, normalized });
			BufferLayoutType& layoutType = m_layout.back();
			if (m_layout.size() > 1)
				layoutType.offset = m_layout[m_layout.size() - 2].offset + m_layout[m_layout.size() - 2].size;

			m_size = layoutType.offset + layoutType.size;
		}
	}
}