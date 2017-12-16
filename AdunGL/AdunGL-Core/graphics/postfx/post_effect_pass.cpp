#include "post_effect_pass.h"

namespace AdunGL
{
	namespace graphics
	{
		PostEffectsPass::PostEffectsPass(Shader* shader)
			: m_shader(shader)
		{
			m_shader->enable();
			m_shader->setUniform1i("tex", 0);
			m_shader->disable();
		}

		PostEffectsPass::~PostEffectsPass()
		{

		}

		void PostEffectsPass::renderPass(FrameBuffer* target)
		{
			m_shader->enable();
			m_shader->setUniformMat4("pr_matrix", maths::mat4::Orthographic(0, target->getWidth(), target->getHeight(), 0, -1.0f, 1.0f));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			m_shader->disable();
		}
	}
}
