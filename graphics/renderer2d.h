//
// Created by adun on 2017. 11. 18..
//

#ifndef ADUNGL_RENDERER2D_H
#define ADUNGL_RENDERER2D_H

#include <gl/glut.h>
#include "renderable2d.h"
#include "../maths/maths.h"

namespace AdunGL
{
    namespace graphics
    {
        class Renderer2D
        {
        protected:
            virtual void submit(const Renderable2D* renderable) = 0;
            virtual void flush() = 0;
        };
    }
}
#endif //ADUNGL_RENDERER2D_H
