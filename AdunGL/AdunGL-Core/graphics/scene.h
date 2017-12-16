#pragma once

#include <vector>
#include "mesh.h"
#include <GL/freeglut.h>

namespace AdunGL
{
	namespace graphics
	{
		class Renderer3D;

		class Scene
		{
		private:
			std::vector<Mesh*> m_meshes;

		public:
			Scene();
			~Scene();

			void add(Mesh* mesh);
			void render(Renderer3D& renderer);

			const std::vector<Mesh*> getMeshes() const { return m_meshes; }
		};
	}
}