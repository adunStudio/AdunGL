//
// Created by adun on 2017. 11. 5..
//

#include "vertexArray.h"

namespace AdunGL
{
	namespace graphics
	{
		GLuint VertexArray::s_currentBinding = 0;

		VertexArray::VertexArray()
		{
			// TODO: need Window Versio
			// glGenVertexArrays — generate vertex array object names
			// glGenVertexArrays(GLsizei n, GLuint *arrays);
			// n -> Specifies the number of vertex array object names to generate.
			// arrays -> Specifies an array in which the generated vertex array object names are stored.
			arrayID = API::CreateVertexArray();
		}

		VertexArray::~VertexArray()
		{
			for (int i = 0; i < m_buffers.size(); ++i)
				delete m_buffers[i];

			API::FreeVertexArray(arrayID);
		}

		Buffer* VertexArray::getBuffer(GLuint index)
		{
			return m_buffers[index];
		}

		void VertexArray::pushBuffer(Buffer* buffer)
		{
			m_buffers.push_back(buffer);

			const std::vector<BufferLayoutType>& layout = buffer->layout.getLayout();
			for (GLuint i = 0; i < layout.size(); ++i)
			{
				API::EnableVertexAttribute(i);
				API::SetVertexAttributePointer(i, layout[i].count, layout[i].type, layout[i].normalized, buffer->layout.getStride(), layout[i].offset);
			}

			// 저장된 꼭지점(Vertex)을 사용가능하게 하는 것이다.
			// void glEnableVertexAttribArray(GLuint index) & void glDisableVertexAttribArray(GLuint index)
			//glEnableVertexAttribArray(index);


			// 꼭짓점 값을 읽을때 어떻게 프로그래램에서 읽어야 하는지 정의해준다.
			// void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
			// index -> 꼭지점 데이터 배열의 인덱스 (Vertex shader의 layout(location=x)에서 x에 해당한다.)
			// size -> 꼭지점에서 사용하는 파라미터 개수 , (x, y, z) -> 3
			// normalize-> 데이터에 대해서 정규화를 할지에 대한 결정을 하는 것이다. 데이터의 범위를 [-1, 1]로 변경을 하는 것
			// stride, pointer -> offset
			//glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

			;
		}

		void VertexArray::bind() const
		{
			s_currentBinding = arrayID;
			API::BindVertexArray(arrayID);
		}

		void VertexArray::unbind() const
		{
			s_currentBinding = 0;
			API::UnbindVertexArrays();
		}

		void VertexArray::draw(GLuint count) const
		{
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
		}
	}
}