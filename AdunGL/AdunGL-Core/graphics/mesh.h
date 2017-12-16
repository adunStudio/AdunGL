#pragma once

#include "buffers/vertexArray.h"
#include "buffers/indexBuffer.h"
#include "material.h"

namespace AdunGL
{
	namespace graphics
	{
		class Renderer3D;

		struct Vertex
		{
			maths::vec3 position;
			maths::vec3 normal;
			maths::vec2 uv;
		};

		class Mesh
		{
		private:
			VertexArray* m_vertexArray;
			IndexBuffer* m_indexBuffer;
			MaterialInstance* m_materialInstance;

		public:
			Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer, MaterialInstance* materialInstance);
			~Mesh();

			inline MaterialInstance* getMaterialInstance() const { return m_materialInstance;  }

			void render(Renderer3D& renderer);
		};
	}
}