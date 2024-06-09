#version 450 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec4 inColor;

layout (location = 0) out vec4 color;

uniform mat4 projview;

void main()
{
	color = inColor;
	gl_Position = projview * vec4(inPosition, 1.0);
}