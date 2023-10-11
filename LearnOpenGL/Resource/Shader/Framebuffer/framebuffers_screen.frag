#version 330 core
#define ARR_SIZE 9
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D uScreenTexture;

const float offset = 1.0 / 300.0;

void main()
{
    vec2 offsets[ARR_SIZE] = {
        vec2(-offset,  offset),
        vec2(0.0, offset),
        vec2(offset, offset),
        vec2(-offset, 0.0),
        vec2(0.0, 0.0),
        vec2(offset, 0.0),
        vec2(-offset, -offset),
        vec2(0.0, -offset),
        vec2(offset, -offset)
    };
    
    float kernel[ARR_SIZE] = { 
        0, 0, 0,
        0, 1, 0,
        0, 0, 0,
    };
    
    vec3 sampleTex[ARR_SIZE];
    
    for (int i = 0; i < ARR_SIZE; i++)
    {
        sampleTex[i] = vec3(texture2D(uScreenTexture, TexCoords.st + offsets[i]));
    }
    
    vec3 col = vec3(0.0);
    
    for (int i = 0; i < ARR_SIZE; i++)
    {
        col += sampleTex[i] * kernel[i];
    }

    FragColor = vec4(col, 1.0);
} 