//
// Created by adun on 2017. 11. 18..
//

#ifndef ADUNGL_RENDERER2D_H
#define ADUNGL_RENDERER2D_H

#include <vector>
#include <GL/glut.h>
#include "../maths/maths.h"

namespace AdunGL
{
    namespace graphics
    {
        class Renderable2D;

        class Renderer2D
        {
        protected:
            std::vector<maths::mat4> m_transformationStack;
            const maths::mat4* m_transformationBack;

        protected:
            Renderer2D()
            {
                m_transformationStack.push_back(maths::mat4::identity());
                m_transformationBack = &m_transformationStack.back();
            }

        public:
            void push(maths::mat4 matrix, bool override = false)
            {
                if(override)
                    m_transformationStack.push_back(matrix);
                else
                    m_transformationStack.push_back(m_transformationStack.back() * matrix);

                m_transformationBack = &m_transformationStack.back();
            }

            void pop()
            {
                if(m_transformationStack.size() > 1)  // identity 보존
                    m_transformationStack.pop_back();

                m_transformationBack = &m_transformationStack.back();
                // TODO: Add to log!
            }

            virtual void begin() {};
            virtual void submit(const Renderable2D* renderable) = 0;
            virtual void end() {};
            virtual void flush() = 0;
        };
    }
}
#endif //ADUNGL_RENDERER2D_H
