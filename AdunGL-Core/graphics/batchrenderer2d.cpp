//
// Created by adun on 2017. 11. 18..
//

#include "batchrenderer2d.h"
#include "renderer2d.h"

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



            glGenVertexArrays(1, &m_vao);
            glGenBuffers(1, &m_vbo);

            glBindVertexArray(m_vao);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);


            glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
            glEnableVertexAttribArray(SHADER_UV_INDEX    );
            glEnableVertexAttribArray(SHADER_TID_INDEX   );
            glEnableVertexAttribArray(SHADER_COLOR_INDEX );


            glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT        , GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(0)                          );
            glVertexAttribPointer(SHADER_UV_INDEX,     2, GL_FLOAT        , GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv))   );
            glVertexAttribPointer(SHADER_TID_INDEX,    1, GL_FLOAT        , GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid))  );
            glVertexAttribPointer(SHADER_COLOR_INDEX , 4, GL_UNSIGNED_BYTE, GL_TRUE , RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            GLuint indices[RENDERER_INDICES_SIZE];

            int offset = 0;

            // 사각형 인덱스
            for(int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
            {
                indices[  i  ] = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;
                indices[i + 3] = offset + 2;
                indices[i + 4] = offset + 3;
                indices[i + 5] = offset + 0;

                offset += 4;
            }

            m_ibo = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

            glBindVertexArray(0);

            // 폰트

            // const size_t width, const size_t height, const size_t depth
            m_FTAtlas = ftgl::texture_atlas_new(512, 512, 1);

            // texture_atlas_t * atlas, const float pt_size, const char * filename
            m_FTFonts = ftgl::texture_font_new_from_file(m_FTAtlas, 200, "/Users/adun/Desktop/AdunGL/asset/arial.ttf");
        }

        void BatchRenderer2D::begin()
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

            // 버퍼 개체의 데이터 저장고를 맵핑한다.
            // GLvoid* glMapBuffer(GLenum 타겟, GLenum 접근방식);
            // 버퍼 개체의 데이터 저장고를 클라이언트의 주소 공간과 맵핑한다.
            // 맵핑이 이루어진 뒤에는 리턴된 포인터에 지정한 접근 플래그에 따라 직접적인 읽기나 쓰기를 수행할 수 있으며, 버퍼 개체의 데이터 저장고가 이미 맵핑된 경우에는 오류가 발생한다.
            // OpenGL 명령으로 전달한 인자값은 리턴도니 포인터에서 얻지 못할수도 있다.
            // 타겟: 데이터 저장고를 맵핑하려는 버퍼 개체 타겟 ( GL_ARRAY_BUFFER or GL_ELEMENT_ARAAY_BUFFER )
            // 접근 방식: GL_READ_ONLY, GL_WRITE_ONLY, GL_READ_WRITE
            m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        }

        void BatchRenderer2D::submit(const Renderable2D* renderable)
        {
            const maths::vec3&              position = renderable->getPosition();
            const maths::vec2&              size     = renderable->getSize    ();
            const maths::vec4&              color    = renderable->getColor   ();
            const std::vector<maths::vec2>& uv       = renderable->getUV      ();
            const GLuint                    tid      = renderable->getTID     ();


            unsigned int c = 0;

            float ts = 0.0f;

            if(tid > 0)
            {
                bool found = false;

                for(int i = 0; i < m_textureSlots.size(); ++i)
                {
                    if(m_textureSlots[i] == tid)
                    {
                        ts = (float)(i + 1);
                        found = true;
                        break;
                    }
                }

                if(!found)
                {
                    if(m_textureSlots.size() >= 32)
                    {
                        end();
                        flush();
                        begin();
                    }

                    m_textureSlots.push_back(tid);
                    ts = (float)(m_textureSlots.size());
                }
            }
            else
            {

                int r = color.x * 255.0f;
                int g = color.y * 255.0f;
                int b = color.z * 255.0f;
                int a = color.w * 255.0f;

                // http://www.fayewilliams.com/2011/09/21/bitwise-rgba-values/
                c = a << 24 | b << 16 | g << 8 | r;
            }

            //  4X4 * 4X1 = 4X1

            m_buffer->vertex = *m_transformationBack * position;
            m_buffer->uv = uv[0];
            m_buffer->tid = ts;
            m_buffer->color  = c;//olor;
            m_buffer++;

            m_buffer->vertex = *m_transformationBack * maths::vec3(position.x         , position.y + size.y, position.z);
            m_buffer->uv = uv[1];
            m_buffer->tid = ts;
            m_buffer->color  = c;//olor;
            m_buffer++;

            m_buffer->vertex = *m_transformationBack * maths::vec3(position.x + size.x, position.y + size.y, position.z);
            m_buffer->uv = uv[2];
            m_buffer->tid = ts;
            m_buffer->color  = c;//olor;
            m_buffer++;

            m_buffer->vertex = *m_transformationBack * maths::vec3(position.x + size.x, position.y         , position.z);
            m_buffer->uv = uv[3];
            m_buffer->tid = ts;
            m_buffer->color  = c;//olor;
            m_buffer++;

            m_indexCount += 6;
        }

        void BatchRenderer2D::drawString(const std::string& text, const maths::vec3& position, const maths::vec4& color)
        {
            using namespace ftgl;

            int r = color.x * 255.0f;
            int g = color.y * 255.0f;
            int b = color.z * 255.0f;
            int a = color.w * 255.0f;

            // http://www.fayewilliams.com/2011/09/21/bitwise-rgba-values/
            unsigned int colorr = a << 24 | b << 16 | g << 8 | r;

            float ts = 0.0f;

            bool found = false;

            for(int i = 0; i < m_textureSlots.size(); ++i)
            {
                if(m_textureSlots[i] == m_FTAtlas->id)
                {
                    ts = (float)(i + 1);
                    found = true;
                    break;
                }
            }

            if(!found)
            {
                if(m_textureSlots.size() >= 32)
                {
                    end();
                    flush();
                    begin();
                }

                m_textureSlots.push_back(m_FTAtlas->id);
                ts = (float)(m_textureSlots.size());
            }

            // Todo Window Size!
            float scaleX = 960.0f / 32.0f;
            float scaleY = 540.0f / 18.0f;

            // 시작 위치
            float x = position.x;

            for(int i = 0; i < text.length(); ++i)
            {
                char c = text.at(i);
                texture_glyph_t* glyph = texture_font_get_glyph(m_FTFonts, c);

                if(glyph != NULL)
                {
                    if(i > 0)
                    {
                        // 글 간격
                        float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
                        x += kerning / scaleX;
                    }

                    float x0 = x + glyph->offset_x / scaleX;
                    float y0 = position.y + glyph->offset_y / scaleY;
                    float x1 = x0 + glyph->width / scaleX;
                    float y1 = y0 - glyph->height / scaleY;

                    float u0 = glyph->s0;
                    float v0 = glyph->t0;
                    float u1 = glyph->s1;
                    float v1 = glyph->t1;

                    m_buffer->vertex = *m_transformationBack * maths::vec3(x0, y0, 0);
                    m_buffer->uv = maths::vec2(u0, v0);
                    m_buffer->tid = ts;
                    m_buffer->color = colorr;
                    m_buffer++;

                    m_buffer->vertex = *m_transformationBack * maths::vec3(x0, y1, 0);
                    m_buffer->uv = maths::vec2(u0, v1);
                    m_buffer->tid = ts;
                    m_buffer->color = colorr;
                    m_buffer++;

                    m_buffer->vertex = *m_transformationBack * maths::vec3(x1, y1, 0);
                    m_buffer->uv = maths::vec2(u1, v1);
                    m_buffer->tid = ts;
                    m_buffer->color = colorr;
                    m_buffer++;

                    m_buffer->vertex = *m_transformationBack * maths::vec3(x1, y0, 0);
                    m_buffer->uv = maths::vec2(u1, v0);
                    m_buffer->tid = ts;
                    m_buffer->color = colorr;
                    m_buffer++;

                    m_indexCount += 6;

                    x += glyph->advance_x / scaleX;
                }
            }
        }

        void BatchRenderer2D::end()
        {
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void BatchRenderer2D::flush()
        {
            for(int i = 0; i < m_textureSlots.size(); ++i)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
            }

            glBindVertexArray(m_vao);
            m_ibo->bind();

            glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);

            m_ibo->unbind();
            glBindVertexArray(0);

            m_indexCount = 0;
        }

    }
}