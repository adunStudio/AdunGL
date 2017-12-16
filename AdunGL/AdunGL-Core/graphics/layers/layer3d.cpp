#include "layer3d.h"
#include "../renderers/forward_renderer.h"

namespace AdunGL
{
	namespace graphics
	{
		Layer3D::Layer3D(Scene* scene)
			: m_scene(scene), m_renderer(new ForwardRenderer())
		{

		}

		Layer3D::~Layer3D()
		{
			delete m_scene;
			delete m_renderer;
		}

		void Layer3D::init()
		{
			onInit(*m_renderer, *m_scene);
		}

		void Layer3D::onInit(Renderer3D& renderer, Scene& scene)
		{

		}

		void Layer3D::onRender()
		{
			onRender(*m_renderer);
		}

		void Layer3D::onRender(Renderer3D& renderer)
		{
			m_scene->render(renderer);
			renderer.flush();
		}

	}
}