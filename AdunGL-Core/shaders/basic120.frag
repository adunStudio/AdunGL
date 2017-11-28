#version 120

varying vec4 coloror;
varying vec2 uvv;
varying float tidd;
varying vec4 pos;

uniform vec4 colour;
uniform vec2 light_pos;
uniform sampler2D textures[32];

float intensity = 1.0;

void main(void)
{
float intensity = 3.0 / length(pos.xy - light_pos);

   vec4 texColor = coloror;
    if(tidd > 0.0)
    {
        int tid = int(tidd);

        if(tid == 1)
            texColor = coloror * texture2D(textures[0], uvv);
        else if(tid == 2)
            texColor = coloror * texture2D(textures[1], uvv);
        else if(tid == 3)
            texColor = coloror * texture2D(textures[2], uvv);
        else if(tid == 4)
            texColor = coloror * texture2D(textures[3], uvv);
        else if(tid == 5)
            texColor = coloror * texture2D(textures[4], uvv);
        else if(tid == 6)
            texColor = coloror * texture2D(textures[5], uvv);
        else if(tid == 7)
            texColor = coloror * texture2D(textures[6], uvv);
        else if(tid == 8)
            texColor = coloror * texture2D(textures[7], uvv);
        else if(tid == 9)
            texColor = coloror * texture2D(textures[8], uvv);
        else if(tid == 10)
            texColor = coloror * texture2D(textures[9], uvv);
        else if(tid == 11)
            texColor = coloror * texture2D(textures[10], uvv);
        else if(tid == 12)
            texColor = coloror * texture2D(textures[11], uvv);
        else if(tid == 13)
            texColor = coloror * texture2D(textures[12], uvv);
        else if(tid == 14)
            texColor = coloror * texture2D(textures[13], uvv);
        else if(tid == 15)
            texColor = coloror * texture2D(textures[14], uvv);
        else if(tid == 16)
            texColor = coloror * texture2D(textures[15], uvv);
    }
    gl_FragColor = texColor;// * intensity;
}