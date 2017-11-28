#version 120


attribute vec4 position;
attribute vec2 uv;
attribute float tid;
attribute vec4 color;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

varying vec4 pos;
varying vec2 uvv;
varying vec4 coloror;
varying float tidd;


void main(void)
{
    gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
    pos = ml_matrix * position;
    uvv = uv;
    tidd = tid;
    coloror = color;
}