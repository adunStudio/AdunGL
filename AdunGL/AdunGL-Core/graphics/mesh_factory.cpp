#include "mesh_factory.h"
#define ADUNGL_VERTEX_ARRAYS 1

namespace AdunGL
{
	namespace graphcis
	{
		namespace MeshFactory
		{
			GLuint createQuad(float x, float y, float width, float height)
			{
				GLuint result;
				GLuint buffer;

				AdunGL::graphics::VertexData data[4];

				data[0].vertex = maths::vec3(x, y, 0);
				data[0].uv = maths::vec2(0, 1);

				data[1].vertex = maths::vec3(x, y + height, 0);
				data[1].uv = maths::vec2(0, 0);

				data[2].vertex = maths::vec3(x + width, y + height, 0);
				data[2].uv = maths::vec2(1, 0);

				data[3].vertex = maths::vec3(x + width, y, 0);
				data[3].uv = maths::vec2(1, 1);

				glGenVertexArrays(1, &result);
				glGenBuffers(1, &buffer);

				glBindVertexArray(result);
				glBindBuffer(GL_ARRAY_BUFFER, buffer);

				glBufferData(GL_ARRAY_BUFFER, RENDERER_VERTEX_SIZE * 4, data, GL_STATIC_DRAW);

				glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
				glEnableVertexAttribArray(SHADER_UV_INDEX);
				glEnableVertexAttribArray(SHADER_MASK_UV_INDEX);
				glEnableVertexAttribArray(SHADER_TID_INDEX);
				glEnableVertexAttribArray(SHADER_MID_INDEX);
				glEnableVertexAttribArray(SHADER_COLOR_INDEX);

				glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(0));
				glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(AdunGL::graphics::VertexData, uv)));
				glVertexAttribPointer(SHADER_MASK_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(AdunGL::graphics::VertexData, mask_uv)));
				glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(AdunGL::graphics::VertexData, tid)));
				glVertexAttribPointer(SHADER_MID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(AdunGL::graphics::VertexData, mid)));
				glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(AdunGL::graphics::VertexData, color)));
			
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				return result;
			}

			GLuint createQuad(const maths::vec2& position, const maths::vec2& size)
			{
				return createQuad(position.x, position.y, size.x, size.y);
			}
		}
	}
}