//
// Created by adun on 2017. 11. 29..
//

#include "shader_factory.h"

namespace AdunGL
{
	namespace graphics
	{
		namespace ShaderFactory
		{

			const char* default_shader_vert =
				"#version 330 core\n"
				"\n"
				"layout (location = 0) in vec4 position;\n"
				"layout (location = 1) in vec2 uv;\n"
				"layout (location = 2) in vec2 mask_uv;\n"
				"layout (location = 3) in float tid;\n"
				"layout (location = 4) in float mid;\n"
				"layout (location = 5) in vec4 color;\n"
				"\n"
				"uniform mat4 pr_matrix;\n"
				"uniform mat4 vw_matrix = mat4(1.0);\n"
				"uniform mat4 ml_matrix = mat4(1.0);\n"
				"\n"
				"uniform mat4 mask_matrix;\n"
				"\n"
				"out DATA\n"
				"{\n"
				"	vec4 position;\n"
				"	vec2 uv;\n"
				"	vec2 mask_uv;\n"
				"	float tid;\n"
				"	float mid;\n"
				"	vec4 color;\n"
				"} vs_out;\n"
				"\n"
				"void main()\n"
				"{\n"
				"	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;\n"
				"	vs_out.position = ml_matrix * position;\n"
				"	vs_out.uv = uv;\n"
				"	vs_out.tid = tid;\n"
				"	vs_out.mid = mid;\n"
				"	vs_out.color = color;\n"
				"	vs_out.mask_uv = mask_uv;\n"
				"}\n";

			const char* default_shader_frag =
				"#version 330 core\n"
				"\n"
				"layout (location = 0) out vec4 color;\n"
				"\n"
				"in DATA\n"
				"{\n"
				"	vec4 position;\n"
				"	vec2 uv;\n"
				"	vec2 mask_uv;\n"
				"	float tid;\n"
				"	float mid;\n"
				"	vec4 color;\n"
				"} fs_in;\n"
				"\n"
				"uniform sampler2D textures[32];\n"
				"\n"
				"void main()\n"
				"{\n"
				"	vec4 texColor = fs_in.color;\n"
				"	vec4 maskColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
				"	if (fs_in.tid > 0.0)\n"
				"	{\n"
				"		int tid = int(fs_in.tid - 0.5);\n"
				"		texColor = fs_in.color * texture(textures[tid], fs_in.uv);\n"
				"	}\n"
				"	if (fs_in.mid > 0.0)\n"
				"	{\n"
				"		int mid = int(fs_in.mid - 0.5);\n"
				"		maskColor = texture(textures[mid], fs_in.mask_uv);\n"
				"	}\n"
				"	color = texColor * maskColor; // vec4(1.0 - maskColor.x, 1.0 - maskColor.y, 1.0 - maskColor.z, 1.0);\n"
				"}\n";

			const char* simple_shader_vert =
				"#version 330 core\n"
				"\n"
				"layout (location = 0) in vec4 position;\n"
				"layout (location = 1) in vec2 uv;\n"
				"layout (location = 2) in vec2 mask_uv;\n"
				"layout (location = 3) in float tid;\n"
				"layout (location = 4) in float mid;\n"
				"layout (location = 5) in vec4 color;\n"
				"\n"
				"uniform mat4 pr_matrix;\n"
				"\n"
				"out DATA\n"
				"{\n"
				"	vec2 uv;\n"
				"} vs_out;\n"
				"\n"
				"void main()\n"
				"{\n"
				"	gl_Position = pr_matrix * position;\n"
				"	vs_out.uv = uv;\n"
				"}\n";

			const char* simple_shader_frag =
				"#version 330 core\n"
				"\n"
				"layout (location = 0) out vec4 color;\n"
				"\n"
				"uniform sampler2D tex;\n"
				"\n"
				"in DATA\n"
				"{\n"
				"	vec2 uv;\n"
				"} fs_in;\n"
				"\n"
				"void main()\n"
				"{\n"
				"	color = texture(tex, fs_in.uv);\n"
				"}\n";

			const char* basic_light_shader_vert =
				"#version 330 core\n"
				"\n"
				"layout (location = 0) in vec4 position;\n"
				"layout (location = 1) in vec2 uv;\n"
				"layout (location = 2) in float tid;\n"
				"layout (location = 3) in vec4 color;\n"
				"\n"
				"uniform mat4 pr_matrix;\n"
				"uniform mat4 vw_matrix = mat4(1.0);\n"
				"uniform mat4 ml_matrix = mat4(1.0);\n"
				"\n"
				"out DATA\n"
				"{\n"
				"	vec4 position;\n"
				"	vec2 uv;\n"
				"	float tid;\n"
				"	vec4 color;\n"
				"} vs_out;\n"
				"\n"
				"void main()\n"
				"{\n"
				"	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;\n"
				"	vs_out.position = ml_matrix * position;\n"
				"	vs_out.uv = uv;\n"
				"	vs_out.tid = tid;\n"
				"	vs_out.color = color;\n"
				"}\n";

			const char* basic_light_shader_frag =
				"#version 330 core\n"
				"\n"
				"layout (location = 0) out vec4 color;\n"
				"\n"
				"uniform vec4 colour;\n"
				"uniform vec2 light_pos;\n"
				"\n"
				"in DATA\n"
				"{\n"
				"	vec4 position;\n"
				"	vec2 uv;\n"
				"	float tid;\n"
				"	vec4 color;\n"
				"} fs_in;\n"
				"\n"
				"uniform sampler2D textures[32];\n"
				"\n"
				"void main()\n"
				"{\n"
				"	float intensity = 1.0 / length(fs_in.position.xy - light_pos);\n"
				"	vec4 texColor = fs_in.color;\n"
				"	if (fs_in.tid > 0.0)\n"
				"	{\n"
				"		int tid = int(fs_in.tid - 0.5);\n"
				"		texColor = fs_in.color * texture(textures[tid], fs_in.uv);\n"
				"	}\n"
				"	color = texColor * intensity;\n"
				"}\n";


			Shader* DefaultShader()
			{
				return Shader::FromSource("Default Shader", default_shader_vert, default_shader_frag);
			}

			Shader* SimpleShader()
			{
				return Shader::FromSource("Simple Shader", simple_shader_vert, simple_shader_frag);
			}

			Shader* BasicLightShader()
			{
				return Shader::FromSource("Basic Light Shader", basic_light_shader_vert, basic_light_shader_frag);
			}
		}
	}
}