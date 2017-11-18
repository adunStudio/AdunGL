//
// Created by adun on 2017. 11. 5..
//

#include "buffer.h"

namespace AdunGL
{
    namespace graphics
    {
        Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentCount)
        :componentCount(componentCount)
        {
            // 버퍼 생성
            // 사용되지 않는 버퍼 개체 이름을 리턴한다.
            // 이 함수를 호출한 후에는 glBindBuffer를 호출하여 이름을 연결하고 만들 수 있다.
            // void glGenBuffers(GLsizei n, GLuint* buffers)
            // glGenBuffers([생성할 버퍼 개수 integer], [버퍼 변수 array of GLuint])
            glGenBuffers(1, &bufferID);

            // 버퍼 바인드
            // void glBindBuffer(GLenum target, GLuint buffer)
            // 버퍼 개체를 버텍스 배열이나 배열 인덱스 버퍼 타겟과 연결하는 함수이다.
            // 만약 앞서 버퍼 개체가 연결되지 않은 것이면 새로 만들어진다.
            // 이 함수 호출 후의 변경이나 쿼리는 연결된 버퍼 개체를 대상으로 이루어진다.
            // GL_ARRAY_BUFFER -> 꼭지점 값이 들어간다는 것을 의미
            glBindBuffer(GL_ARRAY_BUFFER, bufferID);

            //
            // 바인드된 버퍼에 데이터를 넣는다.
            // 버퍼 개체의 데이터 저장고를 만들고 초기화한다.
            // 지정된 크기와 성능 힌트에 따라 버퍼 개체의 데이터 저장고를 만들고 초기화 하는 함수이다 기존에 존재하던 데이터는 모두 삭제된다.
            // 만약 데이터 포인터가 null이 아니면 데이터 저장고로 데이터를 복사하며 버퍼 개체의 데이터 저장고가 맵핑되어 있으면 맵핑이 종료된다.
            // void glBufferData( GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage)

            // 타겟: 데이터 저장고를 만들 버퍼 개체 타겟 다음 상수 중 하나가 될 수 있다
            // GL_ARRAY_BUFFER: 버텍스 배열 버퍼 개체의 데이터 저장고가 만들어 진다.
            // GL_ELEMENT_ARRAY_BUFFER: 배열 인덱스 버퍼 개체의 데이터 저장고가 만들어진다.

            // size: 기본 기계 단위로 지정하는 버퍼 개체의 데이터 저장고 크기

            // data: 초기화 시에 데이터 저장고로 복사될 데이터로의 포인터, 데이터 복사가 필요치 않은 경우에는 NULL

            // GL_STATIC_DRAW -> 데이터가 변경되지 않는다.
            glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);

            // unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0);



            /*
            1. glGen* 함수를 통해서 값을 생성하고

            2. glBind* 함수를 통해서 변수에 Binding을 하고,

            3. glBufferData 함수로 값을 저장하고,

            4. Display에 대한 Callback을 받았을 때, glEnableVertexAttibArray() 함수를 통해 사용할 배열을 활성화시키고,

            5. glVertexAttribPointer()함수를 통해 값을 어떻게 읽을지에 대해서 파라미터 지정을 하고,

            6. 마지막으로 glDrawArray()함수를 통해 그리고 glDisableVertexAttribArray()함수를 통해 배열을 비활성화 시킨다.
            */
        }

        Buffer::~Buffer()
        {
            glDeleteBuffers(GL_ARRAY_BUFFER, &bufferID);
        }

        void Buffer::bind() const
        {
            //
            glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        }

        void Buffer::unbind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}