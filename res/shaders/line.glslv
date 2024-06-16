#version 450 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in uint inColor;

layout (location = 0) out vec4 color;

uniform mat4 projview;

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
	color = decodeColor(inColor);
	gl_Position = projview * vec4(inPosition, 1.0);
}