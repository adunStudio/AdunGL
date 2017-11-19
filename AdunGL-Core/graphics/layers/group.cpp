//
// Created by adun on 2017. 11. 20..
//

#include "group.h"

namespace AdunGL
{
    namespace graphics
    {
        Group::Group(const maths::mat4& transform)
        : m_translationMatrix(transform)
        {

        }

        void Group::add(Renderable2D* renderable)
        {
            m_renderables.push_back(renderable);
        }

        void Group::submit(Renderer2D* renderer) const
        {
            renderer->push(m_translationMatrix);

            for(const Renderable2D* renderable : m_renderables)
                renderable->submit(renderer);

            renderer->pop();
        }

    }
}
