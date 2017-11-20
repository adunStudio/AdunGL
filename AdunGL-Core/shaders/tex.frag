#version 120

uniform vec4 colour;
uniform vec2 light_pos;

uniform sampler2D tex;

void main(void)
{
    gl_FragColor = texture2D(tex, gl_TexCoord[0].st);
}