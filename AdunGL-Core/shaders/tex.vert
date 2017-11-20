#version 120



uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

varying vec4 pos;
varying vec4 color;


void main(void)
{
    gl_Position = pr_matrix * gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;
}