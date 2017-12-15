#pragma once
//
// Created by adun on 2017. 11. 18..
//


#include <vector>
#include <GL/freeglut.h>
#include "../../maths/maths.h"
#include "../font.h"
#include "../mask.h"

namespace AdunGL
{
	namespace graphics
	{
		class Renderable2D;

		class Renderer2D
		{
		protected:
			std::vector<maths::mat4> m_transformationStack;
			const maths::mat4* m_transformationBack;
			const Mask* m_mask;

		protected:
			Renderer2D()
				: m_mask(nullptr)
			{
				m_transformationStack.push_back(maths::mat4::identity());
				m_transformationBack = &m_transformationStack.back();
			}

		public:

			virtual ~Renderer2D() {};

			void push(maths::mat4 matrix, bool override = false)
			{
				if (override)
					m_transformationStack.push_back(matrix);
				else
					m_transformationStack.push_back(m_transformationStack.back() * matrix);

				m_transformationBack = &m_transformationStack.back();
			}

			void pop()
			{
				if (m_transformationStack.size() > 1)  // identity º¸Á¸
					m_transformationStack.pop_back();

				m_transformationBack = &m_transformationStack.back();
				// TODO: Add to log!
			}

			virtual void setMask(const Mask* mask) { m_mask = mask; }
			virtual void begin() {};
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void drawString(const std::string& text, const maths::vec3& position, const Font& font, const maths::vec4& color) { };
			virtual void end() {};
			virtual void flush() = 0;
		};
	}
}
