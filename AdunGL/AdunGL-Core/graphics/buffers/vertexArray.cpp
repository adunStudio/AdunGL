//
// Created by adun on 2017. 11. 5..
//

#include "vertexArray.h"

namespace AdunGL
{
	namespace graphics
	{
		VertexArray::VertexArray()
		{
			// TODO: need Window Versio
			// glGenVertexArrays — generate vertex array object names
			// glGenVertexArrays(GLsizei n, GLuint *arrays);
			// n -> Specifies the number of vertex array object names to generate.
			// arrays -> Specifies an array in which the generated vertex array object names are stored.
			glGenVertexArrays(1, &arrayID);

		}

		VertexArray::~VertexArray()
		{
			for (int i = 0; i < buffers.size(); ++i)
				delete buffers[i];

			glDeleteVertexArrays(1, &arrayID);
		}

		void VertexArray::addBuffer(Buffer *buffer, GLuint index)
		{
			bind();
			buffer->bind();

			// 저장된 꼭지점(Vertex)을 사용가능하게 하는 것이다.
			// void glEnableVertexAttribArray(GLuint index) & void glDisableVertexAttribArray(GLuint index)
			glEnableVertexAttribArray(index);


			// 꼭짓점 값을 읽을때 어떻게 프로그래램에서 읽어야 하는지 정의해준다.
			// void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
			// index -> 꼭지점 데이터 배열의 인덱스 (Vertex shader의 layout(location=x)에서 x에 해당한다.)
			// size -> 꼭지점에서 사용하는 파라미터 개수 , (x, y, z) -> 3
			// normalize-> 데이터에 대해서 정규화를 할지에 대한 결정을 하는 것이다. 데이터의 범위를 [-1, 1]로 변경을 하는 것
			// stride, pointer -> offset
			glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

			buffer->unbind();
			unbind();
		}

		void VertexArray::bind() const
		{
			glBindVertexArray(arrayID);
		}

		void VertexArray::unbind() const
		{
			glBindVertexArray(0);
		}

		void VertexArray::draw(GLuint count) const
		{
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
		}
	}
}