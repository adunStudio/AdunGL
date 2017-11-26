//
// Created by adun on 2017. 11. 27..
//

#ifndef ADUNGL_LABEL_H
#define ADUNGL_LABEL_H

#include "renderable2d.h"

namespace AdunGL
{
    namespace graphics
    {
        class Label : public Renderable2D
        {
        private:
            std::string m_text;

        public:
            Label(std::string text, float x, float y, maths::vec4 color);

            void submit(Renderer2D* renderer) const override;
        };
    }
}

#endif //ADUNGL_LABEL_H
