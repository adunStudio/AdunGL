#version 120

varying vec4 color;
varying vec2 uvv;
varying vec4 pos;

uniform vec4 colour;
uniform vec2 light_pos;
uniform sampler2D tex;

float intensity = 1.0;

void main(void)
{
    intensity = 1.0 / length(pos.xy - light_pos);
    //gl_FragColor = colour * intensity;
    gl_FragColor = color * intensity;
    //gl_FragColor = texture(tex, uvv) * intensity;
}