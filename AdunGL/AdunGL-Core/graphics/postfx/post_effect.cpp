#include "post_effect.h"

namespace AdunGL
{
	namespace graphics
	{
		PostEffects::PostEffects()
		{

		}

		PostEffects::~PostEffects()
		{

		}

		void PostEffects::push(PostEffectsPass* pass)
		{
			m_passes.push_back(pass);
		}

		void PostEffects::pop()
		{
			m_passes.pop_back();
		}

		void PostEffects::renderPostEffects(FrameBuffer* source, FrameBuffer* target, GLuint quad, IndexBuffer* indices)
		{
			target->bind();
			glActiveTexture(GL_TEXTURE0);
			source->getTexture()->bind();

			glBindVertexArray(quad);
			indices->bind();

			for (auto pass : m_passes)
				pass->renderPass(target);

			indices->unbind();
			glBindVertexArray(0);
		}
	}
}