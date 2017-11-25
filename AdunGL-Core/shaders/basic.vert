/*#version 120

attribute vec4 position;
attribute vec2 uv;
attribute float tid;
attribute vec4 coloror;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

varying vec4 pos;
varying vec2 uvv;
varying vec4 color;
varying float tidd;


void main(void)
{
    gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
    pos = ml_matrix * position;
    uvv = uv;
    tidd = tid;
    color = coloror;
}*/

#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in float tid;
layout (location = 3) in vec4 color;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} vs_out;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
	vs_out.position = ml_matrix * position;
	vs_out.uv = uv;
	vs_out.tid = tid;
	vs_out.color = color;
}