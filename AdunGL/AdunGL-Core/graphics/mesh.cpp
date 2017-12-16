#include "mesh.h"

#include "renderers/renderer3d.h"

namespace AdunGL
{
	namespace graphics
	{
		Mesh::Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer, MaterialInstance* materialInstance)
			: m_vertexArray(vertexArray), m_indexBuffer(indexBuffer), m_materialInstance(materialInstance)
		{

		}

		Mesh::~Mesh()
		{
			delete m_vertexArray;
			delete m_indexBuffer;
			delete m_materialInstance;
		}

		void Mesh::render(Renderer3D& renderer)
		{
			m_materialInstance->bind();

			m_vertexArray->bind();
			m_indexBuffer->bind();

			m_vertexArray->draw(m_indexBuffer->getCount());

			m_indexBuffer->unbind();
			m_vertexArray->unbind();
			
			m_materialInstance->unbind();
		}


	}
}