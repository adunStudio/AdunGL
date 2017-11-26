//
// Created by adun on 2017. 11. 27..
//

#include "label.h"

namespace AdunGL
{
    namespace graphics
    {
        Label::Label(std::string text, float x, float y, maths::vec4 color)
        : Renderable2D(),  m_text(text)
        {
            m_position = maths::vec3(x, y, 0.0f);
            m_color = color;
        }

        void Label::submit(Renderer2D* renderer) const
        {
            renderer->drawString(m_text, m_position, m_color);
        }
    }
}
