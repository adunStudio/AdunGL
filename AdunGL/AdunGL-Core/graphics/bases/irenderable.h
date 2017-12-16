#pragma once

namespace AdunGL
{
	namespace graphics
	{
		class Renderer3D;

		class IRenderable
		{
		public:
			virtual void render(Renderer3D& renderer) = 0;
		};
	}
}