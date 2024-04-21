#version 330 core

layout (location = 0) out vec4 FragColor;

uniform sampler2D u_texture0;

in vec2 uv;

void main()
{
	FragColor = texture(u_texture0, uv);
}
