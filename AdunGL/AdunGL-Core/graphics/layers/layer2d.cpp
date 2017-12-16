#include "layer2d.h"

#include "../renderers/batchrenderer2d.h"
#include "../window.h"

namespace AdunGL
{
	namespace graphics
	{
		Layer2D::Layer2D(Shader* shader, const maths::mat4& projectionMatrix)
			: m_renderer(new BatchRenderer2D(Window::instance->getWidth(), Window::instance->getHeight())), m_shader(shader), m_projectionMatrix(projectionMatrix)
		{
			m_shader->enable();
			m_shader->setUniformMat4("pr_matrix", m_projectionMatrix);

			GLint texIDs[] =
			{
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31
			};

			m_shader->setUniform1iv("textures", texIDs, 32);
			
			m_shader->disable();
		}

		Layer2D::~Layer2D()
		{
			delete m_shader;
			delete m_renderer;

			for (int i = 0; i < m_renderables.size(); ++i)
				delete m_renderables[i];
		}

		void Layer2D::init()
		{
			onInit(*m_renderer, *m_shader);
		}

		void Layer2D::onInit(Renderer2D& renderer, Shader& shader)
		{

		}

		Renderable2D* Layer2D::add(Renderable2D* renderable)
		{
			m_renderables.push_back(renderable);
			return renderable;
		}

		void Layer2D::onRender()
		{
			m_shader->enable();
			m_renderer->begin();

			for (const Renderable2D* renderable : m_renderables)
			{
				renderable->submit(m_renderer);
			}

			m_renderer->end();
			m_renderer->flush();

			onRender(*m_renderer);
		}

		void Layer2D::onRender(Renderer2D& renderer)
		{


		}
	}
}