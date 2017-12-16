#pragma once

#include "renderer3d.h"

namespace AdunGL
{
	namespace graphics
	{
		class ForwardRenderer : public Renderer3D
		{
		private:

		public:

			ForwardRenderer();

			void init() override;
			void begin() override;
			void submit(Mesh* mesh) override;
			void end() override;
			void flush() override;
		};
	}
}