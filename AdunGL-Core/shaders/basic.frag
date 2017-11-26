#version 410 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;
uniform float tid;

in DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

uniform sampler2D textures[32];

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	vec4 texColor = fs_in.color;

	if(fs_in.tid > 0.0)
	{
	    int tid = int(fs_in.tid);

        if(tid == 1)
            texColor = fs_in.color * texture(textures[0], fs_in.uv);
        else if(tid == 2)
            texColor = fs_in.color * texture(textures[1], fs_in.uv);
        else if(tid == 3)
            texColor = fs_in.color * texture(textures[2], fs_in.uv);
        else if(tid == 4)
            texColor = fs_in.color * texture(textures[3], fs_in.uv);
        else if(tid == 5)
            texColor = fs_in.color * texture(textures[4], fs_in.uv);
        else if(tid == 6)
            texColor = fs_in.color * texture(textures[5], fs_in.uv);
        else if(tid == 7)
            texColor = fs_in.color * texture(textures[6], fs_in.uv);
        else if(tid == 8)
            texColor = fs_in.color * texture(textures[7], fs_in.uv);
        else if(tid == 9)
            texColor = fs_in.color * texture(textures[8], fs_in.uv);
        else if(tid == 10)
            texColor = fs_in.color * texture(textures[9], fs_in.uv);
        else if(tid == 11)
            texColor = fs_in.color * texture(textures[10], fs_in.uv);
        else if(tid == 12)
            texColor = fs_in.color * texture(textures[11], fs_in.uv);
        else if(tid == 13)
            texColor = fs_in.color * texture(textures[12], fs_in.uv);
        else if(tid == 14)
            texColor = fs_in.color * texture(textures[13], fs_in.uv);
        else if(tid == 15)
            texColor = fs_in.color * texture(textures[14], fs_in.uv);
        else if(tid == 16)
            texColor = fs_in.color * texture(textures[15], fs_in.uv);
	}

	color = texColor;// * intensity;
}