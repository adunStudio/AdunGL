#pragma once

#include <cstdlib>
#include <string>
#include <GL/freeglut.h>
using namespace std;
namespace AdunGL
{
#define STRINGFORMAT_BUFFER_SIZE 10 * 1024

	class StringFormat
	{
	private:
		static char* s_buffer;

	public:
		template<typename T>
		static string Hex(const T& input)
		{
			memset(s_buffer, 0, STRINGFORMAT_BUFFER_SIZE);
			sprintf(s_buffer, "%02x", input);
			return string(s_buffer);
		}

		template<typename T>
		static string Hex(const T& input, GLuint size)
		{
			memset(s_buffer, 0, STRINGFORMAT_BUFFER_SIZE);
			for (GLuint i = 0; i < size; ++i)
				sprintf(s_buffer + i * 3, "%02x", input[i]);

			return string(s_buffer);
		}
	
	};
}