#pragma once
//
// Created by adun on 2017. 11. 29..
//

#include "shader.h"

namespace AdunGL
{
	namespace graphics
	{
		namespace ShaderFactory
		{
			Shader* DefaultShader();
			Shader* SimpleShader();
			Shader* BasicLightShader();
		}
	}
}
