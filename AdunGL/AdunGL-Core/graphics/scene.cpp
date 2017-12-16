#include "scene.h"
#include "renderers/renderer3d.h"

namespace AdunGL
{
	namespace graphics
	{
		Scene::Scene()
		{

		}

		Scene::~Scene()
		{
			for (int i = 0; i < m_meshes.size(); ++i)
				delete m_meshes[i];

			m_meshes.clear();
		}

		void Scene::add(Mesh* mesh)
		{
			m_meshes.push_back(mesh);
		}

		void Scene::render(Renderer3D& renderer)
		{
			for (Mesh* mesh : m_meshes)
				renderer.submit(mesh);
		}
	}
}