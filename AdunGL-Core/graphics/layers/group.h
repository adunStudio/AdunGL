//
// Created by adun on 2017. 11. 20..
//

#ifndef ADUNGL_GROUP_H
#define ADUNGL_GROUP_H

#include <vector>
#include "../renderable2d.h"

namespace AdunGL
{
    namespace graphics
    {
        class Group : public Renderable2D
        {
        private:
            std::vector<Renderable2D*> m_renderables;
            maths::mat4 m_translationMatrix;

        public:
            Group(const maths::mat4& transform);

            void add(Renderable2D* renderable);

            void submit(Renderer2D* renderer) const override;
        };
    }
}
#endif //ADUNGL_GROUP_H
