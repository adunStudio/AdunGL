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
			GLuint arrayID;
			std::vector<Buffer* > buffers;

		public:
			VertexArray();
			~VertexArray();

			void addBuffer(Buffer* buffer, GLuint index);

			void bind() const;
			void unbind() const;

			void draw(GLuint count) const;
		};

	}
}
