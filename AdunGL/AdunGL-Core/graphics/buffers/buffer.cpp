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
			// ���� ����
			// ������ �ʴ� ���� ��ü �̸��� �����Ѵ�.
			// �� �Լ��� ȣ���� �Ŀ��� glBindBuffer�� ȣ���Ͽ� �̸��� �����ϰ� ���� �� �ִ�.
			// void glGenBuffers(GLsizei n, GLuint* buffers)
			// glGenBuffers([������ ���� ���� integer], [���� ���� array of GLuint])
			glGenBuffers(1, &bufferID);

			// ���� ���ε�
			// void glBindBuffer(GLenum target, GLuint buffer)
			// ���� ��ü�� ���ؽ� �迭�̳� �迭 �ε��� ���� Ÿ�ٰ� �����ϴ� �Լ��̴�.
			// ���� �ռ� ���� ��ü�� ������� ���� ���̸� ���� ���������.
			// �� �Լ� ȣ�� ���� �����̳� ������ ����� ���� ��ü�� ������� �̷������.
			// GL_ARRAY_BUFFER -> ������ ���� ���ٴ� ���� �ǹ�
			glBindBuffer(GL_ARRAY_BUFFER, bufferID);

			//
			// ���ε�� ���ۿ� �����͸� �ִ´�.
			// ���� ��ü�� ������ ����� ����� �ʱ�ȭ�Ѵ�.
			// ������ ũ��� ���� ��Ʈ�� ���� ���� ��ü�� ������ ����� ����� �ʱ�ȭ �ϴ� �Լ��̴� ������ �����ϴ� �����ʹ� ��� �����ȴ�.
			// ���� ������ �����Ͱ� null�� �ƴϸ� ������ ������ �����͸� �����ϸ� ���� ��ü�� ������ ����� ���εǾ� ������ ������ ����ȴ�.
			// void glBufferData( GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage)

			// Ÿ��: ������ ����� ���� ���� ��ü Ÿ�� ���� ��� �� �ϳ��� �� �� �ִ�
			// GL_ARRAY_BUFFER: ���ؽ� �迭 ���� ��ü�� ������ ����� ����� ����.
			// GL_ELEMENT_ARRAY_BUFFER: �迭 �ε��� ���� ��ü�� ������ ����� ���������.

			// size: �⺻ ��� ������ �����ϴ� ���� ��ü�� ������ ����� ũ��

			// data: �ʱ�ȭ �ÿ� ������ ������ ����� �����ͷ��� ������, ������ ���簡 �ʿ�ġ ���� ��쿡�� NULL

			// GL_STATIC_DRAW -> �����Ͱ� ������� �ʴ´�.
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);

			// unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);



			/*
			1. glGen* �Լ��� ���ؼ� ���� �����ϰ�
			2. glBind* �Լ��� ���ؼ� ������ Binding�� �ϰ�,
			3. glBufferData �Լ��� ���� �����ϰ�,
			4. Display�� ���� Callback�� �޾��� ��, glEnableVertexAttibArray() �Լ��� ���� ����� �迭�� Ȱ��ȭ��Ű��,
			5. glVertexAttribPointer()�Լ��� ���� ���� ��� �������� ���ؼ� �Ķ���� ������ �ϰ�,
			6. ���������� glDrawArray()�Լ��� ���� �׸��� glDisableVertexAttribArray()�Լ��� ���� �迭�� ��Ȱ��ȭ ��Ų��.
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