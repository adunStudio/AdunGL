#pragma once

//
// Created by adun on 2017. 11. 27..
//

#include "./bases/renderable2d.h"
#include "font_manager.h"

namespace AdunGL
{
	namespace graphics
	{
		class Label : public Renderable2D
		{
		public:
			Font*        m_font;
			std::string  text;
			maths::vec3& position;
			float        x, y;

		public:
			Label(std::string text, float x, float y, maths::vec4 color);

			Label(std::string text, float x, float y, Font* font, maths::vec4 color);

			Label(std::string text, float x, float y, const std::string& font, maths::vec4 color);

			Label(std::string text, float x, float y, const std::string& font, unsigned int size, maths::vec4 color);

			void submit(Renderer2D* renderer) const override;

			void validateFont(const std::string& name, int size = -1);
		};
	}
}