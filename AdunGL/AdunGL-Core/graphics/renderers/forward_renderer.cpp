#include "forward_renderer.h"

namespace AdunGL
{
	namespace graphics
	{
		ForwardRenderer::ForwardRenderer()
		{

		}

		void ForwardRenderer::init()
		{

		}

		void ForwardRenderer::begin()
		{
			m_drawQueue.clear();
		}

		void ForwardRenderer::submit(Mesh* mesh)
		{
			m_drawQueue.push_back(mesh);
		}

		void ForwardRenderer::end()
		{

		}

		void ForwardRenderer::flush()
		{
			for (GLuint i = 0; i < m_drawQueue.size(); i++)
				m_drawQueue[i]->render(*this);
		}
	}
}