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

		AdunGL::graphics::Mesh* AdunGL::graphics::MeshFactory::createCube(float size, MaterialInstance* material)
		{
			using namespace maths;

			Vertex data[8];

			memset(data, 0, 8 * sizeof(Vertex));

			data[0].position = vec3(-size / 2.0f, -size / 2.0f, size / 2.0f);
			data[1].position = vec3(size / 2.0f, -size / 2.0f, size / 2.0f);
			data[2].position = vec3(size / 2.0f, size / 2.0f, size / 2.0f);
			data[3].position = vec3(-size / 2.0f, size / 2.0f, size / 2.0f);
			data[4].position = vec3(-size / 2.0f, -size / 2.0f, -size / 2.0f);
			data[5].position = vec3(size / 2.0f, -size / 2.0f, -size / 2.0f);
			data[6].position = vec3(size / 2.0f, size / 2.0f, -size / 2.0f);
			data[7].position = vec3(-size / 2.0f, size / 2.0f, -size / 2.0f);

			data[0].normal = vec3(-1.0f, -1.0f, 1.0f);
			data[1].normal = vec3(1.0f, -1.0f, 1.0f);
			data[2].normal = vec3(1.0f, 1.0f, 1.0f);
			data[3].normal = vec3(-1.0f, 1.0f, 1.0f);
			data[4].normal = vec3(-1.0f, -1.0f, -1.0f);
			data[5].normal = vec3(1.0f, -1.0f, -1.0f);
			data[6].normal = vec3(1.0f, 1.0f, -1.0f);
			data[7].normal = vec3(-1.0f, 1.0f, -1.0f);

			Buffer* buffer = new Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
			buffer->bind();
			buffer->setData(8 * sizeof(Vertex), data);

			buffer->layout.push<vec3>("position");
			buffer->layout.push<vec3>("normal");
			buffer->layout.push<vec2>("uv");

			VertexArray* va = new VertexArray();
			va->bind();
			va->pushBuffer(buffer);

			GLuint* indices = new GLuint[36]
			{
				0, 1, 2, 2, 3, 0,
				3, 2, 6, 6, 7, 3,
				7, 6, 5, 5, 4, 7,
				4, 0, 3, 3, 7, 4,
				0, 1, 5, 5, 4, 0,
				1, 5, 6, 6, 2, 1
			};

			IndexBuffer* ib = new IndexBuffer(indices, 36);

			return new Mesh(va, ib, material);

		}


	}
}
