#include "mesh_factory.h"

namespace AdunGL
{
	namespace graphics
	{
		AdunGL::graphics::VertexArray* AdunGL::graphics::MeshFactory::createQuad(float x, float y, float width, float height)
		{
			AdunGL::graphics::VertexData data[4];

			data[0].vertex = maths::vec3(x, y, 0);
			data[0].uv = maths::vec2(0, 1);

			data[1].vertex = maths::vec3(x, y + height, 0);
			data[1].uv = maths::vec2(0, 0);

			data[2].vertex = maths::vec3(x + width, y + height, 0);
			data[2].uv = maths::vec2(1, 0);

			data[3].vertex = maths::vec3(x + width, y, 0);
			data[3].uv = maths::vec2(1, 1);

			Buffer* buffer = new Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
			buffer->bind();
			buffer->setData(RENDERER_VERTEX_SIZE * 4, data);

			buffer->layout.push<maths::vec3>("position");
			buffer->layout.push<maths::vec2>("uv");
			buffer->layout.push<maths::vec2>("mask_uv");
			buffer->layout.push<float>("tid");
			buffer->layout.push<float>("mid");
			buffer->layout.push<unsigned char>("color", 4, true);
			
			VertexArray* result = new VertexArray();
			result->bind();
			result->pushBuffer(buffer);

			return result;
		}

		AdunGL::graphics::VertexArray* AdunGL::graphics::MeshFactory::createQuad(const maths::vec2& position, const maths::vec2& size)
		{
			return createQuad(position.x, position.y, size.x, size.y);
		}

		

	}
}
