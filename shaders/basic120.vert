#version 120

attribute vec4  position;      // location = 0
attribute vec2  uv;            // location = 1
attribute vec2  mask_uv;       // location = 2
attribute float tid;           // location = 3
attribute float mid;           // location = 4
attribute vec4  color;         // location = 5

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

varying vec4  pos;
varying vec2  uvv;
varying vec2  mask_uvv;
varying float tidd;
varying float midd;
varying vec4  coloror;


void main(void)
{
    gl_Position = pr_matrix * vw_matrix * ml_matrix * position;

    pos      = ml_matrix * position;
    uvv      = uv;
    mask_uvv = mask_uv;
    tidd     = tid;
    midd     = mid;
    coloror  = color;
}