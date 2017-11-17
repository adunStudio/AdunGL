//
// Created by adun on 2017. 11. 18..
//

#ifndef ADUNGL_RENDERABLE2D_H
#define ADUNGL_RENDERABLE2D_H

#include "buffers/buffer.h"
#include "buffers/indexBuffer.h"
#include "buffers/vertexArray.h"
#include "../maths/maths.h"


namespace AdunGL
{
    namespace graphics
    {
        class Renderable2D
        {
        protected:
            maths::vec3 m_position;
            maths::vec2 m_size;
            maths::vec4 m_color;

            VertexArray* m_vertexArray;
            IndexBuffer* m_indexBuffer;

        protected:
            Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color)
            : m_position(position), m_size(size), m_color(color)
            {
                m_vertexArray = new VertexArray();

                GLfloat vertices[] =
                {
                    0         , 0         ,          0,
                    position.x, position.y,          0,
                    position.x, 0         ,          0
                };

                GLfloat colors[] =
                {
                    color.x, color.y, color.z, color.w,
                    color.x, color.y, color.z, color.w,
                    color.x, color.y, color.z, color.w,
                    color.x, color.y, color.z, color.w
                };

                m_vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
                m_vertexArray->addBuffer(new Buffer(colors  , 4 * 4, 4), 1);

                GLushort indices[] = {0, 1, 2, 2, 3, 0}; // 좌 하단, 좌 상단, 우 상단, 우 상단, 우 하단, 좌 하단 -> 삼각형 * 2 = 사각형

                m_indexBuffer = new IndexBuffer(indices, 6);
            }

            virtual ~Renderable2D()
            {
                delete m_vertexArray;
                delete m_indexBuffer;
            }

            inline const maths::vec3& getPosition() const { return m_position; }
            inline const maths::vec2& getSize()     const { return m_size;     }
            inline const maths::vec4& getColor()    const { return m_color;    }



        };
    }
}
#endif //ADUNGL_RENDERABLE2D_H
