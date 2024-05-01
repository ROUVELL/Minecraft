#version 330 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inUV;
layout (location = 2) in vec4 inColor;

out vec2 uv;
out vec4 color;

void main()
{
    uv = inUV;
    color = inColor;

    gl_Position = vec4(inPos, -1.0, 1.0);
}