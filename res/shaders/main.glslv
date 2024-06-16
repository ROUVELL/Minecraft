#version 450 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inUV;

layout (location = 0) out vec2 uv;

uniform mat4 model;
uniform mat4 projview;


void main()
{
	uv = inUV;
	
	gl_Position = projview * model * vec4(inPosition, 1.0);
}