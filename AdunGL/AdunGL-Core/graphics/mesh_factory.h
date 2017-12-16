#pragma once

#include <cstddef>
#include <GL/freeglut.h>
#include "../maths/maths.h"
#include "./bases/renderable2d.h"
#include "./shaders/shader.h"
#include "mesh.h"
#include "material.h"

namespace AdunGL
{
	namespace graphics
	{
		namespace MeshFactory
		{
			VertexArray* createQuad(float x, float y, float width, float height);
			
			VertexArray* createQuad(const maths::vec2& position, const maths::vec2& size);
		
			Mesh* createCube(float size, MaterialInstance* material);
		}
	}
}