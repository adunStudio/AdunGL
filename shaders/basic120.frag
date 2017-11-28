#version 120

varying vec4  pos;
varying vec2  uvv;
varying vec2  mask_uvv;
varying float tidd;
varying float midd;
varying vec4  coloror;

uniform vec4 colour;
uniform vec2 light_pos;
uniform sampler2D textures[32];

float intensity = 1.0;

void main(void)
{
float intensity = 3.0 / length(pos.xy - light_pos);

   vec4 texColor = coloror;

   vec4 maskColor = vec4(1.0, 1.0, 1.0, 1.0);

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

   if(midd > 0.0)
   {
        int mid = int(midd);

        if(mid == 1)
            texColor = texColor * texture2D(textures[0], mask_uvv);
        else if(mid == 2)
            texColor = texColor * texture2D(textures[1], mask_uvv);
        else if(mid == 3)
            texColor = texColor * texture2D(textures[2], mask_uvv);
        else if(mid == 4)
            texColor = texColor * texture2D(textures[3], mask_uvv);
        else if(mid == 5)
            texColor = texColor * texture2D(textures[4], mask_uvv);
        else if(mid == 6)
            texColor = texColor * texture2D(textures[5], mask_uvv);
        else if(mid == 7)
            texColor = texColor * texture2D(textures[6], mask_uvv);
        else if(mid == 8)
            texColor = texColor * texture2D(textures[7], mask_uvv);
        else if(mid == 9)
            texColor = texColor * texture2D(textures[8], mask_uvv);
        else if(mid == 10)
            texColor = texColor * texture2D(textures[9], mask_uvv);
        else if(mid == 11)
            texColor = texColor * texture2D(textures[10], mask_uvv);
        else if(mid == 12)
            texColor = texColor * texture2D(textures[11], mask_uvv);
        else if(mid == 13)
            texColor = texColor * texture2D(textures[12], mask_uvv);
        else if(mid == 14)
            texColor = texColor * texture2D(textures[13], mask_uvv);
        else if(mid == 15)
            texColor = texColor * texture2D(textures[14], mask_uvv);
        else if(mid == 16)
            texColor = texColor * texture2D(textures[15], mask_uvv);
   }

   gl_FragColor = texColor;// * intensity;
}