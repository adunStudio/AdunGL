//
// Created by adun on 2017. 11. 20..
//

#ifndef ADUNGL_LAYER_H
#define ADUNGL_LAYER_H

#include <vector>
#include "../renderer2d.h"
#include "../renderable2d.h"
#include "../mask.h"

namespace AdunGL
{
    namespace graphics
    {
        class Layer
        {
        protected:
            Renderer2D* m_renderer;
            std::vector<Renderable2D*> m_renderables;
            Shader* m_shader;
            maths::mat4 m_projectionMatrix;

        public:
            Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix);

            virtual ~Layer();

            virtual void add(Renderable2D* renderable);

            virtual void render();

            inline void setMask(const Mask* mask) const { m_renderer->setMask(mask); }

            inline const std::vector<Renderable2D*> getRenderalbes() const { return m_renderables; };
        };
    }
};
#endif //ADUNGL_LAYER_H
