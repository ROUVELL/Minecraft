#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec4 inColor;

uniform mat4 projview;

out vec4 color;

void main()
{
	color = inColor;
	gl_Position = projview * vec4(inPosition, 1.0);
}