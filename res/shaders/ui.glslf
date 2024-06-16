#version 450 core

layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec2 uv;
layout (location = 1) in vec4 color;

uniform sampler2D u_textTexture;


void main()
{
    FragColor = color * texture(u_textTexture, uv);

    if (FragColor.a == 0.0)
        discard;
}