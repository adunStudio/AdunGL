#pragma once
//
// Created by adun on 2017. 11. 5..
//

#include <GL/freeglut.h>
#include <vector>
#include "buffer.h"

namespace AdunGL
{
	namespace graphics
	{
		class VertexArray
		{
		private:
			static GLuint s_currentBinding;

		private:
			GLuint arrayID;
			std::vector<Buffer* > m_buffers;

		public:
			VertexArray();
			~VertexArray();

			Buffer* getBuffer(GLuint index = 0);

			void pushBuffer(Buffer* buffer);
			void bind() const;
			void unbind() const;

			void draw(GLuint count) const;
		};

	}
}
