#version 450 core

layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec2 uv;

uniform sampler2D u_texture0;


void main()
{
	FragColor = texture(u_texture0, uv);
}
