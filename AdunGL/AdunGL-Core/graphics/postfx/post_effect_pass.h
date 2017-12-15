#pragma once

#include "../buffers/frameBuffer.h""
#include "../shaders/shader.h"

namespace AdunGL
{
	namespace graphics
	{
		class PostEffectsPass
		{
		private:
			Shader* m_shader;

		public:
			PostEffectsPass(Shader* shader);
			~PostEffectsPass();

			void renderPass(FrameBuffer* target);
		};
	}
}