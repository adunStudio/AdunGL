//
// Created by adun on 2017. 11. 18..
//

#ifndef ADUNGL_BATCHRENDERER2D_H
#define ADUNGL_BATCHRENDERER2D_H

#include "renderer2d.h"

namespace AdunGL
{
#define RENDERER_MAX_SPRITES    10000
#define RENDERER_VERTEX_SIZE    sizeof(VertexData) // renderable.c 구조체
#define RENDERER_SPRITE_SIZE    RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE    RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE   RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX   0
#define SHADER_COLOR_INDEX    1

    namespace graphics {
        class BatchRenderer2D : public Renderer2D {
        private:
            GLuint m_vao;
            GLuint m_vbo;
            IndexBuffer *m_ibo; // 60,000
            GLsizei m_indexCount;

        public:
            BatchRenderer2D();
            ~BatchRenderer2D();

            void submit(const Renderable2D *renderable) override;

            void flush() override;

        private:
            void init();
        };
    }
}
#endif //ADUNGL_BATCHRENDERER2D_H
