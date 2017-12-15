//
// Created by adun on 2017. 11. 27..
//

#include "label.h"

namespace AdunGL
{
	namespace graphics
	{
		Label::Label(std::string text, float x, float y, maths::vec4 color)
			: Renderable2D(), text(text), position(m_position), m_font(FontManager::get("arial"))
		{
			m_position = maths::vec3(x, y, 0);
			m_color = color;
		}

		Label::Label(std::string text, float x, float y, Font* font, maths::vec4 color)
			: Renderable2D(), text(text), position(m_position), m_font(font)
		{
			m_position = maths::vec3(x, y, 0);
			m_color = color;
		}

		Label::Label(std::string text, float x, float y, const std::string& font, maths::vec4 color)
			: Renderable2D(), text(text), position(m_position), m_font(FontManager::get(font))
		{
			m_position = maths::vec3(x, y, 0);
			m_color = color;

			validateFont(font);
		}

		Label::Label(std::string text, float x, float y, const std::string& font, unsigned int size, maths::vec4 color)
			: Renderable2D(), text(text), position(m_position), m_font(FontManager::get(font, size))
		{
			m_position = maths::vec3(x, y, 0);
			m_color = color;

			validateFont(font, size);
		}

		void Label::submit(Renderer2D* renderer) const
		{
			renderer->drawString(text, m_position, *m_font, m_color);
		}

		void Label::validateFont(const std::string& name, int size)
		{
			if (m_font != nullptr)
				return;

			std::cout << "NULL Font! Font=" << name;
			if (size > 0)
				std::cout << ", Size=" << size;
			std::cout << "\n";

			m_font = FontManager::get("arial");
		}

	}
}