#pragma once
//
// Created by adun on 2017. 11. 5..
//

#include <GL/freeglut.h>

namespace AdunGL
{
	namespace graphics
	{
		class Buffer
		{
		private:
			GLuint bufferID;
			GLuint componentCount;

		public:
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			~Buffer();

			void bind() const;
			void unbind() const;

			inline GLuint getComponentCount() const { return componentCount; }
		};
	}
}

