//
// Created by adun on 2017. 11. 27..
//

#ifndef ADUNGL_FONT_H
#define ADUNGL_FONT_H

#include <string>
#include "../exc/freetype-gl/freetype-gl.h"

namespace AdunGL
{
    namespace graphics
    {
        class Font
        {
        private:
            ftgl::texture_atlas_t* m_FTAtlas;
            ftgl::texture_font_t*  m_FTFont;

            unsigned int m_size;

            std::string m_name;
            std::string m_filename;

        public:
            Font(std::string name, std::string filename, int size);

            inline ftgl::texture_font_t* getFTFont() const { return m_FTFont; }

            inline const unsigned int getID()       const { return m_FTAtlas->id; }
            inline const std::string& getName()     const { return m_name;        }
            inline const std::string& getFileName() const { return m_filename;    }
            inline const int          getSize()     const { return m_size;    }
        };
    }
}
#endif //ADUNGL_FONT_H