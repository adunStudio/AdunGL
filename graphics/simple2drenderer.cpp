//
// Created by adun on 2017. 11. 18..
//

#include "simple2drenderer.h"

namespace AdunGL
{
    namespace graphics
    {
        void Simple2DRenderer::submit(const Renderable2D* renderable)
        {
            m_renderQueue.push_back(renderable);
        }

        void Simple2DRenderer::flush()
        {
            while(!m_renderQueue.empty())
            {
                const Renderable2D* renderable = m_renderQueue.front();

                renderable->getVAO()->bind();
                renderable->getIBO()->bind();

                renderable->getShader().setUniformMat4("ml_matrix", maths::mat4::translation(renderable->getPosition()));  // 월드 변환
                glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

                renderable->getIBO()->unbind();
                renderable->getVAO()->unbind();

                m_renderQueue.pop_front();
            }
        }
    }
}

// 배열 데이터로부터 기본 모델을 렌더링한다 배열에는 인덱스가 적용되며 유효한 인덱스값의 범위 또한 지정된다
// 배열 데이터를 순차적으로 읽는 것이 아니라 인덱스 배열을 순차적으로 읽는 함수이다.
// 인덱스 배열은 단순히 버텍스 데이터가 나열된 순서대로 읽어들이지 않으며, 공유 버텍스 데이터 활용을 위해 중보되는 경우도 있다
// void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices);
// 모드, 시작, 끝, 개수, 타입, 포인터
// GLsizei: 배열 내에 있는 좌표 사이의 바이트 간격
//    type: 인덱스 배열에 사용되는 데이터 타입
// GLvoid*: 인덱스 배열의 위치를 지정하는 포인터
