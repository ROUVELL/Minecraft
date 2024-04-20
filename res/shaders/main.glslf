#version 330 core

layout (location = 0) out vec4 FragColor;

uniform sampler2D u_texture0;

in vec4 color;
in vec2 uv;

void main()
{
	FragColor = color * texture(u_texture0, uv);
}
