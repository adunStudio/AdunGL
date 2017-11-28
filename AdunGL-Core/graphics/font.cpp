//
// Created by adun on 2017. 11. 27..
//

#include "font.h"

namespace AdunGL
{
    namespace graphics
    {
        Font::Font(std::string name, std::string filename, int size)
        : m_name(name), m_filename(filename), m_size(size), m_scale(maths::vec2(1, 1))
        {
            m_FTAtlas = ftgl::texture_atlas_new(512, 512, 3);
            m_FTFont  = ftgl::texture_font_new_from_file(m_FTAtlas, size, filename.c_str());
        }

        void Font::setScale(float x, float y)
        {
            m_scale = maths::vec2(x, y);
        }
    }
}