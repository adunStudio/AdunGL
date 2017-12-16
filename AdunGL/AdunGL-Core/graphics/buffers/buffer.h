#pragma once
//
// Created by adun on 2017. 11. 5..
//

#include <GL/freeglut.h>
#include "../api/render_api.h"
#include "buffer_layout.h"

namespace AdunGL
{
	namespace graphics
	{

		struct Buffer
		{
			GLuint id;
			GLuint target, usage;
			GLuint size;

			BufferLayout layout;

			Buffer(GLuint target, GLuint usage);
			~Buffer();

			void resize(GLuint size);
			void setData(GLuint size, const void* data);

			template<typename T>
			T* getPointer(GLuint flags = GL_WRITE_ONLY)
			{
				return (T*)API::GetBufferPointer(target, flags);
			}

			void releasePointer();
			
			void bind();
			void unbind();
		};
	}
}

