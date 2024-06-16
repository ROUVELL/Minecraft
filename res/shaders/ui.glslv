#version 450 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inUV;
layout (location = 2) in uint inColor;

layout (location = 0) out vec2 uv;
layout (location = 1) out vec4 color;

vec4 decodeColor(uint col)
{
    vec4 decoded = vec4(1.0);

    decoded.r = float(col & 0xFF) / 255.0;
    decoded.g = float((col >> 8) & 0xFF) / 255.0;
    decoded.b = float((col >> 16) & 0xFF) / 255.0;
    decoded.a = float((col >> 24) & 0xFF) / 255.0;

    return decoded;
}

void main()
{
    uv = inUV;
    color = decodeColor(inColor);

    gl_Position = vec4(inPos, -1.0, 1.0);
}