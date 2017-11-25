/*#version 120
#extension GL_EXT_texture_array : enable

varying vec4 color;
varying vec2 uvv;
varying float tidd;
varying vec4 pos;

uniform vec4 colour;
uniform vec2 light_pos;
uniform sampler2D texture[32];
float intensity = 1.0;

void main(void)
{
    intensity = 1.0 / length(pos.xy - light_pos);

    vec4 texColor = color;

    if(tidd > 0.0)
    {
        //int texture_id = ;
        //texColor = texture2D(texture[int(tidd)], uvv);
    }

    gl_FragColor = texColor * intensity;
}*/

#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;
uniform sampler2D textures[32];

in DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

uniform sampler2D tex;

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	color = fs_in.color * intensity;
	color = texture(tex, fs_in.uv) * intensity;
}