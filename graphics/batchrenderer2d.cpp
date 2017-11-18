//
// Created by adun on 2017. 11. 18..
//

#include "batchrenderer2d.h"

namespace AdunGL
{
    namespace graphics
    {
        BatchRenderer2D::BatchRenderer2D()
        {
            init();
        }

        BatchRenderer2D::~BatchRenderer2D()
        {
            delete m_ibo;
            glDeleteBuffers(1, &m_vbo);
        }

        void BatchRenderer2D::init()
        {

            // 배치렌더러 버퍼 생성 (모아놓고 빠른 render을 위해)

            // gl레퍼런스의 자세한 내용은 vertexArray.cpp, buffer.cpp 참조

            glGenVertexArraysAPPLE(1, &m_vao);
            glGenBuffers(1, &m_vbo);

            glBindVertexArrayAPPLE(m_vao);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
            glEnableVertexAttribArray(SHADER_COLOR_INDEX );
            glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
            glVertexAttribPointer(SHADER_COLOR_INDEX , 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            GLushort indices[RENDERER_INDICES_SIZE];

            int offset = 0;

            // 사각형 인덱스
            for(int i = 0; i < RENDERER_INDICES_SIZE; i+=6)
            {
                indices[  i  ] = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;
                indices[i + 2] = offset + 2;
                indices[i + 2] = offset + 3;
                indices[i + 2] = offset + 0;

                offset += 4;
            }

            m_ibo = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

            glBindVertexArrayAPPLE(0);
        }

        void BatchRenderer2D::submit(const Renderable2D *renderable)
        {

        }

        void BatchRenderer2D::flush()
        {

        }

    }
}