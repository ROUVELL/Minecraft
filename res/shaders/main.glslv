#version 450 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inUV;
layout (location = 2) in float blockId;

layout (location = 0) out vec2 uv;

uniform mat4 model;
uniform mat4 projview;


vec3 hash31(float p)
{
    vec3 p3 = fract(vec3(p * 21.2) * vec3(0.1031, 0.1030, 0.0973));
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.xxy + p3.yzz) * p3.zyx) + 0.05;
}

void main()
{
	uv = inUV;
	
	gl_Position = projview * model * vec4(inPosition, 1.0);
}