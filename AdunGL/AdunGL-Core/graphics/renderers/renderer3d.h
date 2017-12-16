#pragma once

#include <vector>
#include "../mesh.h"

namespace AdunGL
{
	namespace graphics
	{
		class Renderer3D
		{
		protected:
			std::vector<Mesh*> m_drawQueue;

		public:
			virtual void init() = 0;
			virtual void begin() = 0;
			virtual void submit(Mesh* mesh) = 0;
			virtual void end() = 0;
			virtual void flush() = 0;
		};
	}
}