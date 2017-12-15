#pragma once

//
// Created by adun on 2017. 11. 20..
//


#include <vector>
#include "../bases/renderer2d.h"
#include "../bases/renderable2d.h"
#include "../mask.h"

namespace AdunGL
{
	namespace graphics
	{
		class Layer
		{
		protected:
			std::vector<Renderable2D*> m_renderables;
			Shader* m_shader;
			maths::mat4 m_projectionMatrix;

		public:
			Renderer2D* renderer;

		public:
			Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix);

			virtual ~Layer();

			virtual void add(Renderable2D* renderable);

			virtual void render();

			inline void setMask(const Mask* mask) const { renderer->setMask(mask); }

			inline const std::vector<Renderable2D*> getRenderalbes() const { return m_renderables; };
		};
	}
};
