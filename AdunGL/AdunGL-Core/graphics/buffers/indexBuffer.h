#pragma once
//
// Created by adun on 2017. 11. 5..
//

#include <GL/freeglut.h>
#include "buffer.h"
namespace AdunGL
{
	namespace graphics
	{
		class IndexBuffer
		{
		private:
			Buffer* m_buffer;
			GLuint  m_count;

		public:
			IndexBuffer(GLushort* data, GLsizei count);
			IndexBuffer(GLuint*   data, GLsizei count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline GLuint getCount() const { return m_count; }
		};
	}
}