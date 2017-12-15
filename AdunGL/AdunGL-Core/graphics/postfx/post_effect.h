#pragma once

#include <vector>
#include "../buffers/frameBuffer.h"
#include "../buffers/indexBuffer.h"
#include "post_effect_pass.h"

namespace AdunGL
{
	namespace graphics
	{
		class PostEffects
		{
		private:
			std::vector<PostEffectsPass*> m_passes;

		public:
			PostEffects();
			~PostEffects();

			void push(PostEffectsPass* pass);
			void pop();

			void renderPostEffects(FrameBuffer* source, FrameBuffer* target, GLuint quad, IndexBuffer* indices);
		};
	}
}