//
// Created by adun on 2017. 11. 18..
//

#ifndef ADUNGL_RENDERABLE2D_H
#define ADUNGL_RENDERABLE2D_H

#include "buffers/buffer.h"
#include "buffers/indexBuffer.h"
#include "buffers/vertexArray.h"
#include "shader.h"
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

            Shader& m_shader;

        public:
            Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color, Shader& shader)
            : m_position(position), m_size(size), m_color(color), m_shader(shader)
            {
                m_vertexArray = new VertexArray();

                GLfloat vertices[] =
                {
                    0     , 0     , 0,
                    0     , size.y, 0,
                    size.x, size.y, 0,
                    size.x, 0     , 0
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

        public:
            inline const VertexArray* getVAO()      const { return m_vertexArray; }
            inline const IndexBuffer* getIBO()      const { return m_indexBuffer; }

            inline            Shader& getShader()   const { return m_shader;      }

            inline const maths::vec3& getPosition() const { return m_position;    }
            inline const maths::vec2& getSize()     const { return m_size;        }
            inline const maths::vec4& getColor()    const { return m_color;       }



        };
    }
}
#endif //ADUNGL_RENDERABLE2D_H
