#pragma once

//
// Created by adun on 2017. 11. 20..
//

#include <vector>
#include "../bases/renderable2d.h"

namespace AdunGL
{
	namespace graphics
	{
		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> m_renderables;
			maths::mat4 m_translationMatrix;

		public:
			Group(const maths::mat4& transform);

			~Group();

			void add(Renderable2D* renderable);

			void submit(Renderer2D* renderer) const override;

			inline maths::mat4& getTranslationMatrix() { return m_translationMatrix; }
		};
	}
}
