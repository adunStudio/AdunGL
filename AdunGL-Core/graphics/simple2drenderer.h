//
// Created by adun on 2017. 11. 18..
//

#ifndef ADUNGL_SIMPLE2DRENDERER_H
#define ADUNGL_SIMPLE2DRENDERER_H

#include <deque>
#include "renderer2d.h"
#include "static_sprite.h"

using namespace std;

namespace AdunGL
{
    namespace graphics
    {
        class Simple2DRenderer : public Renderer2D
        {
        private:
            deque<const Renderable2D*> m_renderQueue;

        public:
            void submit(const Renderable2D* renderable) override;
            void flush() override;
        };
    }
}
#endif //ADUNGL_SIMPLE2DRENDERER_H
