#version 120

varying vec4 color;
varying vec4 pos;

uniform vec4 colour;
uniform vec2 light_pos;
float intensity = 1.0;

void main(void)
{
    intensity = 1.0 / length(pos.xy - light_pos);
    gl_FragColor = colour * intensity;
}