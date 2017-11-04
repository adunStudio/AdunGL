#version 120

attribute vec4 position;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

varying vec4 pos;

void main(void)
{
    gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
    pos = position;
}