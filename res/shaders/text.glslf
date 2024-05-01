#version 330 core

layout (location = 0) out vec4 FragColor;

uniform sampler2D u_textTexture;

in vec2 uv;
in vec4 color;

void main()
{
    FragColor = color * texture(u_textTexture, uv);

    if (FragColor.a == 0.0)
        discard;
}