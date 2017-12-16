#pragma once

#include "layer.h"
#include "../../events/event.h"
#include "../bases/renderable2d.h"
#include "../mask.h"

namespace AdunGL
{
	namespace graphics
	{
		class Layer2D : public Layer
		{
		private:
			Renderer2D* m_renderer;

		protected:
			vector<Renderable2D*> m_renderables;
			Shader* m_shader;
			maths::mat4 m_projectionMatrix;

		public:
			Layer2D(Shader* shader, const maths::mat4& projectionMatrix);
			virtual ~Layer2D();

			virtual void init();
			virtual void onInit(Renderer2D& renderer, Shader& shader);

			inline void setMask(const Mask* mask) const { m_renderer->setMask(mask); }
			virtual Renderable2D* add(Renderable2D* renderable);
			inline const vector<Renderable2D*> getRenderables() const { return m_renderables; }

			virtual void onRender(Renderer2D& renderer);
			void onRender() override;
		};
	}
}