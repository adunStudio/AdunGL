#pragma once

#include <cstddef>
#include <GL/freeglut.h>
#include "../maths/maths.h"
#include "./bases/renderable2d.h"
#include "./shaders/shader.h"

namespace AdunGL
{
	namespace graphics
	{
		namespace MeshFactory
		{
			GLuint createQuad(float x, float y, float width, float height);
			
			GLuint createQuad(const maths::vec2& position, const maths::vec2& size);
		}
	}
}