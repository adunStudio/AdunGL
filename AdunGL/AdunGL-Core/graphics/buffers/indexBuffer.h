#pragma once
//
// Created by adun on 2017. 11. 5..
//

#include <GL/freeglut.h>

namespace AdunGL
{
	namespace graphics
	{
		class IndexBuffer
		{
		private:
			GLuint bufferID;
			GLuint count;

		public:
			IndexBuffer(GLushort* data, GLsizei count);
			IndexBuffer(GLuint*   data, GLsizei count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline GLuint getCount() const { return count; }
		};
	}
}